
#include "simple.h"
#include <iostream>

class Simple 
{
public:
  Simple();
  Simple (int x);
  ~Simple();
  void set_x( int x);
  int get_x();
private:
  int _x;
};

Simple::Simple(): _x(0){ cout << "simple default ctor - this " << this << endl;}
Simple::Simple(int x):_x(x){ cout << "simple ctor from int " << x << " this " << this << endl;}
Simple::~Simple() { cout << "simple dtor this " << this << endl;}
void Simple::set_x(int x) { cout << "simple set_x for " << this << " x " << x << endl;_x = x;}
int Simple::get_x() { cout << "simple get_x for " << this << " x " << _x << endl; return _x;}

struct Simple * simple_create()
{
  return new Simple();
}

void simple_destroy(struct Simple * simple)
{
  delete simple;
}

struct Simple * simple_create_from_int( int x)
{
  return new Simple(x);
}

void simple_set_x(struct Simple * simple, int x) 
{
  simple->set_x(x);
}

int simple_get_x(struct Simple * simple)
{
  return simple->get_x();
}
