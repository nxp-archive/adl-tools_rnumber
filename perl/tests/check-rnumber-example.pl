: # -*- perl -*-
eval 'exec perl -wS $0 ${1+"$@"}'
    if 0;

##  -w              enable many useful warnings (RECOMMENDED)
##  -S              look for programfile using PATH environment variable

use strict;
#this points to the path where the version of rnumber.pm 
##use lib "/cad/tools/rnumber/1.16.7/lib/rnumber/";
##use lib "/cad/tools/rnumber/1.17.12/lib/rnumber";

system ("./rnumber-example.pl > output");
if (system ("diff rnumber-example.output output")) {
  print "failed";
  return 1;
}

0;
