/*
 * update.cpp
 *
 *  Created on: Dec 27, 2015
 *      Author: noah
 */

#include "update.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}



int bunzip(FILE *f, string &out)
{
	int bzError;
	BZFILE *bzf;
	char buf[4096];

	bzf = BZ2_bzReadOpen(&bzError, f, 0, 0, NULL, 0);
	if (bzError != BZ_OK)
	{
		fprintf(stderr, "E: BZ2_bzReadOpen: %d\n", bzError);
		return -1;
	}

	while (bzError == BZ_OK)
	{
		int nread = BZ2_bzRead(&bzError, bzf, buf, sizeof buf);
		if (bzError == BZ_OK || bzError == BZ_STREAM_END)
		{
			size_t nwritten = 0;
			for (int i = 0; i < nread; i++)
			{
				out += buf[i];
				nwritten++;
			}
			if (nwritten != (size_t) nread)
			{
				fprintf(stderr, "E: short write\n");
				return -1;
			}
		}
	}
	out.erase (out.size () - 1); // trim last \n character from the list
	if (bzError != BZ_STREAM_END)
	{
		fprintf(stderr, "E: bzip error after read: %d\n", bzError);
		return -1;
	}

	BZ2_bzReadClose(&bzError, bzf);
	return 0;
}

void update(OSType type)
{
	string text = "";
	for (int j = 0; j < versions.size (); j++)
	{
		for (int i = 0; i < sources.size(); i++)
		{
			string url = sources[i] + "/dists/" + versions[j].first + "/" + versions[j].second + "/binary-" + cputype + "/Packages.bz2";
			cout << "Downloading list: " << versions[j].first << " " << versions[j].second << " @" << sources[i] << endl;
			CURL *curl;
			FILE *fp;
			CURLcode res;
			string outfilename = "/tmp/Package";
			curl = curl_easy_init();
			if (curl)
			{
				fp = fopen(outfilename.c_str(), "wb");
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
				res = curl_easy_perform(curl);
				/* always cleanup */
				curl_easy_cleanup(curl);
				fclose(fp);
				FILE *bzFile = fopen(outfilename.c_str(), "rb");
				bunzip(bzFile, text); // unzip the bzip2 package file
				fclose(bzFile);
				break;
			}
		}
	}
	save (text, "/etc/parcel/parcels");
}
