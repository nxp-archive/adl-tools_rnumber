#ifdef trace_h
#error dont include this file twice. (including from a header file is usually what causes this).
#else
#define trace_h

#ifdef VERBOSE
#define VERBOSE_WAS_DEFINED VERBOSE
#endif

#define VERBOSE

#include <iostream>
#include <string>
// This define is inserted automatically when any of the
// -O compiler options are used.
#ifdef __OPTIMIZE__
#undef VERBOSE
#endif

#ifdef __cplusplus
#ifdef VERBOSE
#define TRACE_LINE (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << __FUNCTION__ << "()" << endl;
#define TRACE_MSG(x) (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << __FUNCTION__ << "() " << x << endl;
#define TRACE_START(x) (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << __FUNCTION__ << "() " << x << flush;
#define TRACE_CONT(x) (*trace_stream) << x << flush;
#define TRACE_END(x) (*trace_stream) << x << endl;
#define GTRACE_LINE if ( !tracing_blocked ) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << __FUNCTION__ << "()" << endl; }
#define GTRACE_MSG(x) if ( !tracing_blocked) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V0(x) if ( trace_level_set( 0 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V1(x) if ( trace_level_set ( 1 ) ) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V2(x) if ( trace_level_set ( 2 ) ) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V3(x) if ( trace_level_set ( 4) ) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V4(x) if ( trace_level_set ( 8 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V5(x) if ( trace_level_set ( 0x10 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V6(x) if ( trace_level_set ( 0x20 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V7(x) if ( trace_level_set ( 0x40 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V8(x) if ( trace_level_set ( 0x80 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V9(x) if ( trace_level_set ( 0x100 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V10(x) if ( trace_level_set (0x200 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V11(x) if ( trace_level_set (0x400 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V12(x) if ( trace_level_SET (0x800 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V13(x) if ( trace_level_set (0x1000)) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V14(x) if ( trace_level_set ( 0x2000 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V15(x) if ( trace_level_set ( 0x4000 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#define V16(x)  if ( trace_level_set ( 0x8000 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#else
//#warning "Tracing is off."
#define TRACE_LINE
#define TRACE_MSG(x)
#define TRACE_START(x)
#define TRACE_CONT(x)
#define TRACE_END(x)
#define GTRACE_LINE
#define GTRACE_MSG(x)
#define V0(x)
#define V1(x)
#define V2(x)
#define V3(x)
#define V4(x)
#define V5(x)
#define V6(x)
#define V7(x)
#define V8(x)
#define V9(x)
#define V10(x)
#define V11(x)
#define V12(x)
#define V13(x)
#define V14(x)
#define V15(x)
#define V16(x)  if ( trace_level_set ( 0x8000 )) { (*trace_stream) << __FILE__ << ":" << ::dec << __LINE__ << ":" << \
                      __FUNCTION__ << "() " << x << endl;}
#endif
#endif
 
extern bool tracing_blocked;
extern unsigned tracing_level;
extern std::ostream * trace_stream;

inline void unblock_tracing() { tracing_blocked = false;}
inline void block_tracing() { tracing_blocked = true;}
inline void set_tracing_level(unsigned int x) { tracing_level = x;}
inline unsigned int get_tracing_level () { return tracing_level;}
inline void set_tracing_stream ( std::ostream & os ) { trace_stream = &os;}

void set_tracing_file ( const std::string & filename );
inline bool trace_level_set ( unsigned level ) 
{ 
  return ( ( ( level & tracing_level ) != 0 ) || level == 0 );
}

std::string get_process_status ();

#undef VERBOSE
#ifdef VERBOSE_WAS_DEFINED
#define VERBOSE VERBOSE_WAS_DEFINED
#endif

#endif
