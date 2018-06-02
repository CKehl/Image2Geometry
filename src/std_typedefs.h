#ifndef STD_TYPEDEFS_H_
#define STD_TYPEDEFS_H_

#include <stdint.h>

#ifndef COMPILE_WITH_CUDA

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef struct _uchar2
{
	uchar x,y;
} uchar2;

typedef struct _uchar3
{
	uchar x,y,z;
} uchar3;

typedef struct _uchar4
{
	uchar w,x,y,z;
} uchar4;

typedef struct _int3
{
	int x,y,z;
} int3;

typedef struct _uint3
{
	uint x,y,z;
} uint3;

typedef struct _uint4
{
	uint w,x,y,z;
} uint4;

typedef struct _float3
{
	float x,y,z;
} float3;

typedef struct _double3
{
	double x,y,z;
} double3;

#else
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;
#include <vector_types.h>
#endif

typedef struct _MinMaxD
{
	double min_x, min_y, min_z;
	double max_x, max_y, max_z;
} MinMaxD;

typedef struct _MinMaxF
{
	float min_x, min_y, min_z;
	float max_x, max_y, max_z;
} MinMaxF;

typedef struct _MinMaxUI
{
	uint min_x, min_y, min_z;
	uint max_x, max_y, max_z;
} MinMaxUI;

union int_float_bits_32 {
    int32_t int_bits;
    float float_bits;
};

union int_float_bits_64 {
    int64_t int_bits;
    float float_bits;
};

inline void FloatToUCharA(float tdata, uchar* cdata)
/*
 * Converts a float to a uchar[4] array, having the MSB at 0, LSB at 3; Same as Texture storage in Python Annotation Tool
 */
{
	int32_t temp;
    //memcpy(&temp, &tdata, 4*sizeof(uchar));
    union int_float_bits_32 bits;
    bits.float_bits = tdata;
    temp = bits.int_bits;
	cdata[0] = uchar( ( temp & 0xFF000000 ) >> 24 );
	cdata[1] = uchar( ( temp & 0x00FF0000 ) >> 16 );
	cdata[2] = uchar( ( temp & 0x0000FF00 ) >> 8 );
	cdata[3] = uchar( ( temp & 0x000000FF ) );
}

inline void FloatToCharA(float tdata, char* cdata)
/*
 * Converts a float to a char[4] array, having the MSB at 0, LSB at 3; Same as Texture storage in Python Annotation Tool
 */
{
	int32_t temp;
    //memcpy(&temp, &tdata, 4*sizeof(uchar));
    union int_float_bits_32 bits;
    bits.float_bits = tdata;
    temp = bits.int_bits;
	cdata[0] = char( ( temp & 0xFF000000 ) >> 24 );
	cdata[1] = char( ( temp & 0x00FF0000 ) >> 16 );
	cdata[2] = char( ( temp & 0x0000FF00 ) >> 8 );
	cdata[3] = char( ( temp & 0x000000FF ) );
}

inline void FloatToUCharA64_LSB(float tdata, uchar* cdata)
/*
 * Converts a float to a uchar[8] array, having the LSB at 0, MSB at 7; Opposite Texture storage in Python Annotation Tool
 */
{

	int64_t temp;
    //memcpy(&temp, &tdata, 4*sizeof(uchar));
    union int_float_bits_64 bits;
    bits.float_bits = tdata;
    temp = bits.int_bits;
	cdata[7] = (uchar) ( temp >> 56 );
	cdata[6] = (uchar) ( temp >> 48 );
	cdata[5] = (uchar) ( temp >> 40 );
	cdata[4] = (uchar) ( temp >> 32 );
    cdata[3] = (uchar) ( temp >> 24 );
	cdata[2] = (uchar) ( temp >> 16 );
	cdata[1] = (uchar) ( temp >> 8 );
	cdata[0] = (uchar) ( temp );
}

inline void UCharAToFloat(const uchar* cdata, float* tdata)
/*
 * Converts a uchar[4] array to a float, having the MSB at 0, LSB at 3; Same as Texture storage in Python Annotation Tool
 */
{
	int32_t temp = ( (int32_t(cdata[0]) << 24) + (int32_t(cdata[1]) << 16) + (int32_t(cdata[2]) << 8) + (int32_t(cdata[3]) ) );

    union int_float_bits_32 bits;
    bits.int_bits = temp;
    //return bits.float_bits;
    (*tdata) = bits.float_bits;
}

