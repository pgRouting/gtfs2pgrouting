/*
 * verbosity.h
 *
 *  Created on: 19-Aug-2011
 *      Author: jkk
 */

#ifndef VERBOSITY_H_
#define VERBOSITY_H_

extern int g_verbose; // Global variable to be defined by the caller

/**
 * @brief Print verbosity along the software, behave like printf
 * 
 * @param fmt String to print
 * @param ... Vardiac arguments as for printf
 * @return int 
 */
int print_info(const char *fmt, ...);

#endif /* VERBOSITY_H_ */
