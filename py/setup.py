#!/usr/bin/env python

from setuptools import setup
import sys

setup(
    name='uninameslist',
    version='0.1',
    author='Shriramana Sharma',
    author_email='samjnaa@gmail.com',
    license='BSD-3',
    description='Python wrapper for LibUniNamesList',
    long_description='Provide access to Unicode character names, annotations and block data',
    keywords='unicode name annotation block',
    classifiers=[
	'Environment :: Console',
	'Intended Audience :: Developers',
	'License :: OSI Approved :: BSD License',
	'Natural Language :: English',
	'Topic :: Text Processing :: Fonts',
	'Topic :: Utilities'],
    url='https://github.com/fontforge/libuninameslist/releases/',
    py_modules=['uninameslist']
    )

