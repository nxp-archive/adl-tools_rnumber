#define VERBOSE

#include "trace.h"

#include <fstream>
#if defined (linux)
#  include <sys/procfs.h>
#else
#  include <procfs.h>
#endif
#include <strstream.h>
#include <unistd.h>


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

#if 0
from <sys/procfs.h>
     typedef struct pstatus {
        int          pr_flags;      /* flags (see below) */
        int          pr_nlwp;       /* number of lwps in the process */
        pid_t        pr_pid;        /* process id */
        pid_t        pr_ppid;       /* parent process id */
        pid_t        pr_pgid;       /* process group id */
        pid_t        pr_sid;        /* session id */
        id_t         pr_aslwpid;    /* lwp-id of the aslwp, if any */
        id_t         pr_agentid;    /* lwp-id of the agent lwp, if any */
        sigset_t     pr_sigpend;    /* set of process pending signals */
        uintptr_t    pr_brkbase;    /* virtual address of the process heap */
        size_t       pr_brksize;    /* size of the process heap, in bytes */
        uintptr_t    pr_stkbase;    /* virtual address of the process stack */
        size_t       pr_stksize;    /* size of the process stack, in bytes */
        timestruc_t  pr_utime;      /* process user cpu time */
        timestruc_t  pr_stime;      /* process system cpu time */
        timestruc_t  pr_cutime;     /* sum of children's user times */
        timestruc_t  pr_cstime;     /* sum of children's system times */
        sigset_t     pr_sigtrace;   /* set of traced signals */
        fltset_t     pr_flttrace;   /* set of traced faults */
        sysset_t     pr_sysentry;   /* set of system calls traced on entry */
        sysset_t     pr_sysexit;    /* set of system calls traced on exit */
        lwpstatus_t  pr_lwp;        /* status of the representative lwp */
     } pstatus_t;
#endif

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

  strstream ss;
  ss << "/proc/" << pid << "/status" << ends;
  string s (ss .str());
  ss . freeze (0);

  ifstream input_file ( s . c_str(), ios::in | ios::binary);

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
