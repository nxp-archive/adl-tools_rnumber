   /// By default, we set the seed based upon the time.
   Random();

   static void set_gate ( bool state_in,bool apply_to_all = true );
   /// Generated seed (time based).
   static unsigned init();
   /// Explicitly set seed.  If the value is 0, the time will be used.
   static unsigned init( unsigned seed );

   /// Create a new generator and store its handle.
   /// This does not select the generator for use.
   static int      addNewGen();
   static int      addNewGen(unsigned seed);
   /// Remove n generators from the end of the list.
   static void     popGen(int);
   /// Specify a new generator to use.
   static int      setCurGen(int);
   /// Get the current generator handle.
   static int      getCurGen();
   /// Return the number of generators that we currently have.
   static int      getNumGen();

   /// Get a value from the current generator.
   static RNumber  getRNumber( int size );
   static unsigned getInteger();
   static unsigned getInteger( unsigned n );
   static double   getDouble();

   static RNumber  getFromRange( const RNumber& minimum, const RNumber& maximum );
   static unsigned getFromRange( unsigned minimum, unsigned maximum );

   /// Load/save the state of the random number generator.
   static void save (ostream &os);
   static void load (istream &is);
   /// Get/set info about the random number generator.
   static RandState getState();
   static void setState(const RandState &);
   /// Return the offset that the current generator is at.
   static unsigned getCount();
