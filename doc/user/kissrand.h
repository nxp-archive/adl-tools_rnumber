  KissRand (unsigned seed = 4937);
  /// Specify a seed.
  void sgenrand (unsigned long seed);
  /// Generate the next value.
  unsigned long genrand ();
  /// Save/load state from a binary stream.
  void save(ostream &) const;
  void load(istream &);
  unsigned count() const { return _count; };
  /// Get/set state of generator.
  KissState getState() const;
  void setState(const KissState &);

