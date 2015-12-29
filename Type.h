/*
 * Type.h
 *
 *  Created on: Dec 27, 2015
 *      Author: noah
 */

#ifndef TYPE_H_
#define TYPE_H_
#include <string>
#include <cstdio>
using namespace std;

extern string cputype;

typedef enum
{
	x86,
	x64,
	All
} OSType;

OSType getType ();

#endif /* TYPE_H_ */
