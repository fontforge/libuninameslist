#!/usr/bin/env python

from setuptools import setup
import sys

setup(
    name='uninameslist',
    version='0.2.0',
    author='Shriramana Sharma',
    author_email='samjnaa@gmail.com',
    license='BSD-3',
    description='Unicode character names, annotation descriptions, and block data. Wrapper for libuninameslist',
    long_description='Quickly fetch unicode character names, annotation descriptions, and block data information as described in unicode.org file NamesList.txt. Users will first need to install C library libuninameslist before using this wrapper utility.',
    keywords='unicode character font name definition annotation description block nameslist',
    classifiers=[
	'Environment :: Console',
	'Intended Audience :: Developers',
	'License :: OSI Approved :: BSD License',
	'Natural Language :: English',
	'Topic :: Software Development :: Documentation',
	'Topic :: Software Development :: Libraries',
	'Topic :: Text Processing :: Fonts',
	'Topic :: Utilities'],
    url='https://github.com/fontforge/libuninameslist/releases/',
    py_modules=['uninameslist']
    )

