#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iomanip>
#include <sstream>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <stdexcept>
#include <errno.h>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include "INIReader.h"
#include "byte_converter.h"
#include <modbus/modbus.h>

using namespace std;
static const vector<vector<string>> byteorder_list
{
	{"01","0123","01234567"},
	{"10","3210","76543210"},
	{"01","1032","10325476"},
	{"10","2301","67452301"}
};

modbus_t *client_mb;
//uint16_t tab_Ireg[5];
//uint8_t tab_Creg[5];
//uint8_t tab_Dreg[5];

modbus_t *server_mb;
modbus_mapping_t *server_mapping;

int rc;
int errno;
int soc = -1;

class DataGroup{
    friend std::ostream &operator<<(std::ostream &os , const DataGroup &d);
	bool enable;
    string dataGroupName;
    string dataGroupType;
    int deviceId;
    string modbusRegisterType;
    int scadaModbusServerStartAddress;
    string value;
public:
    DataGroup() = default;
    DataGroup(bool enable , string dataGroupName , string dataGroupType , int deviceId , string modbusRegisterType ,
            int scadaModbusServerStartAddress , string value)
    : enable {enable} , dataGroupName {dataGroupName} , dataGroupType {dataGroupType} , deviceId {deviceId} ,
    modbusRegisterType {modbusRegisterType} , scadaModbusServerStartAddress {scadaModbusServerStartAddress} ,
    value {value} {}
	
	const bool getEnable() const {
		return enable;
	}
	
	const string &getDataGroupName() const {
        return dataGroupName;
    }

    const string &getDataGroupType() const {
        return dataGroupType;
    }

    int getDeviceId() const {
        return deviceId;
    }

    const string &getModbusRegisterType() const {
        return modbusRegisterType;
    }

    int getScadaModbusServerStartAddress() const {
        return scadaModbusServerStartAddress;
    }

    const string &getValue() const {
        return value;
    }
};

std::ostream &operator<<(std::ostream &os , const DataGroup &d) {

    os << endl << d.dataGroupName
       << endl << d.dataGroupType
       << endl << d.deviceId
       << endl << d.modbusRegisterType
       << endl << d.scadaModbusServerStartAddress
       << endl << d.value;

    return os;

}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

