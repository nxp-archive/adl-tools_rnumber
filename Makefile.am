## Please update this variable if any new macros are created
MACROS= \
	std-exceptions.m4 \
	rnumber.m4

EXTRA_DIST = $(MACROS) $(m4data_DATA)

m4datadir = $(datadir)/aclocal
m4data_DATA = $(MACROS)

SUBDIRS = macros include src tests $(PERLBINDINGS) $(BIGLOO) $(DOC)

bin_SCRIPTS = rnumber-config

cinstall:
	@set fnord $(MAKEFLAGS); amf=$$2; \
	dot_seen=no; \
	target=`echo $@ | sed s/-recursive//`; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  echo "Making $$target in $$subdir"; \
	  if test "$$subdir" = "."; then \
	    dot_seen=yes; \
	    local_target="$$target-am"; \
	  else \
	    local_target="$$target"; \
	  fi; \
	  (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done; \
	if test "$$dot_seen" = "no"; then \
	  $(MAKE) $(AM_MAKEFLAGS) "$$target-am" || exit 1; \
	fi; test -z "$$fail"

cinstall-am:
	$(MAKE) install-am

# This ensures that aclocal will be run correctly if we touch
# configure.in, then type "make".  What happens is that configure
# captures the state of the variable and substitutes it into the
# final Makefile.
ACLOCAL_AMFLAGS = @ACLOCAL_FLAGS@
