/*
 * main.cpp
 *
 *  Created on: Dec 27, 2015
 *      Author: noah
 */

#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "update.h"
#include "Type.h"
#include "source.h"
#include "parcel.h"



int main (int argc, char **args)
{
	if(geteuid() != 0)
	{
		cout << "error: parcel needs to run as root" << endl;
		return 1;
	}
	parcels = vector<Parcel> ();
	populateSources (); // does what it's called, it populates the source tree

	if (getType () == x64)
	{
		cputype = "amd64";
	}
	else if (getType () == x86)
	{
		cputype = "i386";
	}
	else
	{
		cout << "running on an unsupported system" << endl;
		return 1;
	}

	for (int i = 1; i < argc; i++)
	{
		string opcode = args[i];
		if (opcode == "update")
		{
			update (getType ());
		}
	}
}