void Read_Modbus(int sig)
{
	Byte_converter byteConvertor;
	byteConvertor.inverse_byte_order = true;
	float mineValue;
	signal(SIGALRM, SIG_IGN);
	printf("Modbus Read!!!\n");
	INIReader conf(".//config//config.ini");
	char start = conf.GetInteger("Settings" , "start" , 0);
	int index = 0;
	int needBytes = 0;
	list<DataGroup> dataGroup;
	list<DataGroup>::iterator data = dataGroup.begin();
	fstream  aFile;
	INIReader read(".//config//config-small.ini");
	for (int i = 0 ; i < 5 ; i++){
		string number = to_string(i);
		if (read.Get("DataGroup" + number , "dataGroupType" , "") == "Uint32" ||
			read.Get("DataGroup" + number , "dataGroupType" , "") == "Float"){
			needBytes += 2;
		}
		/*else if (read.Get("DataGroup" + c , "dataGroupType" , "") == "double" ||
				 read.Get("DataGroup" + c , "dataGroupType" , "") == "long"){
			start += 4;
			index += 4;
		}*/
		else{
			needBytes ++;
		}
	}
	//cout << needBytes << endl;
	vector<uint16_t> tab_Hreg(needBytes);
	
	
	//read holding register
	rc=modbus_read_registers(client_mb, start, needBytes, tab_Hreg.data());// &tab_Hreg[0]
	//write holding register
	//rc = modbus_write_register(ctx, UT_REGISTERS_ADDRESS, 0x1234);

	for (int i = 0 ; i < needBytes ; i++)
	{
		string c = to_string(i);
		if (read.GetInteger("DataGroup" + c , "scadaModbusServerStartAddress" , 0) == start)
		{
			if (read.Get("DataGroup" + c , "dataGroupType" , "") == "Uint32"){
				mineValue = byteConvertor.Convert2UInt16ToUInt32(&tab_Hreg[index] , byteorder_list[3][1]);
			}
			else if (read.Get("DataGroup" + c , "dataGroupType" , "") == "Float"){
				mineValue = byteConvertor.Convert2UInt16ToFloat(&tab_Hreg[index] , byteorder_list[3][1]);
			}
			//else if (read.Get("DataGroup" + c , "dataGroupType" , "") == "double")
				//mineValue = byteConvertor.Convert4UInt16ToDouble(&tab_Hreg[index] , byteorder_list[3][1]);
			//else if (read.Get("DataGroup" + c , "dataGroupType" , "") == "long")
				//mineValue = byteConvertor.Convert4UInt16ToLong(&tab_Hreg[index] , byteorder_list[3][1]);
			else{
				mineValue = tab_Hreg[index];
			}
			dataGroup.insert(dataGroup.begin() , DataGroup(
						read.GetBoolean("DataGroup" + c , "enable" , false) ,
                        read.Get("DataGroup" + c , "dataGroupName" , "") ,
                        read.Get("DataGroup" + c , "dataGroupType" , "") ,
                        read.GetInteger("DataGroup" + c , "deviceId" , 0) ,
                        read.Get("DataGroup" + c , "modbusRegisterType" , "") ,
                        start , to_string_with_precision(mineValue , 1)
                        ));
			
			if (read.Get("DataGroup" + c , "dataGroupType" , "") == "Uint32" ||
				read.Get("DataGroup" + c , "dataGroupType" , "") == "Float"){
				start += 2;
				index += 2;
			}
			/*else if (read.Get("DataGroup" + c , "dataGroupType" , "") == "double" ||
					 read.Get("DataGroup" + c , "dataGroupType" , "") == "long"){
				start += 4;
				index += 4;
			}*/
			else{
				start ++;
				index ++;
			}	
		}
	}
	
	aFile.open(".//..//Simple-Web-Server-3.0.0-rc2//web//index.html", ios::out);
	for (data = dataGroup.begin() ; data != dataGroup.end() ; data++)
    {
        string num = to_string(data->getDeviceId());
		if(data->getEnable() && read.GetBoolean("Device" + num , "enable" , false)){
			//string deviceName = read.Get("Device" + num , "deviceName" , "");
			aFile <<"<!DOCTYPE html>\n""<html langq=\"en\">""<head>\n""<meta charset=\"UTF-8\">\n"
					"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
					"<title>config-small.ini</title>\n""<meta http-equiv=\"refresh\" content=\"30\">"
					"</head>""<script language=\"javascript\">\n""setTimeout(function(){\n""window.location.reload(1);\n"
					"}, 2000);\n""</script>""<style>"".styled-table {\n""margin-left: 10px !important; margin-right:10px !important;"
					"flex: 1 1 150px;""border-collapse: collapse;\n""margin: 25px 0;\n"
					"font-size: 0.9em;\n""font-family: sans-serif;\n""min-width: 400px;\n""table-layout: fixed;""max-width: 400px;""box-shadow: 0 0 20px rgba(0, 0, 0, 0.15);\n"
					"}"".styled-table thead tr {\n""background-color: #009879;\n""color: #ffffff;\n""text-align: left;\n"
					"}"".styled-table th,\n"".styled-table td {\n""padding: 12px 15px;\n""}"
					".styled-table tbody tr {\n""border-bottom: 1px solid #dddddd;\n""}\n""\n"
					".container {display: flex; flex-wrap: wrap; align-items: flex-start; justify-content: center;}"
					".styled-table tbody tr:nth-of-type(even) {\n""background-color: #f3f3f3;\n""}\n""\n"
					".styled-table tbody tr:last-of-type {\n""border-bottom: 2px solid #009879;\n""}"
					".head""{""table-layout: fixed;""background: fixed;background-attachment: fixed;""}"
					".styled-table tbody tr:hover {\n""color: #ff0000;\n""}""</style>""<body class=\"container\">";
			aFile <<"<table class=\"styled-table\">"
					"<thead>"
					"<tr>"
					"<th>Device name</th>"
					"<th>Data type</th>"
					"<th>Value</th>"
					"</tr>"
					"</thead class=\"head\">";
			aFile <<"<tbody>"
                    "<tr>"
                    "<td>" << read.Get("Device" + num , "deviceName" , "") << "</td>"
                    "<td>" << data->getDataGroupName() << "</td>"
                    "<td>" << data->getValue() << "</td>"
                    "</tr>"
                    "</tbody>"
                    "</table>";
			//aFile << "<!DOCTYPE html>\n""<html langq=\"en\">""<head>\n""<meta charset=\"UTF-8\">\n"
			//		"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
			//	  "<title>config-small.ini</title>\n""<meta http-equiv=\"refresh\" content=\"30\">"
			//		"</head>""<script language=\"javascript\">\n""setTimeout(function(){\n""window.location.reload(1);\n"
			//		"}, 1000);\n""</script>" << "<p>" << read.Get("Device" + num , "deviceName" , "") << " : " << data->getDataGroupName() <<
			//	  " : " << data->getValue() << "</p>" << endl;
		}
		
    }
	
	
	/*for (const DataGroup &data : dataGroup) {

        cout << data << endl;

    }*/

	//test read results
	if (rc == -1) 
	{
		fprintf(stderr, "%s\n", modbus_strerror(errno));
	}
	//printf("Holding Register:%u %u \n",tab_Hreg[0] , tab_Hreg[1]);
	//cout << "h0 : " << sizeof(&tab_Hreg[0]) << endl;
	
	//cout << "h2 : " << byteConvertor.Convert2UInt16ToUInt32(&tab_Hreg[3] , byteorder_list[3][1])  << endl;
	//cout << "h2 : " << byteConvertor.Convert2UInt16ToFloat(&tab_Hreg[3] , byteorder_list[3][1]) << endl;
	//cout << "h3 : " << tab_Hreg[5] << endl;
	//cout << "h4 : " << tab_Hreg[6] << endl;

    //vector<uint16_t> tab_Hregf(2);
	//rc=modbus_read_registers(client_mb, 30, 2, tab_Hregf.data());// &tab_Hreg[0]
	//cout << "fh0 : " << tab_Hregf[0] << endl;
	//cout << "fh1 : " << tab_Hregf[1] << endl;

	//cout << "0 : "<< byteConvertor.Convert2UInt16ToFloat(&tab_Hregf[0] , byteorder_list[0][1]) << endl;
	//cout << "1 : "<< byteConvertor.Convert2UInt16ToFloat(&tab_Hregf[0] , byteorder_list[1][1]) << endl;
	//cout << "2 : "<< byteConvertor.Convert2UInt16ToFloat(&tab_Hregf[0] , byteorder_list[2][1]) << endl;
	//cout << "3 : "<< byteConvertor.Convert2UInt16ToFloat(&tab_Hregf[0] , byteorder_list[3][1]) << endl;
	
	//cout << "h2 : "<< << endl;

	/*
	//read input register
	rc = modbus_read_input_registers(client_mb, 0, 4,tab_Ireg);
	//test read results
	if (rc == -1) 
	{
		fprintf(stderr, "%s\n", modbus_strerror(errno));
	}
	printf("Input Register:%u %u %u %u \n",tab_Ireg[0],tab_Ireg[1],tab_Ireg[2],tab_Ireg[3]);
	
	//read coil 
	rc = modbus_read_bits(client_mb, 0, 4, tab_Creg);
	//write coil 
	//rc = modbus_write_bit(ctx, UT_BITS_ADDRESS, ON);
	//test read results
	if (rc == -1) 
	{
		fprintf(stderr, "%s\n", modbus_strerror(errno));
	}
	printf("Coil Register:%u %u %u %u \n",tab_Creg[0],tab_Creg[1],tab_Creg[2],tab_Creg[3]);

	//read input status(DISCRITE)
	rc = modbus_read_input_bits(client_mb, 0, 4, tab_Dreg);
	//test read results
	if (rc == -1) 
	{
		fprintf(stderr, "%s\n", modbus_strerror(errno));
	}
	printf("Discrite Input:%u %u %u %u \n",tab_Dreg[0],tab_Dreg[1],tab_Dreg[2],tab_Dreg[3]);
	// update measurement values based on input string
	*/
	for(int i=0;i<4;i++)
	{
		//server_mapping->tab_registers[server_mapping->start_registers + i] =tab_Hreg[i];
		//server_mapping->tab_input_registers[server_mapping->start_input_registers+i] =tab_Ireg[i];
		//server_mapping->tab_bits[server_mapping->start_bits+i] =tab_Creg[i];
		//server_mapping->tab_input_bits[server_mapping->start_input_bits+i] =tab_Dreg[i];
		
		server_mapping->tab_registers[server_mapping->start_registers + i] =i;
		server_mapping->tab_input_registers[server_mapping->start_input_registers+i] =i;
		server_mapping->tab_bits[server_mapping->start_bits+i] =i;
		server_mapping->tab_input_bits[server_mapping->start_input_bits+i] =i;
	}

	signal(SIGALRM, Read_Modbus);
	alarm(3);
	aFile << "</body>""</html>";
	aFile.close();
}


