libuninameslist – A Library of Unicode names and annotation data
================================================================

-   [Description](#description)
-   [Installation and Build instructions](#installation-and-build-instructions)
-   [Changelog](https://raw.github.com/fontforge/libuninameslist/master/ChangeLog)
-   [License](https://raw.github.com/fontforge/libuninameslist/master/LICENSE)
-   [See Also](#see-also)

Description
-----------

This program is updated for Nameslist.txt ver 8.0 and ListeDesNoms.txt ver 7.0.

http://sourceforge.net/projects/libuninameslist/files/ is not kept up to date.

Nameslist.txt
The Unicode consortium provides [a file containing annotations on many unicode
characters.](http://www.unicode.org/Public/UNIDATA/NamesList.html) This library
contains a compiled version of this file so that programs can access this data
quickly and easily.

ListeDesNoms.txt
Is a seperate file which is translated from Nameslist.txt and was outdated for
a period of time but was recently updated by a group of developers who have
updated it up to version 7.0. Contibutors to that file are listed in that file.


These libraries contain very large (sparse) arrays with one entry for each
unicode code point (U+0000–U+10FFFF). Each entry contains two strings, a name
and an annotation. Either or both may be NULL. Both libraries also contain a
(much smaller) list of all the Unicode blocks.

>     struct unicode_block {
>         int start, end;
>         const char *name;
>     };
>
>     struct unicode_nameannot {
>         const char *name, *annot;
>     };
>
>     extern const struct unicode_block UnicodeBlock[???];
>
>     #define UNICODE_NAME_MAX    ???
>     #define UNICODE_ANNOT_MAX   ???
>     extern const struct unicode_nameannot * const *const UnicodeNameAnnot[];
>
>     /* Index by: UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff] */

To keep both libraries slightly smaller, the beginning of lines starting with
TAB can be expanded with UTF-8 character substitutions as defined below:

>     /* At the beginning of lines (after a tab) within the annotation string, a */
>     /*  * should be replaced by a bullet U+2022 */
>     /*  x should be replaced by a right arrow U+2192 */
>     /*  : should be replaced by an equivalent U+224D */
>     /*  # should be replaced by an approximate U+2245 */
>     /*  = should remain itself */

With the default configure option chosen, this package will install one library
file and one header file. The library file is 'libuninameslist', and the header
is `<uninameslist.h>`. You can access these eight functions:

>     const char *uniNamesList_name(unsigned long uni);
>     const char *uniNamesList_annot(unsigned long uni);
>     const char *uniNamesList_NamesListVersion(void);
>     int uniNamesList_blockCount(void);
>     int uniNamesList_blockNumber(unsigned long uni);
>     long uniNamesList_blockStart(int uniBlock);
>     long uniNamesList_blockEnd(int uniBlock);
>     const char *uniNamesList_blockName(int uniBlock);

and for backwards compatibility for older programs that still use it, there is:

>     UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff].name

while the annotation string is:

>     UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff].annot

The name string is in ASCII, while the annotation string is in UTF-8 and is
also intended to be modified slightly by the having any `*` characters which
immediately follow a tab at the start of a line converted to a bullet
character. Etc.

If you choose to install the second library as well, then you will need to
use ./configure --enable-frenchlib
This library only uses the older method at the moment since it is not decided
yet if they should also have there own identical functions as the mainline
Namelist.txt, or if it/they should be accessed through the mainline library
by creating new additional functions 9 to n for accessing this/these other
library/libraries.
The header file the french library is `<uninameslist-fr.h>`

Installation and Build instructions
-----------------------------------

Download a tagged release version from https://github.com/fontforge/libuninameslist/releases

```bash
wget https://github.com/fontforge/libuninameslist/archive/0.5.20150701.tar.gz
tar -xzf 0.5.20150701.tar.gz
$ cd libuninameslist
```

or download the latest HEAD from github:
```bash
$ git clone https://github.com/fontforge/libuninameslist.git;
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
$ ./configure --help
$ ./configure --enable-frenchlib

See Also
--------

-   [FontForge](http://github.com/fontforge/fontforge/) - font editor application that this library was made for
-   [UMap](http://umap.sf.net/) - Find unicode characters and copy them to the clipboard
