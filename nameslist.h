#ifndef _NAMESLIST_H
# define _NAMESLIST_H

struct unicode_block {
    int start, end;
    const char *name;
};

struct unicode_nameannot {
    const char *name, *annot;
};

extern const struct unicode_block UnicodeBlock[211];

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

#endif
