EXTRA_DIST = $(userwebdata_DATA)

userwebdatadir = $(WEB_HOME)/user
userwebdata_DATA =	user.html \
			user-1.html \
			user-2.html \
			user-3.html \
			user-4.html \
			user-5.html \
			user-6.html 


ps : user.ps

%.html : %.scr
	$(SCRIBE) $(SCRIBEFLAGS) $(SCRIBEVARS) $< -o $@

%.ps : %.dvi
	dvips -o $@ $<

%.dvi : %.tex
	latex $<
	latex $<
	latex $<

%.tex : %.scr
	$(SCRIBE) $(SCRIBEFLAGS) $(SCRIBEVARS) $< -o $@

user.html: user.scr bib.scr user-margin.scr

user.ps: user.scr bib.scr

PROJECT = rnumber
PROJECT_VERSION = $(RNUMBER_VERSION)
USER_TITLE = RNumber
PROJECT_URL = http://www.somerset.sps.mot.com/projects/tools/tlv/$(PROJECT)
PROJECT_EXAMPLE_FTP_SITE = http://www.somerset.sps.mot.com/projects/tools/tlv/$(PROJECT)/examples
USER_URL = $(PROJECT_URL)/user

SCRIBE = scribe
SCRIBEFLAGS =
SCRIBEVARS = --eval "(define *project-url* \"$(PROJECT_URL)\")" \
	--eval "(define *user-dir* \"$(USER_URL)\")" \
	--eval "(define *project-name* \"$(PROJECT)\")" \
	--eval "(define *user-title* \"$(PROJECT)\")" \
	--eval "(define *project-version* \"$(PROJECT_VERSION)\")" \
	--eval "(define *project-example-ftp-site* \"$(PROJECT_EXAMPLE_FTP_SITE)\")" \
