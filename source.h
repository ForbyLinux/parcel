/*
 * source.h
 *
 *  Created on: Dec 27, 2015
 *      Author: noah
 */

#ifndef SOURCE_H_
#define SOURCE_H_
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
using namespace std;

extern vector<string> sources;
extern vector<pair<string, string> > versions;

void populateSources ();

#endif /* SOURCE_H_ */
