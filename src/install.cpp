/*
 * install.cpp
 *
 *  Created on: Dec 29, 2015
 *      Author: noah
 */

#include "install.h"


bool isInstalled (Parcel parcel)
{
	string text = open ("/etc/parcel/installed");
	vector<string> packages = vector<string> ();
	string toks;
	for (int i = 0; i < text.size (); i++) // sort all the packages
	{
		if (text[i] == '\n')
		{
			packages.push_back (toks);
			toks = "";
		}
		else
		{
			toks += text[i];
		}
	}

	for (int i = 0; i < packages.size (); i++)
	{
		if (parcel.name + " (" + parcel.version + ")" == packages[i])
		{
			return true;
		}
	}
	return false;
}
