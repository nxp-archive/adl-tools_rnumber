pkglib_LTLIBRARIES = libRNumber.la

libRNumber_la_SOURCES = \
	Trace.C \
	IntIO.C \
	KissRand.C \
	LcgRand.C \
	MtRand.C \
	RNumber.C \
	C-RNumber.C \
	Random.C \
	rnumber_version.C \
	C-Random.C

noinst_HEADERS = \
	rnumber_feature.h

AM_CPPFLAGS = -I$(top_srcdir)/include

cinstall:
	$(MAKE) install

