
#include "c-io.h"

#include "gccversion.h"
#ifdef STD_CPP
# include <sstream>
#else
# include <strstream>
#endif

using namespace std;

void * ss_create()
{
# ifdef STD_CPP
  return new ostringstream;
# else
  return new strstream;
# endif
}

void ss_ends( void * ss)
{
# ifdef STD_CPP
  // Do nothing.
# else
  strstream * cpp_ss = reinterpret_cast<strstream*>(ss);
  (*cpp_ss)<< ends;
# endif
}

const char * ss_str( void * ss)
{
# ifdef STD_CPP
  ostringstream * cpp_ss = reinterpret_cast<ostringstream*>(ss);  
  return cpp_ss->str().c_str();
# else
  strstream * cpp_ss = reinterpret_cast<strstream*>(ss);
  return cpp_ss->str();
# endif
}

void ss_destroy( void * ss)
{
# ifdef STD_CPP
  ostringstream * cpp_ss = reinterpret_cast<ostringstream*>(ss);
  delete cpp_ss;  
# else
  strstream * cpp_ss = reinterpret_cast<strstream*>(ss);
  delete cpp_ss;
# endif
}