inline void CharAToFloat(const char* cdata, float* tdata)
/*
 * Converts a char[4] array to a float, having the MSB at 0, LSB at 3; Same as Texture storage in Python Annotation Tool
 */
{
	int32_t temp = ( (int32_t(cdata[0]) << 24) + (int32_t(cdata[1]) << 16) + (int32_t(cdata[2]) << 8) + (int32_t(cdata[3]) ) );

    union int_float_bits_32 bits;
    bits.int_bits = temp;
    //return bits.float_bits;
    (*tdata) = bits.float_bits;
}

inline void UCharAToFloat64_LSB(const uchar* cdata, float* tdata)
/*
 * Converts a uchar[8] array to a float, having the LSB at 0, MSB at 7; Opposite Texture storage in Python Annotation Tool
 */
{

	int64_t temp = ( (int64_t(cdata[7]) << 56) + (int64_t(cdata[6]) << 48) + (int64_t(cdata[5]) << 40) + (int64_t(cdata[4]) << 32) + (int64_t(cdata[3]) << 24) + (int64_t(cdata[2]) << 16) + (int64_t(cdata[1]) << 8) + (int64_t(cdata[0]) ) );

    union int_float_bits_64 bits;
    bits.int_bits = temp;
    //return bits.float_bits;
    (*tdata) = bits.float_bits;
}

inline void IntToUCharA(int idata, uchar* cdata)
{
	cdata[0] = uchar( ( idata & 0xFF000000 ) >> 24 );
	cdata[1] = uchar( ( idata & 0x00FF0000 ) >> 16 );
	cdata[2] = uchar( ( idata & 0x0000FF00 ) >> 8 );
	cdata[3] = uchar( ( idata & 0x000000FF ) );
}

inline void IntToCharA(int idata, char* cdata)
{
	cdata[0] = char( ( idata & 0xFF000000 ) >> 24 );
	cdata[1] = char( ( idata & 0x00FF0000 ) >> 16 );
	cdata[2] = char( ( idata & 0x0000FF00 ) >> 8 );
	cdata[3] = char( ( idata & 0x000000FF ) );
}

inline void UCharAToInt(const uchar* cdata, int* idata)
{
	int32_t temp = ( (int32_t(cdata[0]) << 24) + (int32_t(cdata[1]) << 16) + (int32_t(cdata[2]) << 8) + (int32_t(cdata[3]) ) );
	(*idata) = temp;
}

inline void CharAToInt(const char* cdata, int* idata)
{
	int32_t temp = ( (int32_t(cdata[0]) << 24) + (int32_t(cdata[1]) << 16) + (int32_t(cdata[2]) << 8) + (int32_t(cdata[3]) ) );
	(*idata) = temp;
}

inline void UIntToUCharA(uint uidata, uchar* cdata)
{
	cdata[0] = uchar( ( uidata & 0xFF000000 ) >> 24 );
	cdata[1] = uchar( ( uidata & 0x00FF0000 ) >> 16 );
	cdata[2] = uchar( ( uidata & 0x0000FF00 ) >> 8 );
	cdata[3] = uchar( ( uidata & 0x000000FF ) );
}

inline void UIntToCharA(uint uidata, char* cdata)
{
	cdata[0] = char( ( uidata & 0xFF000000 ) >> 24 );
	cdata[1] = char( ( uidata & 0x00FF0000 ) >> 16 );
	cdata[2] = char( ( uidata & 0x0000FF00 ) >> 8 );
	cdata[3] = char( ( uidata & 0x000000FF ) );
}

inline void UCharAToUInt(const uchar* cdata, uint* uidata)
{
	uint temp = ( (uint(cdata[0]) << 24) + (uint(cdata[1]) << 16) + (uint(cdata[2]) << 8) + (uint(cdata[3]) ) );
	(*uidata) = temp;
}

inline void CharAToUInt(const char* cdata, uint* uidata)
{
	uint temp = ( (uint(cdata[0]) << 24) + (uint(cdata[1]) << 16) + (uint(cdata[2]) << 8) + (uint(cdata[3]) ) );
	(*uidata) = temp;
}

#endif /* STD_TYPEDEFS_H_ */
