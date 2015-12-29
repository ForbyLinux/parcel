/*
 * parcel.cpp
 *
 *  Created on: Dec 27, 2015
 *      Author: noah
 */

#include "parcel.h"


Parcel::Parcel()
{
	name = "";
	dependencies = vector<string> ();
	size = 0;
	priority = Normal;
	string version = "";
	string maintainer = "";
	OSType architecture = x86;
	string filename = "";
	description = "";
}

Parcel::~Parcel()
{
	// TODO Auto-generated destructor stub
}

vector<string> parseDependencies (string dependencies)
{
	vector<string> out = vector<string> ();
	string toks;
	for (int i = 0; i < dependencies.size (); i++)
	{
		if (dependencies[i] == ',' and dependencies[i + 1] == ' ')
		{
			out.push_back (toks);
			toks = "";
			i++;
		}
		else
		{
			toks += dependencies[i];
		}
	}
	return out;
}

vector<Parcel> parcels;

void updateParcelData ()
{
	string text = open ("/etc/parcel/parcels");

	vector<string> packages = vector<string> ();

	vector<vector<pair<string, string> > > packagedata = vector<vector<pair<string, string> > > ();
	string toks;
	for (int i = 0; i < text.size (); i++) // sort all the packages
	{
		if (text[i] == '\n' and text[i + 1] == '\n')
		{
			packages.push_back (toks);
			toks = "";
			packagedata.push_back (vector<pair<string, string> > ());
			i++;
		}
		else
		{
			toks += text[i];
		}
	}

	string value = "";
	for (int i = 0; i < packages.size (); i++) // harvest package data
	{
		for (int j = 0; j < packages[i].size (); j++)
		{
			if (packages[i][j] == ':' and packages[i][j + 1] == ' ')
			{
				j++;
				j++;
				while (packages[i][j] != '\n' and j < packages[i].size ())
				{
					value += packages[i][j];
					j++;
				}
				packagedata[i].push_back (make_pair (toks, value));
				toks = "";
				value = "";
			}
			else
			{
				toks += packages[i][j];
			}
		}
	}

	for (int i = 0; i < packagedata.size (); i++) // now we can start parsing it
	{
		Parcel parcel = Parcel ();
		for (int j = 0; j < packagedata[i].size (); j++)
		{
			string opcode = packagedata[i][j].first;
			string value = packagedata[i][j].second;
			if (opcode == "Package")
			{
				parcel.name = value;
			}
			else if (opcode == "Priority")
			{
				parcel.priority = Optional;
			}
			else if (opcode == "Maintainer")
			{
				parcel.maintainer = value;
			}
			else if (opcode == "Architecture")
			{
				if (value == "amd64")
				{
					parcel.architecture = x64;
				}
				else if (value == "i386")
				{
					parcel.architecture = x86;
				}
				else if (value == "all")
				{
					parcel.architecture = All;
				}
				else
				{
					cout << "error: unknown architecture, " << value << endl;
					exit (EXIT_FAILURE);
				}
			}
			else if (opcode == "Version")
			{
				parcel.version = value;
			}
			else if (opcode == "Replaces")
			{
				/*todo
				 * implement replacement protocol
				 */
			}
			else if (opcode == "Depends")
			{
				parcel.dependencies = parseDependencies (value);
			}
			else if (opcode == "Breaks")
			{
				/*todo
				 * implement system to see if soon-to-be broken package is on system.
				 * If it is then remove it.
				 */
			}
			else if (opcode == "Filename")
			{
				parcel.filename = value;
			}
			else if (opcode == "Description")
			{
				parcel.description = value;
			}
			parcels.push_back (parcel);
		}
	}
}
