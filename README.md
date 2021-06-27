libuninameslist – A Library of Unicode names and annotation data
================================================================
[![Build Status](https://travis-ci.org/fontforge/libuninameslist.svg?branch=master)](https://travis-ci.org/fontforge/libuninameslist) [![Build status](https://ci.appveyor.com/api/projects/status/qseac73evm9leu0g?svg=true)](https://ci.appveyor.com/project/fontforge/libuninameslist) [![Coverity Scan Build Status](https://scan.coverity.com/projects/793/badge.svg?flat=1)](https://scan.coverity.com/projects/793)

- [Description](#description)
- [Installation and Build Instructions](#installation-and-build-instructions)
- [Changelog](https://raw.github.com/fontforge/libuninameslist/master/ChangeLog)
- [License](https://raw.github.com/fontforge/libuninameslist/master/LICENSE)
- [Added Python Wrapper](#added-python-wrapper)
- [See Also](#see-also)

Description
-----------

This library is updated for Nameslist.txt ver14.0_beta and ListeDesNoms.txt ver13.0
and includes python wrapper 'uninameslist.py'

For latest release, see: https://github.com/fontforge/libuninameslist/releases
For users that do not have autoconf or automake available, select the '-dist-'
version, which does not need you to first run autoreconf or automake

http://sourceforge.net/projects/libuninameslist/files/ is not kept up to date.

Nameslist.txt
The Unicode consortium provides [a file containing annotations on many unicode
characters.](http://www.unicode.org/Public/UNIDATA/NamesList.html) This library
contains a compiled version of this file so that programs can access this data
quickly and easily.

ListeDesNoms.txt
Is a seperate file which is translated from Nameslist.txt and was outdated for
a period of time but was recently updated by a group of developers who have
updated it up to version 13. Contributors to that file are listed in that file.

These libraries contain very large (sparse) arrays with one entry for each
unicode code point (U+0000–U+10FFFF). Each entry contains two strings, a name
and an annotation. Either or both may be NULL. Both libraries also contain a
(much smaller) list of all the Unicode blocks.
```c
struct unicode_block {
    int start, end;
    const char *name;
};

struct unicode_nameannot {
    const char *name, *annot;
};

extern const struct unicode_block UnicodeBlock[???];

#define UNICODE_NAME_MAX    ???
#define UNICODE_ANNOT_MAX   ???
extern const struct unicode_nameannot * const *const UnicodeNameAnnot[];

/* Index by: UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff] */
```

To keep both libraries slightly smaller, the beginning of lines starting with
TAB can be expanded with UTF-8 character substitutions as defined below:
```c
/* At the beginning of lines (after a tab) within the annotation string, a */
/*  * should be replaced by a bullet U+2022 */
/*  x should be replaced by a right arrow U+2192 */
/*  : should be replaced by an equivalent U+224D */
/*  # should be replaced by an approximate U+2245 */
/*  = should remain itself */
```

With the default configure option chosen, this package will install one library
file, one header file, and one library man file. The library is 'libuninameslist',
and the header is `<uninameslist.h>`. You can access these twenty-six functions:
```c
1) const char *uniNamesList_name(unsigned long uni);
2) const char *uniNamesList_annot(unsigned long uni);
3) const char *uniNamesList_NamesListVersion(void);
These functions are available in libuninameslist-0.4.20140731 and higher
4) int uniNamesList_blockCount(void);
5) int uniNamesList_blockNumber(unsigned long uni);
6) long uniNamesList_blockStart(int uniBlock);
7) long uniNamesList_blockEnd(int uniBlock);
8) const char *uniNamesList_blockName(int uniBlock);
These functions are available in libuninameslist-20180408 and higher
9) int uniNamesList_names2cnt(void);
10) long uniNamesList_names2val(int count);
11) int uniNamesList_names2getU(unsigned long uni);
12) int uniNamesList_names2lnC(int count);
13) int uniNamesList_names2lnU(unsigned long uni);
14) const char *uniNamesList_names2anC(int count);
15) const char *uniNamesList_names2anU(unsigned long uni);
These functions are available in libuninameslist-20200413 and higher
16) const char *uniNamesList_Languages(unsigned int lang);
17) const char *uniNamesList_NamesListVersionAlt(unsigned int lang);
18) const char *uniNamesList_nameAlt(unsigned long uni, unsigned int lang);
19) const char *uniNamesList_annotAlt(unsigned long uni, unsigned int lang);
20) int uniNamesList_nameBoth(unsigned long uni, unsigned int lang, const char **str0, const char **strl);
21) int uniNamesList_annotBoth(unsigned long uni, unsigned int lang, const char **str0, const char **str1);
22) int uniNamesList_blockCountAlt(unsigned int lang);
23) long uniNamesList_blockStartAlt(int uniBlock, unsigned int lang);
24) long uniNamesList_blockEndAlt(int uniBlock, unsigned int lang);
25) const char *uniNamesList_blockNameAlt(int uniBlock, unsigned int lang);
26) int uniNamesList_blockNumberBoth(unsigned long uni, unsigned int lang, int *bn0, int *bn1);
```

and for backwards compatibility for older programs that still use it, there is:
```c
UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff].name
```

while the annotation string is:
```c
UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff].annot
```

The name string is in ASCII, while the annotation string is in UTF-8 and is
also intended to be modified slightly by having any `*` characters which
immediately follow a tab at the start of a line to be converted to a bullet
character, etc.

If you choose to install the second library as well, then you will need to
use: './configure --enable-frenchlib'

This library maintains the same 'name' and 'annot' structure, but has function
names with FR so that it is possible to open both libraries at the same time.
The header file for the French library is `<uninameslist-fr.h>`

This library will also be linked to the main libuninameslist so that it can
be used through the main library (as lang=1) for functions 16 to 26.

NOTE: If you ran 'make' after running './configure' earlier, you may need to
run 'make clean' to clear-out the earlier libuninameslist library, which is
built without knowledge of the additional library.
```c
$ make clean
$ make
$ sudo make install
```
for users with smaller systems, or want slightly smaller libraries and have
strip available, you can run:
```c
$ sudo make install-strip
```

Installation and Build Instructions
-----------------------------------

Download a tagged release version from https://github.com/fontforge/libuninameslist/releases
```bash
$ wget https://github.com/fontforge/libuninameslist/archive/20210626.tar.gz
$ tar -xzf 20210626.tar.gz
$ cd libuninameslist
```

or download the latest HEAD from github:
```bash
$ git clone https://github.com/fontforge/libuninameslist.git
$ cd libuninameslist
```

Then build and install the library
```bash
$ autoreconf -i
$ automake
$ ./configure
$ make
$ sudo make install
```

NOTE: Some Distros and Operating Systems may require you to run 'ldconfig' to
recognize LibUniNamesList if you are not rebooting your computer first before
loading another program that depends on LibUniNamesList. To do this, you may
need to run 'ldconfig' in 'su -' mode after you have done 'make install':
```bash
$ su -
# ldconfig
# exit
$
```

NOTE: Users who do not have autoconf and automake available will want to
download the '-dist-' version found in the releases directory.

Optional French Library
-----------------------

The French library was build as a separate library to maintain backwards with
older (...2012) versions of FontForge. If you want to add libuninameslist-fr,
you will want to use:
```bash
$ ./configure --help
$ ./configure --enable-frenchlib
$ make clean
$ make
$ sudo make install
```

NOTE: Some platforms may have trouble when you run 'make check' or 'make'.
For example, the s390x platform had trouble with 'make check', but was okay
with 'make install' and then running 'make check' because the French library
was now installed and visible with -luninameslist-fr when you checked.
Another example, the ARM platform complained of an error with 'make' but was
fine with the later steps of 'make install' and then also 'make check'.
```bash
$ ./configure --help
$ ./configure --enable-frenchlib
$ make clean
$ make
$ sudo make install
$ make check
```
The explanation for this odd 'make' behaviour is that we are building two
libraries at the same time, where the uninameslist library also depends
on the French library, while at the same time older programs (like older
FontForge) would load these independently (the dependency is to allow for
substitutions if/where/when necessary).

Added Python Wrapper
--------------------

A 'uninameslist.py' Python wrapper is provided for users that want quick
NamesList.txt access using python. To do this, you need to first build and
install the library, and then next, install the python wrapper.
```bash
$ ./configure (may need --/prefix=/usr - use --help to see options)
$ make clean
$ make
$ su
# make install
# cd py
# (May require sudo or su if you're not using a virtualenv)
# python setup.py install
# exit
$
```

The build system can optionally also build installable wheels of the package.
To do this, pass `--enable-pylib`. Optionally, also set the `PYTHON` environment
variable to configure which python to use. The configured python must have `pip`,
`setuptools` and the `wheel` packages installed.
```bash
$ autoreconf -fiv
$ PYTHON=python2 ./configure --enable-pylib
$ make
$ su
# make install
# pip install py/dist/*.whl
# exit
$
```

Note, some operating systems may need to use './configure --prefix=/usr'

The Python wrapper exposes the following library functions and symbols:

```python
 * **version**: documents the version of **libuninameslist**
 * **name(_char_)**: returns the Unicode character name
 * **name2(_char_)**: returns the Unicode normative alias if defined for correcting a character name, else just the name
 * **charactersWithName2**: string holding all characters with normative aliases
 * **annotation(_char_)**: returns all Unicode annotations including aliases and cross-references as provided by NamesList.txt
 * **block(_char_)**: returns the Unicode block a character is in, or by block name
 * **blocks()**: a generator for iterating through all defined Unicode blocks
 * **valid(_char_)**: returns whether the character is valid (defined in Unicode)
 * **uplus(_char_)**: returns the Unicode codepoint for a character in the format U+XXXX for BMP and U+XXXXXX beyond that
```

Blocks can be iterated over to yield all characters encoded in them.


See Also
--------

- [FontForge Users](https://sourceforge.net/p/fontforge/mailman/fontforge-users/) - Discussion area for users.
- [FontForge](http://github.com/fontforge/fontforge/) - font editor application that this library was made for.
- [UMap](http://umap.sf.net/) - Find unicode characters and copy them to the clipboard.
