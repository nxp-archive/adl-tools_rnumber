/*
C-Random.h modified so that cigloo can process it.
*/


/* // This class is never instantiated- it's purely static.  It contains */
/* // multiple RandomObj generators which may be swapped in and out- the */
/* // current generator is then used by the various get functions. */

/* // By default, we set the seed based upon the time. */
void random_create();
void random_set_gate_all ( int state_in );
void random_set_gate ( int state_in, int apply_to_all );

/* // Generated seed (time based). */
unsigned random_init();
/* // Explicitly set seed.  If the value is 0, the time will be used. */
unsigned random_init_from_seed( unsigned seed );

/* // Create a new generator and store its handle. */
/* // This does not select the generator for use. */
int random_add_new_gen();
int random_add_new_gen_with_seed(unsigned seed);
/* // Remove n generators from the end of the list. */
void random_pop_gen(int x);
/* // Specify a new generator to use. */
int  random_set_cur_gen(int x);
/* // Get the current generator handle. */
int random_get_cur_gen();
/* // Return the number of generators that we currently have. */
int random_get_num_gen();

/* // Get a value from the current generator. */
struct RNumber * random_get_rnumber( int size );
unsigned  random_get_integer();
unsigned  random_get_integer_n( unsigned n );
double    random_get_double();

struct RNumber *  random_get_from_range_rnumber( struct RNumber * minimum, struct RNumber * maximum );
unsigned   random_get_from_range_unsigned( unsigned minimum, unsigned maximum );

/* // Load/save the state of the random number generator. */
void random_save (void * os);
void random_load (void * is);
/* // Get/set info about the random number generator. */
void * random_get_state();
void random_set_state( void * state);
/* // Return the offset that the current generator is at. */
unsigned random_get_count();

