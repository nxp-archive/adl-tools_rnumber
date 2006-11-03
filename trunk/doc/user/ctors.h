    RNumber();
    RNumber( const RNumber& number );
    RNumber( unsigned int number, Sizing sizing = fixed );
    RNumber( unsigned int number, unsigned int size, Sizing sizing = fixed );
    RNumber( const string& number, Sizing sizing = fixed );
    RNumber( const string& number, unsigned int size, Sizing sizing = fixed );
    RNumber( const string& number, Radix radix, Sizing sizing = fixed );
    RNumber( const string& number, unsigned int size, Radix radix, Sizing sizing = fixed );
    RNumber( const RNumber& number, unsigned int size, Sizing sizing = fixed );
    RNumber( unsigned int radix, const string& str, int size = -1 );  /// deprecated 
    RNumber(const unsigned int* numVector, unsigned int wordCount, unsigned int size,
            Sizing sizing = fixed );
    ~RNumber();
