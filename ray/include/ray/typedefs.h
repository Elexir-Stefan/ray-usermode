#ifndef _RAY_TYPEDEFS_H
#define _RAY_TYPEDEFS_H

/* types named by occupied length in bits */
typedef unsigned int UINT32;
typedef unsigned short UINT16;
typedef unsigned char UINT8;
typedef signed int SINT32;
typedef signed short SINT16;
typedef signed char SINT8;
typedef unsigned long long UINT64;
typedef signed long long SINT64;

#define UNUSED __attribute__ ((unused))
#define DONTPROFILE __attribute__ ((no_instrument_function))
#define PACKED __attribute__ ((packed))

typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;
typedef unsigned long long UINT64;

typedef signed char  SINT8;
typedef signed short SINT16;
typedef signed int   SINT32;
typedef signed long long SINT64;

typedef char* String;
typedef const char* CString;

typedef enum {
	FALSE = 0,
	TRUE = 1
} PACKED BOOL;

typedef void* POINTER;
typedef const void* CPOINTER;

#ifndef NULL
#define NULL (POINTER)0
#endif


#endif
