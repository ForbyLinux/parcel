/*
 * fs.h
 *
 *  Created on: Dec 29, 2015
 *      Author: noah
 */

#ifndef FS_H_
#define FS_H_
#include <string>
#include <fstream>
using namespace std;

void save (string text, string location);
string open (string location);

#endif /* FS_H_ */
