/*
 * verbosity.c
 *
 *  Created on: 19-Aug-2011
 *      Author: jkk
 */

#include "verbosity.h"
#include <stdio.h>
#include <stdarg.h>

int print_info(const char *fmt, ...)
{
	va_list arg;
	int res = 0;
	if (g_verbose)
	{
		va_start(arg, fmt);
		res = vprintf(fmt, arg);
		va_end(arg);
	}
	return res;
}
