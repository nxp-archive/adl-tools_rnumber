/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
**
** perl wrapper for C Wrapper for Random.h
** ===========================================================================
*/
%module example
%{
  /* put headers and other declarations here    */
  %}


// This class is never instantiated- it's purely static.  It contains
// multiple RandomObj generators which may be swapped in and out- the
// current generator is then used by the various get functions.

// By default, we set the seed based upon the time.
extern void random_create();
extern void random_set_gate_all ( int state_in );
extern void random_set_gate ( int state_in, int apply_to_all );

// Generated seed (time based).
extern unsigned random_init();
// Explicitly set seed.  If the value is 0, the time will be used.
extern unsigned random_init_from_seed( unsigned seed );

// Create a new generator and store its handle.
// This does not select the generator for use.
extern int random_add_new_gen();
extern int random_add_new_gen_with_seed(unsigned seed);
// Remove n generators from the end of the list.
extern void random_pop_gen(int x);
// Specify a new generator to use.
extern int  random_set_cur_gen(int x);
// Get the current generator handle.
extern int random_get_cur_gen();
// Return the number of generators that we currently have.
extern int random_get_num_gen();

// Get a value from the current generator.
extern struct RNumber * random_get_rnumber( int size );
extern unsigned  random_get_integer();
extern unsigned  random_get_integer_n( unsigned n );
extern double    random_get_double();

extern struct RNumber *  random_get_from_range_rnumber( struct RNumber * minimum, 
							struct RNumber * maximum );
extern unsigned   random_get_from_range_unsigned( unsigned minimum, unsigned maximum );

// Load/save the state of the random number generator.
extern void random_save (void * os);
extern void random_load (void * is);
// Get/set info about the random number generator.
extern void * random_get_state();
extern void random_set_state( void * state);
// Return the offset that the current generator is at.
extern unsigned random_get_count();