int main(void)
{
	
	INIReader conf(".//config//config.ini");
	
	printf(".:ida DCU v3.1 Start:.\n");
	printf("CopyRight (C) ida Ltd;\n");

    //creat new modbus connection
   	client_mb = modbus_new_tcp(conf.Get("Settings" , "IP" , "").c_str() , conf.GetInteger("Settings" , "tcpPort" , 0));
	//client_mb = modbus_new_rtu("/dev/ttyS2",9600,'N',8,1);

    if (client_mb == NULL) 
	{
        fprintf(stderr, "Unable to allocate libmodbus context\n");
        return -1;
	}

	modbus_set_slave(client_mb,1);

	rc=modbus_connect(client_mb);
	if (rc == -1) 
	{
		fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
		modbus_free(client_mb);
		return -1;
	}
	if(client_mb != NULL && rc != -1)
	{
		fprintf(stderr,"Connect To Client Success!\n");
	}	

	

	//modbus server creating
	//tcp
	const char* tPort = to_string(conf.GetInteger("Settings" , "tcpPort" , 0)).c_str();
	server_mb = modbus_new_tcp_pi(conf.Get("Settings" , "IP" , "").c_str() , tPort);
    modbus_set_debug(server_mb, TRUE); 
	//rtu
	//server_mb = modbus_new_rtu("/dev/ttyS2",9600,'N',8,1);

    //server_mapping = modbus_mapping_new_start_address(0, 0, 0, 0, 10000, 10, 0, 0);
	server_mapping = modbus_mapping_new(5,5,5,5);
    if (server_mapping == NULL) 
    {
        fprintf(stderr,"Failed to allocate the mapping: %s\n",modbus_strerror(errno));
        modbus_free(server_mb);
        return -1;
    }

	//active modbus client read register routing every few second
	signal(SIGALRM, Read_Modbus);
	alarm(3);
	//printf("while loop:\n");
    while(true) 
    {
			//printf("wait for query:\n");
			//tcp
			u_int8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
			//rtu
			//u_int8_t query[MODBUS_RTU_MAX_ADU_LENGTH];

			printf("socket:%u\n",soc);

			//start server at startup
			if(soc == -1)
			{
				//tcp
				soc = modbus_tcp_pi_listen(server_mb, 1);
				modbus_tcp_pi_accept(server_mb, &soc);
				//rtu
				modbus_set_slave(server_mb, 1);
				soc = modbus_connect(server_mb);
			}
    		

			//printf("1socket:%u\n",soc);
			rc = modbus_receive(server_mb, query);
			//printf("1rc:%u\n",rc);

			if (rc > 0) 
			{
				// rc is the query size 
				modbus_reply(server_mb, query, rc, server_mapping);
			} 
			else if (rc == -1) 
			{
				
				// Connection closed by the client or error 
				close(soc);
				soc = -1;
				//break;
			}
    }

    
	fprintf(stderr,"Quit the loop: %s\n", modbus_strerror(errno));
	if (soc != -1) 
		{
			close(soc);
		}
    
    modbus_mapping_free(server_mapping);
	modbus_close(client_mb);
	modbus_free(client_mb);
    modbus_close(server_mb);
    modbus_free(server_mb);


    return 0;
}
