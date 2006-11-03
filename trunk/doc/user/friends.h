
  friend struct Hash {
      size_t operator()( const RNumber& num ) const;
  };

  friend struct Equal {
      size_t operator()( const RNumber& num1, const RNumber& num2 ) const;
  };
  
  friend  const RNumber add( const RNumber& n1, const RNumber& n2, bool extend );
  friend  const RNumber add( const RNumber& n1, unsigned int n2, bool extend );
  friend  const RNumber subtract( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber subtract( const RNumber& n1, unsigned int n2 );
  friend  const RNumber subtract( unsigned int n1, const RNumber& n2 );
  friend  const RNumber multiply( const RNumber& n1, const RNumber& n2, bool extend );
  friend  const RNumber multiply( const RNumber& n1, unsigned int n2, bool extend );
  friend  const RNumber divide( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber divide( const RNumber& n1, unsigned int n2 );
  friend  const RNumber divide( unsigned int n1, const RNumber& n2 );
  friend  const RNumber mod( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber mod( const RNumber& n1, unsigned int n2 );
  friend  const RNumber mod( unsigned int n1, const RNumber& n2 );
  friend  const RNumber bitWiseAnd( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber bitWiseAnd( const RNumber& n1, unsigned int n2 );
  friend  const RNumber bitWiseOr( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber bitWiseOr( const RNumber& n1, unsigned int n2 );
  friend  const RNumber bitWiseXor( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber bitWiseXor( const RNumber& n1, unsigned int n2 );
  friend  const RNumber leftShift( const RNumber& num, const RNumber& shift, bool extend );
  friend  const RNumber leftShift( const RNumber& num, unsigned int shift, bool extend );
  friend  const RNumber leftShift( unsigned int num, const RNumber& shift, bool extend );
  friend  const RNumber rightShift( const RNumber& num, const RNumber& shift );
  friend  const RNumber rightShift( const RNumber& num, unsigned int shift );
  friend  const RNumber rightShift( unsigned int num, const RNumber& shift );

  friend  bool notEqual( const RNumber& n1, const RNumber& n2 );
  friend  bool notEqual( const RNumber& n1, unsigned int n2 );
  friend  bool equal( const RNumber& n1, const RNumber& n2 );
  friend  bool equal( const RNumber& n1, unsigned int n2 );
  friend  bool lessThan( const RNumber& n1, const RNumber& n2, bool orEqual );
  friend  bool lessThan( const RNumber& n1, unsigned int n2, bool orEqual );
  friend  bool lessThan( unsigned int n1, const RNumber& n2, bool orEqual );
  friend  bool greaterThan( const RNumber& n1, const RNumber& n2, bool orEqual );
  friend  bool greaterThan( const RNumber& n1, unsigned int n2, bool orEqual );
  friend  bool greaterThan( unsigned int n1, const RNumber& n2, bool orEqual );

