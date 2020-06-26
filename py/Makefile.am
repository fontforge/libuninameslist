# Makefile.am - Python script automakefile for libuninameslist
# Copyright (C) 2017, Joe Da Silva
# GPL3+
#
# Python doesn't quite follow same conventions as autoconf so
# you need to modify pythondir for your install and uninstall.

EXTRA_DIST = setup.py uninameslist.py
GENERATED = build wheel uninameslist.egg-info dist __pycache

wheel: $(EXTRA_DIST)
	$(PYTHON) $(srcdir)/setup.py sdist --dist-dir wheel bdist_wheel --universal --dist-dir wheel

all-local: wheel

clean-local:
	rm -rf $(GENERATED)

lint:
	pylint $(srcdir)/py

GITIGNOREFILES = $(GENERATED)

-include $(top_srcdir)/git.mk
