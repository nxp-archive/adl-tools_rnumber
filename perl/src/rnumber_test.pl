: # -*- perl -*-
eval 'exec perl -w -S $0 ${1+"$@"}'
    if 0;

use strict;

print "This is perl.\n";

use lib '.';
use pl_rnumber;

print pl_rnumber::rnumber_cstr(pl_rnumber::rnumber_create_from_unsigned(10)) . "\n";
pl_rnumber::random_create();
pl_rnumber::random_init();
print pl_rnumber::random_get_integer(), "\n";

my $a = pl_rnumber::rnumber_create_from_unsigned(10);
my $b = 10;

print "ref a '", ref($a), "'\n";
print "ref b '", ref($b), "'\n";

my $string = "1234";
my $integer = 10;
my $rnumber = pl_rnumber::rnumber_create_from_unsigned(10);

pl_rnumber::rnumber_predicate_init();

print "string  stringp ", pl_rnumber::stringp($string), " integerp ", pl_rnumber::integerp($string), " rnumberp ", 
    rnumberp($string), "\n";
print "integer stringp ", pl_rnumber::stringp($integer), " integerp ", pl_rnumber::integerp($integer), " rnumberp ",
    rnumberp($integer), "\n";
print "rnumber stringp ", pl_rnumber::stringp($rnumber), " integerp ", pl_rnumber::integerp($rnumber), " rnumberp ", 
    rnumberp($rnumber), "\n";
