
#include "c-io.h"
#include <strstream>

using namespace std;

void * ss_create()
{
  return new strstream;
}

void ss_ends( void * ss)
{
  strstream * cpp_ss = reinterpret_cast<strstream*>(ss);
  (*cpp_ss)<< ends;
}

char * ss_str( void * ss)
{
  strstream * cpp_ss = reinterpret_cast<strstream*>(ss);
  return cpp_ss->str();
}

void ss_destroy( void * ss)
{
  strstream * cpp_ss = reinterpret_cast<strstream*>(ss);
  delete cpp_ss;
}
