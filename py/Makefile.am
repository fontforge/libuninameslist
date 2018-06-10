# Makefile.am - Python script automakefile for libuninameslist
# Copyright (C) 2017, Joe Da Silva
# GPL3+
#
# Python doesn't quite follow same conventions as autoconf so
# you need to modify pythondir for your install and uninstall.

EXTRA_DIST = setup.py uninameslist.py

all-local:
if HAVE_PYTHON2
	$(LUPYTHON2) setup.py build --build-base $(builddir)/build2 \
		--verbose
endif
if HAVE_PYTHON3
	$(LUPYTHON3) setup.py build --build-base $(builddir)/build3 \
		--verbose
endif

# python still does a build before doing an install
install-exec-hook:
if HAVE_PYTHON2
	$(LUPYTHON2) setup.py build --build-base $(builddir)/build2 \
		install $(PYWRDR2) --verbose
endif
if HAVE_PYTHON3
	$(LUPYTHON3) setup.py build --build-base $(builddir)/build3 \
		install $(PYWRDR3) --verbose
endif

# lacking uninstall... do: python install --record then remove
uninstall-hook:
if HAVE_PYTHON2
	$(LUPYTHON2) setup.py build --build-base $(builddir)/build2 \
		install $(PYWRDR2) --verbose \
		--record $(builddir)/uninameslistfilestoremove.txt
	cat $(builddir)/uninameslistfilestoremove.txt | xargs rm -rf
	rm -rf $(builddir)/uninameslistfilestoremove.txt
endif
if HAVE_PYTHON3
	$(LUPYTHON3) setup.py build --build-base $(builddir)/build3 \
		install $(PYWRDR3) --verbose \
		--record $(builddir)/uninameslistfilestoremove.txt
	cat $(builddir)/uninameslistfilestoremove.txt | xargs rm -rf
	rm -rf $(builddir)/uninameslistfilestoremove.txt
endif

check-local:

clean-local:
if PSWRAP
if HAVE_PYTHON2
	$(LUPYTHON2) $(srcdir)/setup.py clean --all
endif
if HAVE_PYTHON3
	$(LUPYTHON3) $(srcdir)/setup.py clean --all
endif
	rm -rf $(builddir)/build2 $(builddir)/build3
endif

lint:
if PSWRAP
	pylint $(srcdir)/py
endif

