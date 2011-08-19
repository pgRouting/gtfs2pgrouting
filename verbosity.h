/*
 * verbosity.h
 *
 *  Created on: 19-Aug-2011
 *      Author: jkk
 */

#ifndef VERBOSITY_H_
#define VERBOSITY_H_

extern int g_verbose; // Global variable to be defined by the caller

int print_info(const char *fmt, ...);

#endif /* VERBOSITY_H_ */
