#ifndef __STD_MICRO_TYPES_H
#define __STD_MICRO_TYPES_H

#ifndef _SSIZE_T_DECLARED
#define _SSIZE_T_DECLARED
typedef signed long long ssize_t;
#endif
static_assert(sizeof(ssize_t) == 8, "ssize_t expected to be 8 bytes long.");

#ifndef _SIZE_T_DECLARED
#define _SIZE_T_DECLARED
typedef unsigned long long size_t;
#endif
static_assert(sizeof(size_t) == 8, "size_t expected to be 8 bytes long.");

#ifndef _INT64_T_DECLARED
#define _INT64_T_DECLARED
typedef signed long long int64_t;
#endif
static_assert(sizeof(int64_t) == 8, "int64_t expected to be 8 bytes long.");

#ifndef _UINT64_T_DECLARED
#define _UINT64_T_DECLARED
typedef unsigned long long uint64_t;
#endif
static_assert(sizeof(uint64_t) == 8, "uint64_t expected to be 8 bytes long.");

#ifndef _INT32_T_DECLARED
#define _INT32_T_DECLARED
typedef signed int int32_t;
#endif
static_assert(sizeof(int32_t) == 4, "int32_t expected to be 4 bytes long.");

#ifndef _UINT32_T_DECLARED
#define _UINT32_T_DECLARED
typedef unsigned int uint32_t;
#endif
static_assert(sizeof(uint32_t) == 4, "uint32_t expected to be 4 bytes long.");

#ifndef _INT16_T_DECLARED
#define _INT16_T_DECLARED
typedef signed short int16_t;
#endif
static_assert(sizeof(int16_t) == 2, "int16_t expected to be 2 bytes long.");

#ifndef _UINT16_T_DECLARED
#define _UINT16_T_DECLARED
typedef unsigned short uint16_t;
#endif
static_assert(sizeof(uint16_t) == 2, "uint16_t expected to be 2 bytes long.");

#ifndef _INT8_T_DECLARED
#define _INT8_T_DECLARED
typedef signed char int8_t;
#endif
static_assert(sizeof(int8_t) == 1, "int8_t expected to be 1 bytes long.");

#ifndef _UINT8_T_DECLARED
#define _UINT8_T_DECLARED
typedef unsigned char uint8_t;
#endif
static_assert(sizeof(uint8_t) == 1, "uint8_t expected to be 1 bytes long.");

#ifndef _BYTE_T_DECLARED
#define _BYTE_T_DECLARED
typedef unsigned char byte_t;
#endif
static_assert(sizeof(byte_t) == 1, "byte_t expected to be 1 bytes long.");

#endif
