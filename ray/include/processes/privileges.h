/**
 * @file privileges.h
 * @author Stefan Nuernberger [NURNware Technologies - stefan@nurnware.de]
 * @date Di Mär 20 2007
 * @see privileges.c
 * @brief standard privilege levels
 */

#ifndef _privileges_H
#define _privileges_H

#define PRIV_PRIORITY	200

#define NUM_PRIO 		16
#define PRIO_HIGHEST		15
#define PRIO_HIGH		10
#define PRIO_NORMAL		7
#define PRIO_LOW		2
#define PRIO_IDLE		0

typedef UINT8 PRIORITY;
typedef UINT8 PRIVLEVEL;

#endif
