/*****************************************************************************
	
	utilhlpr.h - helper header file to make it compatible with visual studio
	
	-Issam Ali <http://issamsoft.com>

*****************************************************************************/

#ifndef _UTILHELPR_
#define _UTILHELPR_

#include <stdarg.h>
#include <stdio.h>
#include <varargs.h>

#define false   0
#define true    1
#define bool int



#if defined(_MSC_VER) && _MSC_VER < 1900

#define snprintf c99_snprintf
#define vsnprintf c99_vsnprintf

int c99_vsnprintf(char *outBuf, size_t size, const char *format, va_list ap);

int c99_snprintf(char *outBuf, size_t size, const char *format, ...);

#endif

#endif
