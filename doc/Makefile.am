
EXTRA_DIST = $(webdata_DATA)

SUBDIRS = user

webdatadir = $(WEB_HOME)
webdata_DATA = index.html

#EXTRA_DIST = $(TESTS) 

#INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/src

%.html : %.scr
	scribe $^ -o $@

index.html: index.scr

documentation:
