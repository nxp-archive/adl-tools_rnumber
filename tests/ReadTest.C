//
// Simple test of reading RNumbers from a stream and
// from a string.
//

#include <unistd.h>
#include <fstream>
#include <string>

#include "RNumber.h"

using namespace std;
using namespace rnumber;

void usage();

int main (int argc,char *argv[])
{
  string fn;

  if (argc < 2) {
    usage();
  }
  int c = 0;
  cout << dec;
  // First, process any options
  while ((c = getopt(argc,argv,"xh?df:")) != EOF) {
    switch (c) {
    case 'x':
      cout << hex;
      break;
    case 'f':
      fn = optarg;
      break;
    case 'h':
    case '?':
      usage ();
      break;
    }
  }

  ifstream in (fn.c_str());
  if (in.fail()) {
	 cout << "Error!  Could not open file '" << fn << "'." << endl;
	 return -1;
  }

  // Run through the file, streaming in RNumbers, until we find that the
  // stream is at EOF.
  cout << "RNumber Read Test.\n" << endl;
  RNumber tmp;
  while (!in.eof()) {
    in >> tmp;
    cout << tmp << endl;
  }
  cout << endl;  

  return 0;
}


// Display help and exit
void usage ()
{
  cerr << "Usage:  ReadTest [options]\n\n"
		 << "        -?       Print this help and exit\n"
		 << "        -h       Print this help and exit\n"
       << "        -x       Set output radix as hex\n"
		 << "        -f       Specify file to parse\n" << endl;
  exit(1);
}

