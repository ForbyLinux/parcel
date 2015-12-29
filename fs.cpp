/*
 * fs.cpp
 *
 *  Created on: Dec 29, 2015
 *      Author: noah
 */

#include "fs.h"

void save (string text, string location)
{
	ofstream out(location.c_str ());
	out << text;
	out.close();
}

string open (string location)
{
	std::ifstream t(location.c_str ());
	std::string text((std::istreambuf_iterator<char>(t)),
		                 std::istreambuf_iterator<char>());
	return text;
}
