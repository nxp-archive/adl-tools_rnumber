
EXTRA_DIST = $(MACROS) $(m4data_DATA)

AUTOMAKE_OPTIONS = foreign

MACROS = rnumber.m4

m4datadir = $(datadir)/aclocal
m4data_DATA = $(MACROS)

SUBDIRS = macros include src tests $(PERL) $(BIGLOO) doc examples

bin_SCRIPTS = rnumber-config

AM_CFLAGS = $CFLAGS

# This ensures that aclocal will be run correctly if we touch
# configure.in, then type "make".  What happens is that configure
# captures the state of the variable and substitutes it into the
# final Makefile.
ACLOCAL_AMFLAGS = -I ./macros
