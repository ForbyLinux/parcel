/*
 * Type.cpp
 *
 *  Created on: Dec 27, 2015
 *      Author: noah
 */

#include "Type.h"

string cputype;

OSType getType ()
{
	if (sizeof (size_t) == 8)
		return x64;
	else if (sizeof (size_t) == 4)
		return x86;
}
