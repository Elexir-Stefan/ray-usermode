/**
 * @file arguments.h
 * @author Stefan Nuernberger [NURNware Technologies - stefan@nurnware.de]
 * @date Di Mär 20 2007
 * @see arguments.c
 * @brief Used to pass arbitrary count of arguments
 */

#ifndef _arguments_H
#define _arguments_H

typedef struct {
	UINT16 count;
	UINT32 *values;
} PACKED ARGUMENTS;

#endif