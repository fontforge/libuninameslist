# Makefile.am - Python script automakefile for libuninameslist
# Copyright (C) 2017, Joe Da Silva
# GPL3+
#
# Python doesn't quite follow same conventions as autoconf so
# you need to modify pythondir for your install and uninstall.

EXTRA_DIST = setup.py uninameslist.py

all-local:
	cd $(srcdir)
	$(PYTHON) setup.py build \
		--build-base $(shell readlink -f $(builddir))/build \
		--verbose

install-exec-local:
	$(PYTHON) setup.py install --install-lib $(PYWRDR) --verbose

# lacking uninstall... do: python install --record then remove
uninstall-local:
	$(PYTHON) setup.py install --install-lib $(PYWRDR) --verbose \
		--record uninameslistfilestoremove.txt
	cat uninameslistfilestoremove.txt | xargs rm -rf
	rm -rf uninameslistfilestoremove.txt

clean-local:
if PSWRAP
	$(PYTHON) $(srcdir)/setup.py clean --all
endif
	rm -rf $(builddir)/build

lint:
	pylint $(srcdir)/py

