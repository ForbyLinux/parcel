/*
 * parcel.h
 *
 *  Created on: Dec 27, 2015
 *      Author: noah
 */

#ifndef PARCEL_H_
#define PARCEL_H_
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

#include "Type.h"
#include "fs.h"


typedef enum
{
	Optional,
	Urgent,
	Normal
} Priority;

class Parcel
{
public:
	Parcel();
	virtual ~Parcel();
	string name;
	Priority priority;
	vector<string> dependencies;
	int size;
	string version;
	string maintainer;
	OSType architecture;
	string filename;
	string description;
};

extern vector<Parcel> parcels;

vector<string> parseDependencies (string dependencies);

#endif /* PARCEL_H_ */
