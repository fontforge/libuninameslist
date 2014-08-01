#ifndef _NAMESLIST_FR_H
# define _NAMESLIST_FR_H

/* This file was generated using the program 'buildnameslist.c' */

struct unicode_block {
	int start, end;
	const char *name;
};

struct unicode_nameannot {
	const char *name, *annot;
};

/* NOTE: Build your program to access UnicodeBlock[], not UnicodeBlock[259] */
/* because newer version of NamesList.txt can have more blocks than before. */
/* To allow for future use of libuninameslist without changing your program */
/* you can test for (UnicodeBlock[i].end>=0x10ffff) to find the last block. */
extern const struct unicode_block UnicodeBlock[259];

/* NOTE: These 2 constants are correct for this version of libuninameslist, */
/* but can change for later versions of NamesList (use as an example guide) */
#define UNICODE_FR_NAME_MAX	105
#define UNICODE_FR_ANNOT_MAX	509
extern const struct unicode_nameannot * const *const UnicodeNameAnnot[];

/* Index by: UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff] */

/* At the beginning of lines (after a tab) within the annotation string, a: */
/*  * should be replaced by a bullet U+2022 */
/*  x should be replaced by a right arrow U+2192 */
/*  : should be replaced by an equivalent U+224D */
/*  # should be replaced by an approximate U+2245 */
/*  = should remain itself */

/* French NamesList (Version 7.0). */
#define LIBUNINAMESLIST_FR_MAJOR	0
#define LIBUNINAMESLIST_FR_MINOR	4

#endif
