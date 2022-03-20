//=========================================================================
// Copyright (C) IDA, ltd - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Website http://ida-ltd.com
//=========================================================================

#ifndef IDA_DCU_BYTE_CONVERTER_H
#define IDA_DCU_BYTE_CONVERTER_H

#include <string>
#include <vector>
#include <iostream>


//#define DEBUG_BYTE_CONVERTER

typedef unsigned char byte;

// This class Comes into two Parts.
// The Modbus library uses uint16_t to get data from devices, see the documentation of
// modbus_read_registers() function.
// If the readed data comes in the range of uint8_t we should use Part I functions.
// The function to convert the array of uint16_t containing uint8_t values into other
// types are developed in the first part of this class.
//
// At somepoint in SCADA-Mission software, there must be some conversions from
// uint16_t arrays to other types. This types needs to separate the uint16_t into
// two uint8_t before the conversions. This functions comes into the second part of the class.
// This part haven't been used in the DCU code yet. But since it is developed well, we let it 
// be for the future needs.
///
class Byte_converter
{
	public:

	
	Byte_converter(bool byte_order=true) {
		inverse_byte_order = byte_order;
	};
	
	bool inverse_byte_order;

	//============================================================================
	//============================================================================
	// ****************************** PART I *************************************
	//============================================================================
	//============================================================================
	
