  void            printToOS( ostream& os ) const;
  ostream&        printWithRadix( ostream& os, Radix = rios, bool prefix=false ) const;
  friend istream& operator>>( istream& is, RNumber& number );
  friend ostream& operator<<( ostream& os, const RNumber& number );
  void            read( istream& is );
  void            write( ostream& os ) const;
