  unsigned    size() const;
  unsigned    wordCount() const;
  const       unsigned *buffer() const;
  static      unsigned int defaultSize(); /// deprecated, use getDefaultSize()
  static      unsigned int getDefaultSize();
  static void setDefaultSize( unsigned int size );
