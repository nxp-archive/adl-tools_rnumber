## Please update this variable if any new macros are created
MACROS= \
	std-exceptions.m4

EXTRA_DIST = $(m4data_DATA)
EXTRA_DIST = $(MACROS)

m4datadir = $(datadir)/aclocal
m4data_DATA = $(MACROS)

cinstall:
	$(MAKE) install

EXTRA_DIST = $(m4data_DATA)

SUBDIRS = \
	macros \
	doc   \
	src   \
	tests 

bin_SCRIPTS = rnumber-config

m4datadir = $(datadir)/aclocal
m4data_DATA = rnumber.m4

# This is run after the distribution directory is created
# This target is here to remove src/rcparser.yy from the dist
dist-hook:
	rm $(distdir)/src/rvparser.yy

cinstall-am:
	$(MAKE) install-am
