  RandomObj();
  RandomObj(unsigned);
  RandomObj(const RandomObj &);

  /// Initializes the random number generator.  
  /// The seed is returned.
  unsigned init();
  /// Same as above, except that a seed is supplied.
  /// If the seed is zero, we generate a new seed.
  unsigned init( unsigned seed );
  /// Various functions for getting random data.
  RNumber  getRNumber( unsigned int size );
  unsigned getInteger();
  unsigned getInteger( unsigned n );
  double   getDouble();
  /// Range-based gets.  Handles those awful signed ranges that are still
  /// in Raptor.
  RNumber  getFromRange( const RNumber& minimum, const RNumber& maximum );
  /// Simple unsigned range- min must be less than max.
  unsigned getFromRange( unsigned minimum, unsigned maximum );
  /// Load/save the state of the random number generator.
  void save (ostream &os);
  void load (istream &is);
  /// Get/set info about the random number generator.
  RandState getState() const;
  void setState(const RandState &);
  unsigned getCount();
  /// Gate control.
  void set_gate(bool g);
