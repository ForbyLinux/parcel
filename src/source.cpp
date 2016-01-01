/*
 * source.cpp
 *
 *  Created on: Dec 27, 2015
 *      Author: noah
 */

#include "source.h"

vector<pair<string, pair<string, string> > > versions;

void populateSources ()
{
	versions = vector<pair<string, pair<string, string> > > ();

	vector<string> tmpsources = vector<string> ();
	std::ifstream t("/etc/parcel/sources");
	std::string text((std::istreambuf_iterator<char>(t)),
	                 std::istreambuf_iterator<char>());

	string toks;
	for (int i = 0; i < text.size (); i++)
	{
		if (text[i] == '\n')
		{
			tmpsources.push_back (toks);
			toks = "";
		}
		else if (text[i] == '#')
		{
			while (text[i] != '\n') {i++;}
		}
		else
		{
			toks += text[i];
		}
	}

	for (int i = 0; i < tmpsources.size (); i++)
	{
		vector<string> parts = vector<string> ();
		for (int j = 0; j < tmpsources[i].size (); j++) // break each line into pieces
		{
			if (tmpsources[i][j] == ' ')
			{
				parts.push_back (toks);
				toks = "";
			}
			else if (j == tmpsources[i].size () - 1)
			{
				toks += tmpsources[i][j];
				parts.push_back (toks);
				toks = "";
			}
			else if (tmpsources[i][j] == '#')
			{
				while (tmpsources[i][j] != '\n') {j++;}
			}
			else
			{
				toks += tmpsources[i][j];
			}
		}

		for (int j = 0; j < parts.size (); j++)
		{
			string opcode = parts[j];
			if (opcode == "@debian") // we're dealing with a debian mirror
			{
				if (j + 3 < parts.size ())
				{
					j++;
					string url = parts[j];
					j++;
					string tmp = parts[j];
					j++;
					while (j < parts.size ())
					{
						versions.push_back (make_pair (url, make_pair (tmp, parts[j])));
						j++;
					}
					//break; // this may or may not be terrible design, when we pass the while loop we need to go back to the parent loop
				}
			}
		}
	}
}
