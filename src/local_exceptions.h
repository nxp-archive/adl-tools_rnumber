/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
** ===========================================================================
*/
#ifndef local_exceptions_h
#define local_exceptions_h "$Id$"

#include <exception>
#include <string>

namespace std
{
  class logic_error : public exception 
  {
  public:
    explicit logic_error ( const string &what_arg ) :
      what_string ( what_arg ) { };
    virtual const char * what () const throw () 
      {
	return what_string . c_str ();
      }
  private:
    string what_string;
  };

  class invalid_argument : public logic_error 
  {
  public:
    explicit invalid_argument ( const string &what_arg ) :
      logic_error ( what_arg ) {};
  };
  class out_of_range : public logic_error 
  {
  public:
    explicit out_of_range ( const string &what_arg ) :
      logic_error ( what_arg ) {};
  };
  class length_error : public logic_error 
  {
  public:
    explicit length_error ( const string &what_arg ) :
      logic_error ( what_arg ) {};
  };
  class domain_error : public logic_error 
  {
  public:
    explicit domain_error ( const string &what_arg ) :
      logic_error ( what_arg ) {};
  };


  class runtime_error : public exception
  {
  public:
    explicit runtime_error ( const string &what_arg ) :
      what_string ( what_arg ) { };
    virtual const char * what () const throw () 
      {
	return what_string . c_str ();
      }
  private:
    string what_string;
  };

  class range_error : public runtime_error
  {
  public:
    explicit range_error ( const string &what_arg ) :
      runtime_error ( what_arg ) {};
  };
  
  class overflow_error : public runtime_error
  {
  public:
    explicit overflow_error ( const string &what_arg ) :
      runtime_error ( what_arg ) {};
  };
  
  class underflow_error : public runtime_error
  {
  public:
    explicit underflow_error ( const string &what_arg ) :
      runtime_error ( what_arg ) {};
  };
  
}

#endif
