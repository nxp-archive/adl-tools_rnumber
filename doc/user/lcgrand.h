  LcgRand (unsigned seed = 4937) { sgenrand(seed); };
  /// Specify a seed (initial state).
  void sgenrand (unsigned long seed) { _x = seed & 0xffffffff; };
  /// Generate the next value.
  unsigned long genrand ();
  /// Generate the previous value.
  unsigned long rgenrand ();
  /// Access the state element.
  unsigned long state() const { return _x; };
  /// Save/load state from a binary stream.
  void save(ostream &) const;
  void load(istream &);
