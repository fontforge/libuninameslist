#ifndef UN_NAMESLIST_H
# define UN_NAMESLIST_H

/* This file was generated using the program 'buildnameslist.c' */

#ifdef __cplusplus
extern "C" {
#endif

struct unicode_block {
	int start, end;
	const char *name;
};

struct unicode_nameannot {
	const char *name, *annot;
};

/* NOTE: Build your program to access the functions if using multilanguage. */

#define UNICODE_BLOCK_MAX	334
#define UNICODE_EN_BLOCK_MAX	334
extern const struct unicode_block UnicodeBlock[334];

/* NOTE: These 4 constants are correct for this version of libuninameslist, */
/* but can change for later versions of NamesList (use as an example guide) */
#define UNICODE_NAME_MAX	100
#define UNICODE_ANNOT_MAX	633
#define UNICODE_EN_NAME_MAX	88
#define UNICODE_EN_ANNOT_MAX	633
extern const struct unicode_nameannot * const *const UnicodeNameAnnot[];

/* Index by: UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff] */

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
const char *uniNamesList_name(unsigned long uni);

/* Returns pointer to the annotations for this unicode value */
/* This value points to a constant string inside the library */
const char *uniNamesList_annot(unsigned long uni);

/* Return a pointer to the Nameslist.txt version number. */
/* This value points to a constant string inside the library */
const char *uniNamesList_NamesListVersion(void);


/* These functions are available in libuninameslist-0.4.20140731 and higher */

/* Version information for this <uninameslist.h> include file */
#define LIBUNINAMESLIST_MAJOR	1
#define LIBUNINAMESLIST_MINOR	9

/* Return number of blocks in this NamesList (Version 14.0). */
int uniNamesList_blockCount(void);

/* Return block number for this unicode value (-1 if bad unicode value) */
int uniNamesList_blockNumber(unsigned long uni);

/* Return unicode value starting this Unicode block (bad uniBlock = -1) */
long uniNamesList_blockStart(int uniBlock);

/* Return unicode value ending this Unicode block (-1 if bad uniBlock). */
long uniNamesList_blockEnd(int uniBlock);

/* Return a pointer to the blockname for this unicode block. */
/* This value points to a constant string inside the library */
const char * uniNamesList_blockName(int uniBlock);

/* These functions are available in libuninameslist-20180408 and higher */

/* Return count of how many names2 are found in this version of library */
int uniNamesList_names2cnt(void);

/* Return list location for this unicode value. Return -1 if not found. */
int uniNamesList_names2getU(unsigned long uni);

/* Return unicode value with names2 (0<=count<uniNamesList_names2cnt(). */
long uniNamesList_names2val(int count);

/* Stringlength of names2. Use this if you want to truncate annotations */
int uniNamesList_names2lnC(int count);
int uniNamesList_names2lnU(unsigned long uni);

/* Return pointer to start of normalized alias names2 within annotation */
const char *uniNamesList_names2anC(int count);
const char *uniNamesList_names2anU(unsigned long uni);

/* These functions are available in libuninameslist-20200413 and higher */

/* Return language codes available from libraries. 0=English, 1=French. */
const char *uniNamesList_Languages(unsigned int lang);
const char *uniNamesList_NamesListVersionAlt(unsigned int lang);

/* Return pointer to name/annotation for this unicode value using lang. */
/* Return English if language does not have information for this Ucode. */
const char *uniNamesList_nameAlt(unsigned long uni, unsigned int lang);
const char *uniNamesList_annotAlt(unsigned long uni, unsigned int lang);

/* Returns 2 lang pointers to names/annotations for this unicode value, */
/* Return str0=English, and str1=language_version (or NULL if no info). */
int uniNamesList_nameBoth(unsigned long uni, unsigned int lang, const char **str0, const char **strl);
int uniNamesList_annotBoth(unsigned long uni, unsigned int lang, const char **str0, const char **str1);

/* Blocklists won't sync if they are different versions. 0=ok, -1=error */
int uniNamesList_blockCountAlt(unsigned int lang);
long uniNamesList_blockStartAlt(int uniBlock, unsigned int lang);
long uniNamesList_blockEndAlt(int uniBlock, unsigned int lang);
const char *uniNamesList_blockNameAlt(int uniBlock, unsigned int lang);
int uniNamesList_blockNumberBoth(unsigned long uni, unsigned int lang, int *bn0, int *bn1);

#ifdef __cplusplus
}
#endif
#endif
