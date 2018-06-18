# Makefile.am - Python script automakefile for libuninameslist
# Copyright (C) 2017, Joe Da Silva
# GPL3+
#
# Python doesn't quite follow same conventions as autoconf so
# you need to modify pythondir for your install and uninstall.

EXTRA_DIST = setup.py uninameslist.py
GENERATED = dist uninameslist.egg-info

all-local:
	$(PYTHON) setup.py sdist bdist_wheel --verbose

clean-local:
	rm -rf $(GENERATED)

lint:
	pylint $(srcdir)/py

GITIGNOREFILES = $(GENERATED)

-include $(top_srcdir)/git.mk
