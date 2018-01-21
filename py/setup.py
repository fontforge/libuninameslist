#!/usr/bin/env python

from distutils.core import setup
import sys

if sys.version_info >= (3,):
    extra['use_2to3'] = True

setup(
    name='uninameslist',
    version='0.1',
    author="Shriramana Sharma",
    license="BSD-3",
    description='Python wrapper for LibUniNamesList',
    url='https://github.com/fontforge/libuninameslist/releases/',
    py_modules=['uninameslist']
    )

