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

This program is updated for Nameslist.txt ver13.0 and ListeDesNoms.txt ver10.0.

For latest release, see: https://github.com/fontforge/libuninameslist/releases

http://sourceforge.net/projects/libuninameslist/files/ is not kept up to date.

Nameslist.txt
The Unicode consortium provides [a file containing annotations on many unicode
characters.](http://www.unicode.org/Public/UNIDATA/NamesList.html) This library
contains a compiled version of this file so that programs can access this data
quickly and easily.

ListeDesNoms.txt
Is a seperate file which is translated from Nameslist.txt and was outdated for
a period of time but was recently updated by a group of developers who have
updated it up to version 10. Contributors to that file are listed in that file.

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
and the header is `<uninameslist.h>`. You can access these fifteen functions:
```c
const char *uniNamesList_name(unsigned long uni);
const char *uniNamesList_annot(unsigned long uni);
const char *uniNamesList_NamesListVersion(void);
These functions are available in libuninameslist-0.4.20140731 and higher
int uniNamesList_blockCount(void);
int uniNamesList_blockNumber(unsigned long uni);
long uniNamesList_blockStart(int uniBlock);
long uniNamesList_blockEnd(int uniBlock);
const char *uniNamesList_blockName(int uniBlock);
These functions are available in libuninameslist-20180408 and higher
int uniNamesList_names2cnt(void);
long uniNamesList_names2val(int count);
int uniNamesList_names2getU(unsigned long uni);
int uniNamesList_names2lnC(int count);
int uniNamesList_names2lnU(unsigned long uni);
const char *uniNamesList_names2anC(int count);
const char *uniNamesList_names2anU(unsigned long uni);
These functions are available in libuninameslist-20200328 and higher
const char *uniNamesList_Languages(unsigned int lang);
const char *uniNamesList_NamesListVersionAlt(unsigned int lang);
const char *uniNamesList_nameAlt(unsigned long uni, unsigned int lang);
const char *uniNamesList_annotAlt(unsigned long uni, unsigned int lang);
int uniNamesList_nameBoth(unsigned long uni, unsigned int lang, const char **str0, const char **strl);
int uniNamesList_annotBoth(unsigned long uni, unsigned int lang, const char **str0, const char **str1);
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

NOTE: If you ran 'make' after running './configure' earlier, you will need to
run 'make clean' to clear-out the earlier libuninameslist library, which is
built without knowledge of the additional library.
```c
make clean
make
```

Installation and Build Instructions
-----------------------------------

Download a tagged release version from https://github.com/fontforge/libuninameslist/releases
```bash
$ wget https://github.com/fontforge/libuninameslist/archive/20200313.tar.gz
$ tar -xzf 20200313.tar.gz
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

If you need to also include libuninameslist-fr, you will want to use:
```bash
$ ./configure --help
$ ./configure --enable-frenchlib
$ make clean
$ make
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

Added Python Wrapper
--------------------

A Python wrapper is provided. To install, run:
```bash
cd py
# May require sudo if you're not using a virtualenv
python setup.py install
```

The build system can optionally also build installable wheels of the package.
To do this, pass `--enable-pylib`. Optionally, also set the `PYTHON` environment
variable to configure which python to use. The configured python must have `pip`,
`setuptools` and the `wheel` packages installed.
```bash
autoreconf -fiv
PYTHON=python2 ./configure --enable-pylib
make
pip install py/dist/*.whl
```

The Python wrapper exposes the following symbols:

 * **version**: documents the version of **libuninameslist**
 * **name(_char_)**: returns the Unicode character name
 * **name2(_char_)**: returns the Unicode normative alias if defined for correcting a character name, else just the name
 * **charactersWithName2**: string holding all characters with normative aliases
 * **annotation(_char_)**: returns all Unicode annotations including aliases and cross-references as provided by NamesList.txt
 * **block(_char_)**: returns the Unicode block a character is in, or by block name
 * **blocks()**: a generator for iterating through all defined Unicode blocks
 * **valid(_char_)**: returns whether the character is valid (defined in Unicode)
 * **uplus(_char_)**: returns the Unicode codepoint for a character in the format U+XXXX for BMP and U+XXXXXX beyond that

Blocks can be iterated over to yield all characters encoded in them.


See Also
--------

- [FontForge Users](https://sourceforge.net/p/fontforge/mailman/fontforge-users/) - Discussion area for users.
- [FontForge](http://github.com/fontforge/fontforge/) - font editor application that this library was made for.
- [UMap](http://umap.sf.net/) - Find unicode characters and copy them to the clipboard.
