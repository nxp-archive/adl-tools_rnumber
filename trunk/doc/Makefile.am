SUBDIRS = user

webdatadir = $(WEB_HOME)
webdata_DATA = index.html

EXTRA_DIST = index.skb $(webdata_DATA)

CLEANFILES = $(webdata_DATA)

%.html : %.skb
	$(SKRIBE) $^ -o $@

index.html: index.skb

