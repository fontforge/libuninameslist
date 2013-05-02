#ifndef _NAMESLIST_H
# define _NAMESLIST_H

/* This file was generated using the program 'buildnameslist.c' */

struct unicode_block {
	int start, end;
	const char *name;
};

struct unicode_nameannot {
	const char *name, *annot;
};

extern const struct unicode_block UnicodeBlock[234];

#define UNICODE_NAME_MAX	83
#define UNICODE_ANNOT_MAX	462
extern const struct unicode_nameannot * const *const UnicodeNameAnnot[];

/* Index by: UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff] */

/* At the beginning of lines (after a tab) within the annotation string, a */
/*  * should be replaced by a bullet U+2022 */
/*  x should be replaced by a right arrow U+2192 */
/*  : should be replaced by an equivalent U+224D */
/*  # should be replaced by an approximate U+2245 */
/*  = should remain itself */

/* Return a pointer to the name for this unicode value */
/* This value points to a constant string inside the library */
const char *uniNamesList_name(unsigned long uni);

/* Return a pointer to the annotations for this unicode value */
/* This value points to a constant string inside the library */
const char *uniNamesList_annot(unsigned long uni);

/* Return a pointer to the Nameslist.txt version number. */
/* This value points to a constant string inside the library */
const char *uniNamesList_NamesListVersion(void);

#endif
