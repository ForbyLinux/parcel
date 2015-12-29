/*
 * update.h
 *
 *  Created on: Dec 27, 2015
 *      Author: noah
 */

#ifndef UPDATE_H_
#define UPDATE_H_
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <curl/curl.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <bzlib.h>
using namespace std;

#include "Type.h"
#include "fs.h"
#include "source.h"
#include "parcel.h"

void update (OSType type);

void parse (string text);

int bunzip (FILE *f, string &out);

#endif /* UPDATE_H_ */
