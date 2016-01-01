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


bool inflateGzip ( const std::string& compressedBytes, std::string& uncompressedBytes )
{
  if ( compressedBytes.size() == 0 )
  {
    uncompressedBytes = compressedBytes;
    return true ;
  }

  uncompressedBytes.clear() ;

  unsigned full_length = compressedBytes.size();
  unsigned half_length = compressedBytes.size() / 2;

  unsigned uncompLength = full_length ;
  char* uncomp = (char*) calloc( sizeof(char), uncompLength );

  z_stream strm;
  strm.next_in = (Bytef *) compressedBytes.c_str();
  strm.avail_in = compressedBytes.size();
  strm.total_out = 0;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;

  bool done = false ;

  if (inflateInit2(&strm, (16+MAX_WBITS)) != Z_OK) {
    free( uncomp );
    return false;
  }

  while (!done) {
    // If our output buffer is too small
    if (strm.total_out >= uncompLength ) {
      // Increase size of output buffer
      char* uncomp2 = (char*) calloc( sizeof(char), uncompLength + half_length );
      memcpy( uncomp2, uncomp, uncompLength );
      uncompLength += half_length ;
      free( uncomp );
      uncomp = uncomp2 ;
    }

    strm.next_out = (Bytef *) (uncomp + strm.total_out);
    strm.avail_out = uncompLength - strm.total_out;

    // Inflate another chunk.
    int err = inflate (&strm, Z_SYNC_FLUSH);
    if (err == Z_STREAM_END) done = true;
    else if (err != Z_OK)  {
      break;
    }
  }

  if (inflateEnd (&strm) != Z_OK) {
    free( uncomp );
    return false;
  }

  for ( size_t i=0; i<strm.total_out; ++i ) {
    uncompressedBytes += uncomp[ i ];
  }
  free( uncomp );
  return true;
}

void update(OSType type)
{
	string text = "";
	for (int j = 0; j < versions.size (); j++)
	{
			string url = versions[j].first + "/dists/" + versions[j].second.first + "/" + versions[j].second.second + "/binary-" + cputype + "/Packages.gz";
			cout << "Downloading list: " << versions[j].second.first << " " << versions[j].second.second << " @" << versions[j].first << endl;
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
				//FILE *bzFile = fopen(outfilename.c_str(), "rb");
				//bunzip(bzFile, text); // unzip the bzip2 package file
				//fclose(bzFile);
				string compressed = open (outfilename);
				string out;
				inflateGzip (compressed, out);
				text += out;
			}
	}
	updateParcelData ();
	optimize (parcels);
	save (text, "/etc/parcel/parcels");
}
