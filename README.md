libuninameslist – A Library of Unicode annotation data
======================================================

-   [Description](#description)
-   [Installation and Build instructions](#installation-and-build-instructions)
-   [Changelog](https://raw.github.com/fontforge/libuninameslist/master/ChangeLog)
-   [License](https://raw.github.com/fontforge/libuninameslist/master/LICENSE)
-   [See Also](#see-also)

Description
-----------

This program is updated for Nameslist.txt ver6.2 and ListeDesNoms.txt ver 5.0,
and is available at http://sourceforge.net/projects/libuninameslist/files/

The Unicode consortium provides [a file containing annotations on many unicode
characters.](http://www.unicode.org/Public/UNIDATA/NamesList.html) This library
contains a compiled version of this file so that programs can access these data
easily.

The library contains a very large (sparse) array with one entry for each
unicode code point (U+0000–U+10FFFF). Each entry contains two strings, a name
and an annotation. Either or both may be NULL. The library also contains a
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
>     extern const struct unicode_block UnicodeBlock[124];
>   
>     #define UNICODE_NAME_MAX    94
>     #define UNICODE_ANNOT_MAX   372
>     extern const struct unicode_nameannot * const *const UnicodeNameAnnot[];
>   
>     /* Index by: UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff] */
>   
>     /* At the beginning of lines (after a tab) within the annotation string, a */
>     /*  * should be replaced by a bullet U+2022 */
>     /*  x should be replaced by a right arrow U+2192 */
>     /*  : should be replaced by an equivalent U+224D */
>     /*  # should be replaced by an approximate U+2245 */
>     /*  = should remain itself */

This package consists of one header file and one library file. The header is
`<uninameslist.h>`. To find the name of a given unicode character `uni` use:

>     UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff].name

while the annotation string is:

>     UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff].annot

The name string is in ASCII, while the annotation string is in UTF-8 and is
also intended to be modified slightly by the having any `*` characters which
immediately follow a tab at the start of a line converted to a bullet
character. Etc.

Installation and Build instructions
-----------------------------------

Download the source from the [downloads
page](https://github.com/fontforge/libuninameslist/downloads).
Then:

>     $ tar xf libuninameslist*.tgz
>     $ gunzip libuninameslist*.tgz ; tar xf libuninameslist*.tar
>     $ cd libuninameslist
>     $ configure
>     $ make
>     $ su
>     # make install

See Also
--------

-   [LibUnicodeNames](https://github.com/fontforge/libuninameslist.git)
-   [FontForge](http://fontforge.org/)
-   [UMap](http://umap.sf.net/)
