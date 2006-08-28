
EXTRA_DIST = $(MACROS) $(m4data_DATA)

AUTOMAKE_OPTIONS = foreign

MACROS = rnumber.m4

m4datadir = $(datadir)/aclocal
m4data_DATA = $(MACROS)

SUBDIRS = macros include src tests $(PERL) $(BIGLOO) 

# Add in this directory to SUBDIRS when scribe works correctly.
##$(DOC)

bin_SCRIPTS = rnumber-config

# This ensures that aclocal will be run correctly if we touch
# configure.in, then type "make".  What happens is that configure
# captures the state of the variable and substitutes it into the
# final Makefile.
ACLOCAL_AMFLAGS = -I ./macros

# Tags
TAGS_EXE	= btags
TAGS		= .etags
SOURCE_FILES    = $(shell list-sourcefiles.scm)

$(TAGS) : $(SOURCE_FILES)
	./make-tagfile