	int16_t Convert2UInt8ToInt16(uint8_t* v1, const std::string &byteOrder)
	{		
      
#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt8ToInt16 " << " i " << std::endl;
#endif

		static byte buff[2];

		if (inverse_byte_order)
		{
			buff[byteOrder[1] - '0'] = v1[0];
			buff[byteOrder[0] - '0'] = v1[1];
		}		
		else
		{
			buff[byteOrder[0] - '0'] = v1[0];
			buff[byteOrder[1] - '0'] = v1[1];
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		int16_t value = *(int16_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt8ToInt16 " << " f " << std::endl;
#endif		

		return value;
	}
	
	//============================================================================
	// 
	//============================================================================
	uint16_t Convert2UInt8ToUInt16(uint8_t* v1, const std::string &byteOrder)
	{
		

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt8ToUInt16 " << " i " << std::endl;
#endif		

		static byte buff[2];

		if (inverse_byte_order)
		{
			buff[byteOrder[1] - '0'] = v1[0];
			buff[byteOrder[0] - '0'] = v1[1];
		}		
		else
		{
			buff[byteOrder[0] - '0'] = v1[0];
			buff[byteOrder[1] - '0'] = v1[1];
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		uint16_t value = *(uint16_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt8ToUInt16 " << " f " << std::endl;
#endif		
		
		return value;
	}
	//============================================================================
	// 
	//============================================================================
	int16_t Convert2UInt16ToInt16(uint16_t* v1, const std::string &byteOrder) 
	{		

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt16ToInt16 " << " i " << std::endl;
#endif		

		static byte buff[2];

		if (inverse_byte_order)
		{
			buff[byteOrder[1] - '0'] = (byte) v1[0]; // conversion cuts the numbers 
			buff[byteOrder[0] - '0'] = (byte) v1[1];
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte) v1[0];
			buff[byteOrder[1] - '0'] = (byte) v1[1];
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		int16_t value = *(int16_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt16ToInt16 " << " f " << std::endl;
#endif		
		
		return value;
	}
	
	//============================================================================
	// 
	//============================================================================
	uint16_t Convert2UInt16ToUInt16(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt16ToUInt16 " << " i " << std::endl;
#endif		
		
		static byte buff[2];

		if (inverse_byte_order)
		{
			buff[byteOrder[1] - '0'] = (byte) v1[0];
			buff[byteOrder[0] - '0'] = (byte) v1[1];
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte) v1[0];
			buff[byteOrder[1] - '0'] = (byte) v1[1];
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		uint16_t value = *(uint16_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt16ToUInt16 " << " f " << std::endl;
#endif		
		
		return value;
	}

	//============================================================================
	// 
	//============================================================================
	uint32_t Convert4UInt16ToUInt32(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToUInt32 " << " i " << std::endl;
#endif		
		
		static byte buff[4];

		if (inverse_byte_order)
		{
			buff[byteOrder[3] - '0'] = (byte) v1[0];
			buff[byteOrder[2] - '0'] = (byte) v1[1];
			buff[byteOrder[1] - '0'] = (byte) v1[2];
			buff[byteOrder[0] - '0'] = (byte) v1[3];
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte) v1[0];
			buff[byteOrder[1] - '0'] = (byte) v1[1];
			buff[byteOrder[2] - '0'] = (byte) v1[2];
			buff[byteOrder[3] - '0'] = (byte) v1[3];
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		uint32_t value = *(uint32_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToUInt32 " << " f " << std::endl;
#endif		
		
		return value;
	}

	//============================================================================
	// 
	//============================================================================
	int32_t Convert4UInt16ToInt32(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToInt32 " << " i " << std::endl;
#endif		
		
		static byte buff[4];

		if (inverse_byte_order)
		{
			buff[byteOrder[3] - '0'] = (byte) v1[0];
			buff[byteOrder[2] - '0'] = (byte) v1[1];
			buff[byteOrder[1] - '0'] = (byte) v1[2];
			buff[byteOrder[0] - '0'] = (byte) v1[3];
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte) v1[0];
			buff[byteOrder[1] - '0'] = (byte) v1[1];
			buff[byteOrder[2] - '0'] = (byte) v1[2];
			buff[byteOrder[3] - '0'] = (byte) v1[3];
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		int32_t value = *(int32_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToInt32 " << " f " << std::endl;
#endif		
		
		return value;
	}

	//============================================================================
	// 
	//============================================================================
	float Convert4UInt16ToFloat(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToFloat " << " i " << std::endl;
#endif		
		
		static byte buff[4];

		if (inverse_byte_order)
		{
			buff[byteOrder[3] - '0'] = (byte) v1[0];
			buff[byteOrder[2] - '0'] = (byte) v1[1];
			buff[byteOrder[1] - '0'] = (byte) v1[2];
			buff[byteOrder[0] - '0'] = (byte) v1[3];
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte) v1[0];
			buff[byteOrder[1] - '0'] = (byte) v1[1];
			buff[byteOrder[2] - '0'] = (byte) v1[2];
			buff[byteOrder[3] - '0'] = (byte) v1[3];
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		float value = *(float *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToFloat " << " f " << std::endl;
#endif		
		
		return value;
	}
	
	//============================================================================
	// 
	//============================================================================
	double Convert8UInt16ToDouble(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert8UInt16ToDouble " << " i " << std::endl;
#endif		
		
		static byte buff[8];

		if (inverse_byte_order)
		{
			buff[byteOrder[7] - '0'] = (byte) v1[0];
			buff[byteOrder[6] - '0'] = (byte) v1[1];
			buff[byteOrder[5] - '0'] = (byte) v1[2];
			buff[byteOrder[4] - '0'] = (byte) v1[3];
			buff[byteOrder[3] - '0'] = (byte) v1[4];
			buff[byteOrder[2] - '0'] = (byte) v1[5];
			buff[byteOrder[1] - '0'] = (byte) v1[6];
			buff[byteOrder[0] - '0'] = (byte) v1[7];
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte) v1[0];
			buff[byteOrder[1] - '0'] = (byte) v1[1];
			buff[byteOrder[2] - '0'] = (byte) v1[2];
			buff[byteOrder[3] - '0'] = (byte) v1[3];
			buff[byteOrder[4] - '0'] = (byte) v1[4];
			buff[byteOrder[5] - '0'] = (byte) v1[5];
			buff[byteOrder[6] - '0'] = (byte) v1[6];
			buff[byteOrder[7] - '0'] = (byte) v1[7];
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		double value = *(double *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert8UInt16ToDouble " << " f " << std::endl;
#endif		
		
		return value;
	}
	
	//============================================================================
	// 
	//============================================================================
	int64_t Convert8UInt16ToInt64(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert8UInt16ToInt64 " << " i " << std::endl;
#endif		
		
		static byte buff[8];

		if (inverse_byte_order)
		{
			buff[byteOrder[7] - '0'] = (byte) v1[0];
			buff[byteOrder[6] - '0'] = (byte) v1[1];
			buff[byteOrder[5] - '0'] = (byte) v1[2];
			buff[byteOrder[4] - '0'] = (byte) v1[3];
			buff[byteOrder[3] - '0'] = (byte) v1[4];
			buff[byteOrder[2] - '0'] = (byte) v1[5];
			buff[byteOrder[1] - '0'] = (byte) v1[6];
			buff[byteOrder[0] - '0'] = (byte) v1[7];
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte) v1[0];
			buff[byteOrder[1] - '0'] = (byte) v1[1];
			buff[byteOrder[2] - '0'] = (byte) v1[2];
			buff[byteOrder[3] - '0'] = (byte) v1[3];
			buff[byteOrder[4] - '0'] = (byte) v1[4];
			buff[byteOrder[5] - '0'] = (byte) v1[5];
			buff[byteOrder[6] - '0'] = (byte) v1[6];
			buff[byteOrder[7] - '0'] = (byte) v1[7];
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		int64_t value = *(int64_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert8UInt16ToInt64 " << " f " << std::endl;
#endif		
		
		return value;
	}
	
	//============================================================================
	// 
	//============================================================================
	uint64_t Convert8UInt16ToUInt64(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert8UInt16ToUInt64 " << " i " << std::endl;
#endif		
		
		static byte buff[8];

		if (inverse_byte_order)
		{
			buff[byteOrder[7] - '0'] = (byte) v1[0];
			buff[byteOrder[6] - '0'] = (byte) v1[1];
			buff[byteOrder[5] - '0'] = (byte) v1[2];
			buff[byteOrder[4] - '0'] = (byte) v1[3];
			buff[byteOrder[3] - '0'] = (byte) v1[4];
			buff[byteOrder[2] - '0'] = (byte) v1[5];
			buff[byteOrder[1] - '0'] = (byte) v1[6];
			buff[byteOrder[0] - '0'] = (byte) v1[7];
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte) v1[0];
			buff[byteOrder[1] - '0'] = (byte) v1[1];
			buff[byteOrder[2] - '0'] = (byte) v1[2];
			buff[byteOrder[3] - '0'] = (byte) v1[3];
			buff[byteOrder[4] - '0'] = (byte) v1[4];
			buff[byteOrder[5] - '0'] = (byte) v1[5];
			buff[byteOrder[6] - '0'] = (byte) v1[6];
			buff[byteOrder[7] - '0'] = (byte) v1[7];
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		uint64_t value = *(uint64_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert8UInt16ToUInt64 " << " f " << std::endl;
#endif		
		
		return value;
	}
	
	//============================================================================
	//============================================================================
	// ****************************** PART II ************************************
	//============================================================================
	//============================================================================
	
	
	//============================================================================
	// A change to the byte order
	//============================================================================
	uint16_t ConvertUInt16ToUInt16(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertUInt16ToUInt16 " << " i " << std::endl;
#endif		
		
		//--------------------------------------------------------
		// The following 'uint16_t' can be replaced with 'uint8_t':
		//--------------------------------------------------------
		uint16_t b1L = (uint16_t)((v1[0] & 0xFF00) >> 8);
		uint16_t b1R = (uint16_t)(v1[0] & 0x00FF);


		static byte buff[2];

		if (inverse_byte_order)
		{
			buff[byteOrder[1] - '0'] = (byte)b1L;
			buff[byteOrder[0] - '0'] = (byte)b1R;
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte)b1L;
			buff[byteOrder[1] - '0'] = (byte)b1R;
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		uint16_t value = *(uint16_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertUInt16ToUInt16 " << " f " << std::endl;
#endif		
		
		return value;
	}
	
	//============================================================================
	// A change to the byte order and sign
	//============================================================================
	int16_t ConvertUInt16ToInt16(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertUInt16ToInt16 " << " i " << std::endl;
#endif		
		
		//--------------------------------------------------------
		// The following 'uint16_t' can be replaced with 'uint8_t':
		//--------------------------------------------------------
		uint16_t b1L = (uint16_t)((v1[0] & 0xFF00) >> 8);
		uint16_t b1R = (uint16_t)(v1[0] & 0x00FF);


		static byte buff[2];

		if (inverse_byte_order)
		{
			buff[byteOrder[1] - '0'] = (byte)b1L;
			buff[byteOrder[0] - '0'] = (byte)b1R;
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte)b1L;
			buff[byteOrder[1] - '0'] = (byte)b1R;
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		int16_t value = *(int16_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertUInt16ToInt16 " << " f " << std::endl;
#endif		
		
		return value;
	}

	//============================================================================
	//
	//============================================================================
	float Convert2UInt16ToFloat(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt16ToFloat " << v1[0] << " " << v1[1] << " " <<byteOrder << std::endl;
#endif		
		
		// ModBus read in Hex: F5C3   41C2
		// Convert to Decimal: 62915  16834
		// Expected value for float: 24.37
		// With byte order "1032" and inverse_byte_order = false;
		// With byte order "2301" and inverse_byte_order = true;
		// UInt32 v1 = 62915;
		// UInt32 v2 = 16834;
		//
		//
		
		//--------------------------------------------------------
		// The following 'uint16_t' can be replaced with 'uint8_t':
		//--------------------------------------------------------
		uint16_t b1L = (uint16_t)((v1[0] & 0xFF00) >> 8);
		uint16_t b1R = (uint16_t)(v1[0] & 0x00FF);


		uint16_t b2L = (uint16_t)((v1[1] & 0xFF00) >> 8);
		uint16_t b2R = (uint16_t)(v1[1] & 0x00FF);


		static byte buff[4];

		if (inverse_byte_order)
		{
			buff[byteOrder[3] - '0'] = (byte)b1L;
			buff[byteOrder[2] - '0'] = (byte)b1R;
			buff[byteOrder[1] - '0'] = (byte)b2L;
			buff[byteOrder[0] - '0'] = (byte)b2R;
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte)b1L;
			buff[byteOrder[1] - '0'] = (byte)b1R;
			buff[byteOrder[2] - '0'] = (byte)b2L;
			buff[byteOrder[3] - '0'] = (byte)b2R;
		}

		//float value = BitConverter.ToSingle(buff, 0);		
		float value = *(float *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt16ToFloat " <<  value  << std::endl;
#endif		
		
		return value;
	}
	
	//============================================================================
	//
	//============================================================================
	
	double Convert4UInt16ToDouble(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToDouble " << " i " << std::endl;
#endif		

		uint16_t b1L = (uint16_t)((v1[0] & 0xFF00) >> 8);
		uint16_t b1R = (uint16_t)(v1[0] & 0x00FF);

		uint16_t b2L = (uint16_t)((v1[1] & 0xFF00) >> 8);
		uint16_t b2R = (uint16_t)(v1[1] & 0x00FF);

		uint16_t b3L = (uint16_t)((v1[2] & 0xFF00) >> 8);
		uint16_t b3R = (uint16_t)(v1[2] & 0x00FF);

		uint16_t b4L = (uint16_t)((v1[3] & 0xFF00) >> 8);
		uint16_t b4R = (uint16_t)(v1[3] & 0x00FF);

		static byte buff[4];

		if (inverse_byte_order)
		{
			buff[byteOrder[7] - '0'] = (byte)b1L;
			buff[byteOrder[6] - '0'] = (byte)b1R;
			buff[byteOrder[5] - '0'] = (byte)b2L;
			buff[byteOrder[4] - '0'] = (byte)b2R;
			buff[byteOrder[3] - '0'] = (byte)b3L;
			buff[byteOrder[2] - '0'] = (byte)b3R;
			buff[byteOrder[1] - '0'] = (byte)b4L;
			buff[byteOrder[0] - '0'] = (byte)b4R;
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte)b1L;
			buff[byteOrder[1] - '0'] = (byte)b1R;
			buff[byteOrder[2] - '0'] = (byte)b2L;
			buff[byteOrder[3] - '0'] = (byte)b2R;
			buff[byteOrder[4] - '0'] = (byte)b3L;
			buff[byteOrder[5] - '0'] = (byte)b3R;
			buff[byteOrder[6] - '0'] = (byte)b4L;
			buff[byteOrder[7] - '0'] = (byte)b4R;

		}
		//double value = BitConverter.ToDouble(buff, 0);
		double value = *(double *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToDouble " << " f " << std::endl;
#endif		

		return value;
	}

	//============================================================================
	//
	//============================================================================
	
	 uint32_t Convert2UInt16ToUInt32(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt16ToUInt32 " << " i " << std::endl;
#endif		

		uint16_t b1L = (uint16_t)((v1[0] & 0xFF00) >> 8);
		uint16_t b1R = (uint16_t)(v1[0] & 0x00FF);


		uint16_t b2L = (uint16_t)((v1[1] & 0xFF00) >> 8);
		uint16_t b2R = (uint16_t)(v1[1] & 0x00FF); ;


		static byte buff[4];

		if (inverse_byte_order)
		{
			buff[byteOrder[3] - '0'] = (byte)b1L;
			buff[byteOrder[2] - '0'] = (byte)b1R;
			buff[byteOrder[1] - '0'] = (byte)b2L;
			buff[byteOrder[0] - '0'] = (byte)b2R;
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte)b1L;
			buff[byteOrder[1] - '0'] = (byte)b1R;
			buff[byteOrder[2] - '0'] = (byte)b2L;
			buff[byteOrder[3] - '0'] = (byte)b2R;	
		}
		

		//uint32_t value = BitConverter.ToUInt32(buff, 0);
		uint32_t value = *(uint32_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt16ToUInt32 " << " f " << std::endl;
#endif		

		return value;
	}

	//============================================================================
	//
	//============================================================================

	 int32_t Convert2UInt16ToInt32(uint16_t* v1, const std::string &byteOrder)
	{           

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt16ToInt32 " << " i " << std::endl;
#endif		

		uint16_t b1L = (uint16_t)((v1[0] & 0xFF00) >> 8);
		uint16_t b1R = (uint16_t)(v1[0] & 0x00FF);


		uint16_t b2L = (uint16_t)((v1[1] & 0xFF00) >> 8);
		uint16_t b2R = (uint16_t)(v1[1] & 0x00FF); ;


		static byte buff[4];

		if (inverse_byte_order)
		{
			buff[byteOrder[3] - '0'] = (byte)b1L;
			buff[byteOrder[2] - '0'] = (byte)b1R;
			buff[byteOrder[1] - '0'] = (byte)b2L;
			buff[byteOrder[0] - '0'] = (byte)b2R;
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte)b1L;
			buff[byteOrder[1] - '0'] = (byte)b1R;
			buff[byteOrder[2] - '0'] = (byte)b2L;
			buff[byteOrder[3] - '0'] = (byte)b2R;	
		}
		//int32_t value = BitConverter.ToInt32(buff, 0);
		int32_t value = *(int32_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert2UInt16ToInt32 " << " f " << std::endl;
#endif		

		return value;
	}

	//============================================================================
	//
	//============================================================================
	
	 uint64_t Convert4UInt16ToUInt64(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToUInt64 " << " i " << std::endl;
#endif		

		uint16_t b1L = (uint16_t)((v1[0] & 0xFF00) >> 8);
		uint16_t b1R = (uint16_t)(v1[0] & 0x00FF);

		uint16_t b2L = (uint16_t)((v1[1] & 0xFF00) >> 8);
		uint16_t b2R = (uint16_t)(v1[1] & 0x00FF);

		uint16_t b3L = (uint16_t)((v1[2] & 0xFF00) >> 8);
		uint16_t b3R = (uint16_t)(v1[2] & 0x00FF);

		uint16_t b4L = (uint16_t)((v1[3] & 0xFF00) >> 8);
		uint16_t b4R = (uint16_t)(v1[3] & 0x00FF);

		static byte buff[4];

		if (inverse_byte_order)
		{
			buff[byteOrder[7] - '0'] = (byte)b1L;
			buff[byteOrder[6] - '0'] = (byte)b1R;
			buff[byteOrder[5] - '0'] = (byte)b2L;
			buff[byteOrder[4] - '0'] = (byte)b2R;
			buff[byteOrder[3] - '0'] = (byte)b3L;
			buff[byteOrder[2] - '0'] = (byte)b3R;
			buff[byteOrder[1] - '0'] = (byte)b4L;
			buff[byteOrder[0] - '0'] = (byte)b4R;
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte)b1L;
			buff[byteOrder[1] - '0'] = (byte)b1R;
			buff[byteOrder[2] - '0'] = (byte)b2L;
			buff[byteOrder[3] - '0'] = (byte)b2R;
			buff[byteOrder[4] - '0'] = (byte)b3L;
			buff[byteOrder[5] - '0'] = (byte)b3R;
			buff[byteOrder[6] - '0'] = (byte)b4L;
			buff[byteOrder[7] - '0'] = (byte)b4R;
		}
		
		//uint64_t value = BitConverter.ToUInt64(buff, 0);
		uint64_t value = *(uint64_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToUInt64 " << " f " << std::endl;
#endif		

		return value;
	}

	//============================================================================
	//
	//============================================================================
	
	 int64_t Convert4UInt16ToInt64(uint16_t* v1, const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToInt64 " << " i " << std::endl;
#endif		

		uint16_t b1L = (uint16_t)((v1[0] & 0xFF00) >> 8);
		uint16_t b1R = (uint16_t)(v1[0] & 0x00FF);

		uint16_t b2L = (uint16_t)((v1[1] & 0xFF00) >> 8);
		uint16_t b2R = (uint16_t)(v1[1] & 0x00FF);

		uint16_t b3L = (uint16_t)((v1[2] & 0xFF00) >> 8);
		uint16_t b3R = (uint16_t)(v1[2] & 0x00FF);

		uint16_t b4L = (uint16_t)((v1[3] & 0xFF00) >> 8);
		uint16_t b4R = (uint16_t)(v1[3] & 0x00FF);

		static byte buff[4];
		
		if (inverse_byte_order)
		{
			buff[byteOrder[7] - '0'] = (byte)b1L;
			buff[byteOrder[6] - '0'] = (byte)b1R;
			buff[byteOrder[5] - '0'] = (byte)b2L;
			buff[byteOrder[4] - '0'] = (byte)b2R;
			buff[byteOrder[3] - '0'] = (byte)b3L;
			buff[byteOrder[2] - '0'] = (byte)b3R;
			buff[byteOrder[1] - '0'] = (byte)b4L;
			buff[byteOrder[0] - '0'] = (byte)b4R;
		}		
		else
		{
			buff[byteOrder[0] - '0'] = (byte)b1L;
			buff[byteOrder[1] - '0'] = (byte)b1R;
			buff[byteOrder[2] - '0'] = (byte)b2L;
			buff[byteOrder[3] - '0'] = (byte)b2R;
			buff[byteOrder[4] - '0'] = (byte)b3L;
			buff[byteOrder[5] - '0'] = (byte)b3R;
			buff[byteOrder[6] - '0'] = (byte)b4L;
			buff[byteOrder[7] - '0'] = (byte)b4R;
		}
		
		//int64_t value = BitConverter.ToInt64(buff, 0);
		int64_t value = *(int64_t *)(buff);

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "Convert4UInt16ToInt64 " << " f " << std::endl;
#endif		

		return value;
	}
	//============================================================================
	// 
	//============================================================================
	
		// This part is used in  modbus_client_for_scada_modbus_server.cpp
		// before setting modbus client values in scadaMapping
	
	//============================================================================
	// 
	//============================================================================
	void ChangeUInt16VectorByteOrder(std::vector<uint16_t> &v, std::vector<uint16_t> &v_out,const std::string &byteOrder)
	{

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ChangeUInt16VectorByteOrder " << " i " << std::endl;
#endif		
		
		v_out.resize(v.size());
		
		if (v.size()==1)
		{
	
			uint16_t b1R = (uint16_t)((v[0] & 0xFF00) >> 8);
			uint16_t b1L = (uint16_t)(v[0] & 0x00FF);


			static byte buff[2];

			if (inverse_byte_order)
			{
				buff[byteOrder[1] - '0'] = (byte)b1L;
				buff[byteOrder[0] - '0'] = (byte)b1R;
			}		
			else
			{
				buff[byteOrder[0] - '0'] = (byte)b1L;
				buff[byteOrder[1] - '0'] = (byte)b1R;
			}

			v_out[0] = *(uint16_t *)(buff);
			//printf("in unit16: %x \n",v[0]);

			//printf("unit8: %x %x\n",buff[0], buff[1]);
			
			//printf("out unit16: %x \n",v_out[0]);
			
		}
		else if (v.size()==2)
		{
			
			//--------------------------------------------------------
			// The following 'uint16_t' can be replaced with 'uint8_t':
			//--------------------------------------------------------
			uint16_t b1R = (uint16_t)((v[0] & 0xFF00) >> 8);
			uint16_t b1L = (uint16_t)(v[0] & 0x00FF);


			uint16_t b2R = (uint16_t)((v[1] & 0xFF00) >> 8);
			uint16_t b2L = (uint16_t)(v[1] & 0x00FF);


			static byte buff[4];

			if (inverse_byte_order)
			{
				buff[byteOrder[3] - '0'] = (byte)b1L;
				buff[byteOrder[2] - '0'] = (byte)b1R;
				buff[byteOrder[1] - '0'] = (byte)b2L;
				buff[byteOrder[0] - '0'] = (byte)b2R;
			}		
			else
			{
				buff[byteOrder[0] - '0'] = (byte)b1L;
				buff[byteOrder[1] - '0'] = (byte)b1R;
				buff[byteOrder[2] - '0'] = (byte)b2L;
				buff[byteOrder[3] - '0'] = (byte)b2R;
			}
		

			v_out[0] = *(uint16_t *)(&buff[0]);
			v_out[1] = *(uint16_t *)(&buff[2]);
			
			//printf("in unit16: %x %x\n",v[0], v[1]);

			//printf("unit8: %x %x %x %x\n",buff[0], buff[1] ,buff[2], buff[3]);
			
			//printf("out unit16: %x %x\n",v_out[0], v_out[1]);
			
		}
		else if (v.size()==4)
		{
			
			uint16_t b1R = (uint16_t)((v[0] & 0xFF00) >> 8);
			uint16_t b1L = (uint16_t)(v[0] & 0x00FF);

			uint16_t b2R = (uint16_t)((v[1] & 0xFF00) >> 8);
			uint16_t b2L = (uint16_t)(v[1] & 0x00FF);

			uint16_t b3R = (uint16_t)((v[2] & 0xFF00) >> 8);
			uint16_t b3L = (uint16_t)(v[2] & 0x00FF);

			uint16_t b4R = (uint16_t)((v[3] & 0xFF00) >> 8);
			uint16_t b4L = (uint16_t)(v[3] & 0x00FF);

			static byte buff[4];

			if (inverse_byte_order)
			{
				buff[byteOrder[7] - '0'] = (byte)b1L;
				buff[byteOrder[6] - '0'] = (byte)b1R;
				buff[byteOrder[5] - '0'] = (byte)b2L;
				buff[byteOrder[4] - '0'] = (byte)b2R;
				buff[byteOrder[3] - '0'] = (byte)b3L;
				buff[byteOrder[2] - '0'] = (byte)b3R;
				buff[byteOrder[1] - '0'] = (byte)b4L;
				buff[byteOrder[0] - '0'] = (byte)b4R;
			}		
			else
			{
				buff[byteOrder[0] - '0'] = (byte)b1L;
				buff[byteOrder[1] - '0'] = (byte)b1R;
				buff[byteOrder[2] - '0'] = (byte)b2L;
				buff[byteOrder[3] - '0'] = (byte)b2R;
				buff[byteOrder[4] - '0'] = (byte)b3L;
				buff[byteOrder[5] - '0'] = (byte)b3R;
				buff[byteOrder[6] - '0'] = (byte)b4L;
				buff[byteOrder[7] - '0'] = (byte)b4R;

			}

			v_out[0] = *(uint16_t *)(&buff[0]);
			v_out[1] = *(uint16_t *)(&buff[2]);
			v_out[2] = *(uint16_t *)(&buff[4]);
			v_out[3] = *(uint16_t *)(&buff[6]);
			
			//printf("in unit16: %x %x %x %x\n",v[0], v[1] ,v[2], v[3]);
			//printf("unit8: %x %x %x %x %x %x %x %x\n",buff[0], buff[1] ,buff[2], buff[3], buff[4], buff[5], buff[6], buff[7]);
			//printf("out unit16: %x %x %x %x\n",v_out[0], v_out[1] ,v_out[2], v_out[3]);
		}
		
#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ChangeUInt16VectorByteOrder " << " f " << std::endl;
#endif		

	}
	
	
	//============================================================================
	// 
	//============================================================================
	
		// This part is used for simulator_mode in modbus_client.cpp
		// and also for formula conversions
	
	//============================================================================
	// 
	//============================================================================
	
	void ConvertUShortToUInt16Vector(ushort fl, std::vector<uint16_t> &regs16,const std::string &byteOrder)
	{	

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertUShortToUInt16Vector " << " i " << std::endl;
#endif		

		
		uint8_t uint8_arr[sizeof(ushort)]; // a 2 bytes array
		
		*(ushort*)(uint8_arr) = fl; // convert short to bytes

		uint8_t uint8_arr_ordered[sizeof(ushort)]; // a 2 bytes array to re-order

		if (inverse_byte_order)
		{
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[1];
		}	
		else 
		{
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[1];
		}
		
		uint16_t uint_ar;
	
		uint_ar = uint8_arr_ordered[1] | uint8_arr_ordered[0] << 8;
		
		regs16[0] = uint_ar;						
        
#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertUShortToUInt16Vector " << " f " << std::endl;
#endif		

	}
	//============================================================================
	// 
	//============================================================================
	
	void ConvertShortToUInt16Vector(short fl, std::vector<uint16_t> &regs16,const std::string &byteOrder)
	{	

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertShortToUInt16Vector " << " i " << std::endl;
std::cout << "fl " << fl << std::endl;
std::cout << "byteOrder " << byteOrder << std::endl;
std::cout << "regs16.size() " << regs16.size() << std::endl;
for (auto && i:regs16)
  std::cout << "regs16 " << i << std::endl; 
#endif		

		
		uint8_t uint8_arr[sizeof(short)]; // a 2 bytes array
		
		*(short*)(uint8_arr) = fl; // convert short to bytes

		uint8_t uint8_arr_ordered[sizeof(short)]; // a 2 bytes array to re-order

		if (inverse_byte_order)
		{
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[1];
		}	
		else 
		{
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[1];
		}
		
		uint16_t uint_ar;
	
		uint_ar = uint8_arr_ordered[1] | uint8_arr_ordered[0] << 8;
		
		regs16[0] = uint_ar;						
        
#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertShortToUInt16Vector " << " f " << std::endl;
#endif		

	}
	
		//============================================================================
	// 
	//============================================================================
	void ConvertUIntToUInt16Vector(uint fl, std::vector<uint16_t> &regs16,const std::string &byteOrder)
	{						

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertUIntToUInt16Vector " << " i " << std::endl;
#endif		

		uint8_t uint8_arr[sizeof(uint)]; // a 4 bytes array
		
		*(uint*)(uint8_arr) = fl; // convert float to bytes

		uint8_t uint8_arr_ordered[sizeof(uint)]; // a 4 bytes array to re-order
		
		uint16_t uint_ar[2];						

		if (inverse_byte_order)
		{
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[3];
		}
		else 
		{
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[3];
		}
		
		uint_ar[0] = uint8_arr_ordered[1] | uint8_arr_ordered[0] << 8;
		uint_ar[1] = uint8_arr_ordered[3] | uint8_arr_ordered[2] << 8;
		
		regs16[0] = uint_ar[0];
		regs16[1] = uint_ar[1];	
        
#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertUIntToUInt16Vector " << " f " << std::endl;
#endif		

	}
	
	
	//============================================================================
	// 
	//============================================================================
	void ConvertIntToUInt16Vector(int fl, std::vector<uint16_t> &regs16,const std::string &byteOrder)
	{						

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertIntToUInt16Vector " << " i " << std::endl;
#endif		

		uint8_t uint8_arr[sizeof(int)]; // a 4 bytes array
		
		*(int*)(uint8_arr) = fl; // convert float to bytes

		uint8_t uint8_arr_ordered[sizeof(int)]; // a 4 bytes array to re-order
		
		uint16_t uint_ar[2];						

		if (inverse_byte_order)
		{
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[3];
		}
		else 
		{
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[3];
		}
		
		uint_ar[0] = uint8_arr_ordered[1] | uint8_arr_ordered[0] << 8;
		uint_ar[1] = uint8_arr_ordered[3] | uint8_arr_ordered[2] << 8;
		
		regs16[0] = uint_ar[0];
		regs16[1] = uint_ar[1];	
        
#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertIntToUInt16Vector " << " f " << std::endl;
#endif		

	}
	
	//============================================================================
	// 
	//============================================================================
	void ConvertFloatToUInt16Vector(float fl, std::vector<uint16_t> &regs16,const std::string &byteOrder)
	{	

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertFloatToUInt16Vector " << " i " << std::endl;
#endif		
	
		uint8_t uint8_arr[sizeof(float)]; // a 4 bytes array
		
		*(float*)(uint8_arr) = fl; // convert float to bytes

		uint8_t uint8_arr_ordered[sizeof(float)]; // a 4 bytes array to re-order
		
		
		if (inverse_byte_order)
		{
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[3];
		}
		else 
		{
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[3];
		}
		
		uint16_t uint_ar[2];
		
		uint_ar[0] = uint8_arr_ordered[1] | uint8_arr_ordered[0] << 8;
		uint_ar[1] = uint8_arr_ordered[3] | uint8_arr_ordered[2] << 8;
		
		
		regs16[0] = uint_ar[0];
		regs16[1] = uint_ar[1];

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertFloatToUInt16Vector " << " f " << std::endl;
#endif		
								
	}
	
	//============================================================================
	// 
	//============================================================================
	void ConvertDoubleToUInt16Vector(double fl, std::vector<uint16_t> &regs16,const std::string &byteOrder)
	{	


#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertDoubleToUInt16Vector " << " i " << std::endl;
#endif		

		
		uint8_t uint8_arr[sizeof(double)]; // a 8 bytes array
		
		*(double*)(uint8_arr) = fl; // convert double to bytes

		uint8_t uint8_arr_ordered[sizeof(double)]; // a 8 bytes array to re-order
		
		
		if (inverse_byte_order)
		{
			uint8_arr_ordered[byteOrder[7] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[6] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[5] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[4] - '0'] = uint8_arr[3];
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[4];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[5];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[6];
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[7];
		}		
		else 
		{
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[3];
			uint8_arr_ordered[byteOrder[4] - '0'] = uint8_arr[4];
			uint8_arr_ordered[byteOrder[5] - '0'] = uint8_arr[5];
			uint8_arr_ordered[byteOrder[6] - '0'] = uint8_arr[6];
			uint8_arr_ordered[byteOrder[7] - '0'] = uint8_arr[7];
		}
		
		uint16_t uint_ar[4];						
		
		uint_ar[0] = uint8_arr_ordered[1] | uint8_arr_ordered[0] << 8;
		uint_ar[1] = uint8_arr_ordered[3] | uint8_arr_ordered[2] << 8;
		uint_ar[2] = uint8_arr_ordered[5] | uint8_arr_ordered[4] << 8;
		uint_ar[3] = uint8_arr_ordered[7] | uint8_arr_ordered[6] << 8;
		
		regs16[0] = uint_ar[0];
		regs16[1] = uint_ar[1];
		regs16[2] = uint_ar[2];
		regs16[3] = uint_ar[3];
        
#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertDoubleToUInt16Vector " << " f " << std::endl;
#endif		

	}
	
		//============================================================================
	// 
	//============================================================================
	void ConvertULongToUInt16Vector(uint64_t fl, std::vector<uint16_t> &regs16,const std::string &byteOrder)
	{	


#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertULongToUInt16Vector " << " i " << std::endl;
#endif		
		
		uint8_t uint8_arr[sizeof(uint64_t)]; // a 8 bytes array
		
		*(uint64_t*)(uint8_arr) = fl; // convert long to bytes

		uint8_t uint8_arr_ordered[sizeof(uint64_t)]; // a 8 bytes array to re-order
		

		/*
			// This is also another working method.
			unsigned char arr[8];
			
			arr[0]= (int)((fl >> 56) & 0xFF);
			arr[1]= (int)((fl >> 48) & 0xFF);
			arr[2]= (int)((fl >> 40) & 0xFF);
			arr[3]= (int)((fl >> 32) & 0xFF);
			arr[4]= (int)((fl >> 24) & 0xFF);
			arr[5]= (int)((fl >> 16) & 0xFF);
			arr[6]= (int)((fl >> 8) & 0xFF);
			arr[7]= (int)( fl & 0xFF);
			
			uint8_arr_ordered[byteOrder[7] - '0'] = arr[0];
			uint8_arr_ordered[byteOrder[6] - '0'] = arr[1];
			uint8_arr_ordered[byteOrder[5] - '0'] = arr[2];
			uint8_arr_ordered[byteOrder[4] - '0'] = arr[3];
			uint8_arr_ordered[byteOrder[3] - '0'] = arr[4];
			uint8_arr_ordered[byteOrder[2] - '0'] = arr[5];
			uint8_arr_ordered[byteOrder[1] - '0'] = arr[6];
			uint8_arr_ordered[byteOrder[0] - '0'] = arr[7];
		*/
		
		if (inverse_byte_order)
		{
			uint8_arr_ordered[byteOrder[7] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[6] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[5] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[4] - '0'] = uint8_arr[3];
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[4];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[5];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[6];
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[7];
		}
		else 
		{
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[3];
			uint8_arr_ordered[byteOrder[4] - '0'] = uint8_arr[4];
			uint8_arr_ordered[byteOrder[5] - '0'] = uint8_arr[5];
			uint8_arr_ordered[byteOrder[6] - '0'] = uint8_arr[6];
			uint8_arr_ordered[byteOrder[7] - '0'] = uint8_arr[7];
		}
		
		//printf("%x %x %x %x %x %x %x %x\n",arr[0],arr[1],arr[2]
		//       ,arr[3],arr[4],arr[5],arr[6],arr[7]);
		
		uint16_t uint_ar[4];
		
		uint_ar[0] = uint8_arr_ordered[1] | uint8_arr_ordered[0] << 8;
		uint_ar[1] = uint8_arr_ordered[3] | uint8_arr_ordered[2] << 8;
		uint_ar[2] = uint8_arr_ordered[5] | uint8_arr_ordered[4] << 8;
		uint_ar[3] = uint8_arr_ordered[7] | uint8_arr_ordered[6] << 8;				


		regs16[0] = uint_ar[0];
		regs16[1] = uint_ar[1];
		regs16[2] = uint_ar[2];
		regs16[3] = uint_ar[3];				
        
        
#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertULongToUInt16Vector " << " f " << std::endl;
#endif		

	}	
	
	//============================================================================
	// 
	//============================================================================
	void ConvertLongToUInt16Vector(int64_t fl, std::vector<uint16_t> &regs16,const std::string &byteOrder)
	{	

#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertLongToUInt16Vector " << " i " << std::endl;
#endif		

		
		uint8_t uint8_arr[sizeof(int64_t)]; // a 8 bytes array
		
		*(int64_t*)(uint8_arr) = fl; // convert long to bytes

		uint8_t uint8_arr_ordered[sizeof(int64_t)]; // a 8 bytes array to re-order
		

		/*
			// This is also another working method.
			unsigned char arr[8];
			
			arr[0]= (int)((fl >> 56) & 0xFF);
			arr[1]= (int)((fl >> 48) & 0xFF);
			arr[2]= (int)((fl >> 40) & 0xFF);
			arr[3]= (int)((fl >> 32) & 0xFF);
			arr[4]= (int)((fl >> 24) & 0xFF);
			arr[5]= (int)((fl >> 16) & 0xFF);
			arr[6]= (int)((fl >> 8) & 0xFF);
			arr[7]= (int)( fl & 0xFF);
			
			uint8_arr_ordered[byteOrder[7] - '0'] = arr[0];
			uint8_arr_ordered[byteOrder[6] - '0'] = arr[1];
			uint8_arr_ordered[byteOrder[5] - '0'] = arr[2];
			uint8_arr_ordered[byteOrder[4] - '0'] = arr[3];
			uint8_arr_ordered[byteOrder[3] - '0'] = arr[4];
			uint8_arr_ordered[byteOrder[2] - '0'] = arr[5];
			uint8_arr_ordered[byteOrder[1] - '0'] = arr[6];
			uint8_arr_ordered[byteOrder[0] - '0'] = arr[7];
		*/
		
		if (inverse_byte_order)
		{
			uint8_arr_ordered[byteOrder[7] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[6] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[5] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[4] - '0'] = uint8_arr[3];
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[4];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[5];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[6];
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[7];
		}
		else 
		{
			uint8_arr_ordered[byteOrder[0] - '0'] = uint8_arr[0];
			uint8_arr_ordered[byteOrder[1] - '0'] = uint8_arr[1];
			uint8_arr_ordered[byteOrder[2] - '0'] = uint8_arr[2];
			uint8_arr_ordered[byteOrder[3] - '0'] = uint8_arr[3];
			uint8_arr_ordered[byteOrder[4] - '0'] = uint8_arr[4];
			uint8_arr_ordered[byteOrder[5] - '0'] = uint8_arr[5];
			uint8_arr_ordered[byteOrder[6] - '0'] = uint8_arr[6];
			uint8_arr_ordered[byteOrder[7] - '0'] = uint8_arr[7];
		}
		
		//printf("%x %x %x %x %x %x %x %x\n",arr[0],arr[1],arr[2]
		//       ,arr[3],arr[4],arr[5],arr[6],arr[7]);
		
		uint16_t uint_ar[4];
		
		uint_ar[0] = uint8_arr_ordered[1] | uint8_arr_ordered[0] << 8;
		uint_ar[1] = uint8_arr_ordered[3] | uint8_arr_ordered[2] << 8;
		uint_ar[2] = uint8_arr_ordered[5] | uint8_arr_ordered[4] << 8;
		uint_ar[3] = uint8_arr_ordered[7] | uint8_arr_ordered[6] << 8;				


		regs16[0] = uint_ar[0];
		regs16[1] = uint_ar[1];
		regs16[2] = uint_ar[2];
		regs16[3] = uint_ar[3];				
        
#ifdef DEBUG_BYTE_CONVERTER
std::cout << "ConvertLongToUInt16Vector " << " f " << std::endl;
#endif		

	}	


};

#endif
