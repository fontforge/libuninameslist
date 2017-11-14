# Makefile.am - Python script automakefile for libuninameslist
# Copyright (C) 2017, Joe Da Silva
# GPL3+
#
# Python doesn't quite follow same conventions as autoconf so
# you need to use python to build, install and uninstall.

EXTRA_DIST = setup.py uninameslist.py

all-local:
	cd $(srcdir)
	$(PYTHON) -3 setup.py build \
		--build-base $(shell readlink -f $(builddir))/build \
		--verbose

install-exec-local:
	$(PYTHON) $(srcdir)/setup.py install --verbose

uninstall-local:
	$(PYTHON) $(srcdir)/setup.py uninstall --verbose

# "pythondir" location is correct at /usr/local..., use python uninstall
# uninstall-local:
#	rm -rf $(pythondir)/uninameslist.py*
#	rm -rf $(pythondir)/uninameslist-*egg-info*

clean-local:
if PSWRAP
	$(PYTHON) $(srcdir)/setup.py clean --all
endif
	rm -rf $(builddir)/build

lint:
	pylint $(srcdir)/py

