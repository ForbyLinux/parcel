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
#include <cstdio>
#include <cstring>
#include <zlib.h>
#include <zconf.h>
using namespace std;

#include "Type.h"
#include "fs.h"
#include "source.h"
#include "parcel.h"

void update (OSType type);

void parse (string text);

bool inflateGzip ( const std::string& compressedBytes, std::string& uncompressedBytes );

#endif /* UPDATE_H_ */
