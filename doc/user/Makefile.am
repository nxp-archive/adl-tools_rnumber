userwebdatadir = $(WEB_HOME)/user

userwebdata_DATA = user.html \
		user-1.html \
		user-2.html \
		user-3.html \
		user-4.html \
		user-5.html \
		user-6.html \
		user-7.html \
		user-8.html

USER_SOURCE = user.skb bib.scr user-margin.scr bigloo-bindings.skb  c-functions.skb  cpp-classes.skb  perl-bindings.skb \
	ctors.h \
	arithmetic.h	       field-accessors.h  non-member-cond.h  rnumber-c.h		 types.h \
	assign.h	       friends.h	  non-member.h	     rnumber-c-non-allocating.h  unary-cond.h \
	attribute-accessors.h  kissrand.h	  random.h	     signed-cond.h		 unary.h \
	bit-value.h	       lcgrand.h	  random-obj.h	     sizing.h			 value-accessors.h \
	enum.h		       misc-bit.h	  random-stl.h	     streaming-io.h 


EXTRA_DIST = $(USER_SOURCE)

CLEANFILES = $(userwebdata_DATA) s.skr
PROJECT = rnumber
PROJECT_VERSION = $(RNUMBER_VERSION)
USER_TITLE = RNumber
PROJECT_URL = $(WEB_HOME)
PROJECT_EXAMPLE_FTP_SITE = $(WEB_HOME)/examples
USER_URL = $(PROJECT_URL)/user

SKRIBEFLAGS = -I $(srcdir) -B $(srcdir) -S $(srcdir) -P $(srcdir)

SUSER_URL = --eval "\(define *user-dir* \"$(USER_URL)\"\)"
SPROJ_NAME = --eval "\(define *project-name* \"$(PROJECT)\"\)"
SUSER_TITLE = --eval "\(define *user-title* \"$(PROJECT)\"\)"

SPROJ_URL = "(define *project-url* \"$(PROJECT_URL)\")"
SPROJ_VER = "(define *project-version* \"$(PROJECT_VERSION)\")"
SEXAMPLE_FTP = "(define *project-example-ftp-site* \"$(PROJECT_EXAMPLE_FTP_SITE)\")"

ps : user.ps

%.html : %.skb
	echo $(SPROJ_VER) > s.skr
	echo $(SEXAMPLE_FTP) >> s.skr
	$(SKRIBE) $(SKRIBEFLAGS) $< -o $@

%.ps : %.dvi
	dvips -o $@ $<

%.dvi : %.tex
	latex $<
	latex $<
	latex $<

%.tex : %.skb
	echo $(SPROJ_VER) > s.skr
	echo $(SEXAMPLE_FTP) >> s.skr
	$(SCRIBE) $(SCRIBEFLAGS) $< -o $@

user.html: $(USER_SOURCE)

user.ps:  $(USER_SOURCE)

