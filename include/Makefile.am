

pkginclude_HEADERS = \
	KissRand.h \
	LcgRand.h \
	MtRand.h \
	RNumber.h \
	C-RNumber.h \
	Random.h \
	C-Random.h \
	rnumber_version.h \
	types.h \
	trace.h \
	gccversion.h

TEST=/usr/bin/test
cinstall: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am cinstall-data-am
cinstall-data-am: cinstall-pkgdataDATA cinstall-pkgincludeHEADERS
cinstall-pkgdataDATA: $(pkgdata_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)
	@list='$(pkgdata_DATA)'; for p in $$list; do \
	  if test -f $(srcdir)/$$p; then \
		 x="$(DESTDIR)$(pkgdatadir)/$$p"; \
		 if $(TEST) \! -f $$x -o $$p -nt $$x ; then \
	      echo " $(INSTALL_DATA) $(srcdir)/$$p $$x"; \
	      $(INSTALL_DATA) $(srcdir)/$$p $$x; \
		 fi; \
	  else if test -f $$p; then \
		 x="$(DESTDIR)$(pkgdatadir)/$$p"; \
		 if $(TEST) \! -f $$x -o $$p -nt $$x ; then \
	      echo " $(INSTALL_DATA) $$p $$x"; \
	      $(INSTALL_DATA) $$p $$x; \
		 fi; \
	  fi; fi; \
	done

cinstall-pkgincludeHEADERS: $(pkginclude_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(pkgincludedir)
	@list='$(pkginclude_HEADERS)'; for p in $$list; do \
		if test -f "$$p"; then d= ; else d="$(srcdir)/"; fi; \
		x="$(DESTDIR)$(pkgincludedir)/$$p"; \
		if $(TEST) \! -f $$x -o $$p -nt $$x ; then \
			echo " $(INSTALL_DATA) $$d$$p $$x"; \
			$(INSTALL_DATA) $$d$$p $$x; \
		else :; fi; \
	done

