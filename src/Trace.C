#define VERBOSE

#include <unistd.h>

#include "trace.h"

#include <fstream>
#if defined (linux)
#  include <sys/procfs.h>
#else
#  include <procfs.h>
#endif

#include "gccversion.h"
#ifdef STD_CPP
# include <sstream>
#else
# include <strstream.h>
#endif

using namespace std;

bool tracing_blocked = true;
unsigned tracing_level = 0;
ostream * trace_stream = &cout;


ofstream tracing_file;

void tracing_close_file()
{
  tracing_file .close();
}

void set_tracing_file ( const string & filename )
{
  tracing_file . open ( filename . c_str() );
  trace_stream = &tracing_file;
  atexit ( tracing_close_file);
}

#ifdef SunOS

ostream & operator << ( ostream & os, const timestruc_t & x )
{
  os << x . tv_sec << "." << x . tv_nsec;
  return os;
} 

#endif

string get_process_status ()
{
#ifdef SunOS
  pid_t pid = getpid();

# ifdef STD_CPP
  ostringstream ss;
  ss << "/proc/" << pid << "/status";
  ifstream input_file ( s . str() . c_str(), ios::in | ios::binary);
# else
  strstream ss;
  ss << "/proc/" << pid << "/status" << ends;
  string s (ss .str());
  ss . freeze (0);
  ifstream input_file ( s . c_str(), ios::in | ios::binary);
# endif

  pstatus_t status;

  input_file . read ( &status, sizeof (status));

  strstream return_ss;
  return_ss << "brksize " << ::dec << status . pr_brksize << " stksize " << status . pr_stksize
            << " utime " << status . pr_utime << " stime " << status . pr_stime << ends;
  string return_value ( return_ss . str());
  return_ss . freeze ( 0 );
  return return_value;
#endif
  return "";
}
