#ifndef UN_NAMESLIST_FR_H
# define UN_NAMESLIST_FR_H

/* This file was generated using the program 'buildnameslist.c' */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UN_NAMESLIST_H
struct unicode_block {
	int start, end;
	const char *name;
};

struct unicode_nameannot {
	const char *name, *annot;
};
#endif

/* NOTE: Build your program to access the functions if using multilanguage. */

#define UNICODE_FR_BLOCK_MAX	322
extern const struct unicode_block UnicodeBlockFR[322];
#define UnicodeBlock UnicodeBlockFR

/* NOTE: These 2 constants are correct for this version of libuninameslist, */
/* but can change for later versions of NamesList (use as an example guide) */
#define UNICODE_FR_NAME_MAX	100
#define UNICODE_FR_ANNOT_MAX	609
extern const struct unicode_nameannot * const *const UnicodeNameAnnotFR[];

/* Index by: UnicodeNameAnnotFR[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff] */

/* At the beginning of lines (after a tab) within the annotation string, a: */
/*  * should be replaced by a bullet U+2022 */
/*  % should be replaced by a reference mark U+203B */
/*  x should be replaced by a right arrow U+2192 */
/*  ~ should be replaced by a swung dash U+2053 */
/*  : should be replaced by an equivalent U+2261 */
/*  # should be replaced by an approximate U+2248 */
/*  = should remain itself */

/* Return a pointer to the name for this unicode value */
/* This value points to a constant string inside the library */
const char *uniNamesList_nameFR(unsigned long uni);

/* Returns pointer to the annotations for this unicode value */
/* This value points to a constant string inside the library */
const char *uniNamesList_annotFR(unsigned long uni);

/* Return a pointer to the Nameslist.txt version number. */
/* This value points to a constant string inside the library */
const char *uniNamesList_NamesListVersionFR(void);


/* These functions are available in libuninameslist-0.4.20140731 and higher */

/* Version information for this <uninameslist.h> include file */
#define LIBUNINAMESLIST_FR_MAJOR	1
#define LIBUNINAMESLIST_FR_MINOR	4

/* Return number of blocks in this NamesList (Version 13.1). */
int uniNamesList_blockCountFR(void);

/* Return block number for this unicode value (-1 if bad unicode value) */
int uniNamesList_blockNumberFR(unsigned long uni);

/* Return unicode value starting this Unicode block (bad uniBlock = -1) */
long uniNamesList_blockStartFR(int uniBlock);

/* Return unicode value ending this Unicode block (-1 if bad uniBlock). */
long uniNamesList_blockEndFR(int uniBlock);

/* Return a pointer to the blockname for this unicode block. */
/* This value points to a constant string inside the library */
const char * uniNamesList_blockNameFR(int uniBlock);

#define UnicodeNameAnnot UnicodeNameAnnotFR

/* These functions are available in libuninameslist-20180408 and higher */

/* Return count of how many names2 are found in this version of library */
int uniNamesList_names2cntFR(void);

/* Return list location for this unicode value. Return -1 if not found. */
int uniNamesList_names2getUFR(unsigned long uni);

/* Return unicode value with names2 (0<=count<uniNamesList_names2cnt(). */
long uniNamesList_names2valFR(int count);

/* Stringlength of names2. Use this if you want to truncate annotations */
int uniNamesList_names2lnCFR(int count);
int uniNamesList_names2lnUFR(unsigned long uni);

/* Return pointer to start of normalized alias names2 within annotation */
const char *uniNamesList_names2anCFR(int count);
const char *uniNamesList_names2anUFR(unsigned long uni);

#ifdef __cplusplus
}
#endif
#endif
