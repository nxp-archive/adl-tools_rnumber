: # -*- perl -*-
eval 'exec perl -w -S $0 ${1+"$@"}'
    if 0;


use lib '../src/';
use rnumber;

print RNumber::rnumber_cstr(RNumber::rnumber_create_from_unsigned(10)) . "\n";
