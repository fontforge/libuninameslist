#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "buildnameslist.h"

#define UNUSED_PARAMETER(x) ((void)x)

/* buildnameslist reads from NamesList.txt and ListeDesNoms.txt which */
/* must be present in the current directory. Then, builds two arrays  */
/* of strings for each unicode character. One array contains the name */
/* of the character, the other holds annotations for each character.  */
/* Outputs nameslist.c containing these two sparse arrays */

/* 2=={English=0, French=1} */
static char *uninames[2][17*65536];
static char *uniannot[2][17*65536];
static struct block { long int start, end; char *name; struct block *next;}
	*head[2]={NULL,NULL}, *final[2]={NULL,NULL};

unsigned max_a, max_n;

static int printcopyright1(FILE *out) {
/* Copyright notice for unicode NamesList.txt - 2016 */
    fprintf( out, "\n/*\n");
    fprintf( out, "The data contained in these arrays were derived from data contained in\n");
    fprintf( out, "NamesList.txt which came from www.unicode.org. Below is the copyright\n");
    fprintf( out, "notice for the information given:\n\n");
    fprintf( out, "Copyright © 1991-2016 Unicode, Inc. All rights reserved.\n");
    fprintf( out, "Distributed under the Terms of Use in http://www.unicode.org/copyright.html.\n");
    fprintf( out, "Permission is hereby granted, free of charge, to any person obtaining a copy\n");
    fprintf( out, "of the Unicode data files and any associated documentation (the \"Data Files\")\n");
    fprintf( out, "or Unicode software and any associated documentation (the \"Software\") to deal\n");
    fprintf( out, "in the Data Files or Software without restriction, including without\n");
    fprintf( out, "limitation the rights to use, copy, modify, merge, publish, distribute,\n");
    fprintf( out, "and/or sell copies of the Data Files or Software, and to permit persons to\n");
    fprintf( out, "whom the Data Files or Software are furnished to do so, provided that (a) the\n");
    fprintf( out, "above copyright notice(s) and this permission notice appear with all copies\n");
    fprintf( out, "of the Data Files or Software, (b) both the above copyright notice(s) and\n");
    fprintf( out, "this permission notice appear in associated documentation, and (c) there is\n");
    fprintf( out, "clear notice in each modified Data File or in the Software as well as in the\n");
    fprintf( out, "documentation associated with the Data File(s) or Software that the data or\n");
    fprintf( out, "software has been modified.\n\n");
    fprintf( out, "THE DATA FILES AND SOFTWARE ARE PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY\n");
    fprintf( out, "KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n");
    fprintf( out, "MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF\n");
    fprintf( out, "THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS\n");
    fprintf( out, "INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT\n");
    fprintf( out, "OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF\n");
    fprintf( out, "USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER\n");
    fprintf( out, "TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE\n");
    fprintf( out, "OF THE DATA FILES OR SOFTWARE.\n\n");
    fprintf( out, "Except as contained in this notice, the name of a copyright holder shall not\n");
    fprintf( out, "be used in advertising or otherwise to promote the sale, use or other dealings\n");
    fprintf( out, "in these Data Files or Software without prior written authorization of the\n");
    fprintf( out, "copyright holder.\n\n");
    fprintf( out, "Unicode and the Unicode logo are trademarks of Unicode, Inc. in the United\n");
    fprintf( out, "States and other countries. All third party trademarks referenced herein are\n");
    fprintf( out, "the property of their respective owners.\n*/\n\n");
    return( 1 );
}

static char *myfgets(char *buf,int bsize,FILE *file) {
    /* NamesList.txt uses CR as a line separator */
    int ch;
    char *pt, *end = buf+bsize-2;

    for ( pt=buf; pt<end && (ch=getc(file))!=EOF && ch!='\n' && ch!='\r'; )
	*pt++ = (char)(ch);
    if ( ch=='\n' || ch=='\r' ) {
	*pt++='\n';
	if ( ch=='\r' ) {
	    ch=getc(file);
	    if ( ch!='\n' )
		ungetc(ch,file);
	}
    }
    if ( pt==buf && ch==EOF )
return( NULL );
    *pt = '\0';
return( buf );
}

static void InitArrays(void) {
    int i,j;
    for (i=0; i<2; i++) for (j=0; j<17*65536; j++) {
	uninames[i][j] = NULL; uniannot[i][j] = NULL;
    }
}

static void FreeArrays(void) {
    int i,j;
    for (i=0; i<2; i++) for (j=0; j<17*65536; j++) {
	free(uninames[i][j]); free(uniannot[i][j]);
    }

    for (i=0; i<2; i++) {
	struct block *temp;
	while ( head[i]!=NULL ) {
	    if ( head[i]->name!=NULL ) free(head[i]->name);
	    temp=head[i]->next; free(head[i]); head[i]=temp;
	}
    }
}

static int ReadNamesList(void) {
    char buffer[2000];
    FILE *nl;
    long int a_char = -1, first, last;
    char *end, *namestart, *pt, *temp;
    struct block *cur;
    int i;
    static char *nameslistfiles[] = { "NamesList.txt", "ListeDesNoms.txt", NULL };
    static char *nameslistlocs[] = {
	"http://www.unicode.org/Public/9.0.0/ucd/NamesList-9.0.0d6.txt",
	"http://hapax.qc.ca/ListeDesNoms-7.0(2014-06-22).txt (latin base char set)"
    };

    buffer[sizeof(buffer)-1]=0;
    for ( i=0; nameslistfiles[i]!=NULL; ++i ) {
	nl = fopen( nameslistfiles[i],"r" );
	if ( nl==NULL ) {
	    fprintf( stderr, "Cannot find %s. Please copy it from\n\t%s\n", nameslistfiles[i], nameslistlocs[i] );
	    goto errorReadNamesListFO;
	}
	while ( myfgets(buffer,sizeof(buffer),nl)!=NULL ) {
	    if ( buffer[0]=='@' ) {
		if ( buffer[1]=='+' && buffer[2]=='\t' ) {
		    /* This is a Notice_line, @+ */
		    if ( a_char>=0 && a_char<(int)(sizeof(uniannot[0])/sizeof(uniannot[0][0])) ) {
			for ( pt=buffer; *pt && *pt!='\r' && *pt!='\n' ; ++pt );
			if ( *pt=='\r' ) *pt='\n';
			if ( uniannot[i][a_char]==NULL )
			    uniannot[i][a_char] = strdup(buffer+2);
			else {
			    temp = (char *)(realloc(uniannot[i][a_char],strlen(uniannot[i][a_char])+strlen(buffer+2)+1));
			    if ( temp==NULL ) goto errorReadNamesList;
			    strcat(temp,buffer+2);
			    uniannot[i][a_char] = temp;
			}
	continue;
		    } else {
		    ;
		    }
		}
		a_char = -1;
		if ( buffer[1]=='@' && buffer[2]=='\t' ) {
		    /* This is a Block_Header {first...last}, @@ */
		    first = strtol(buffer+3,&end,16);
		    if ( *end=='\t' ) {
			namestart = end+1;
			for ( pt=namestart; *pt!='\0' && *pt!='\t' ; ++pt );
			if ( *pt=='\t' ) {
			    *pt = '\0';
			    last = strtol(pt+1,&end,16);
			    if ( last>first ) {
				/* found a block, record info */
				cur = (struct block *)(malloc(sizeof(struct block)));
				if ( cur==NULL ) goto errorReadNamesList;
				cur->start = first;
				cur->end = last;
				cur->name = strdup(namestart);
				if ( final[i]==NULL )
				    head[i] = cur;
				else
				    final[i]->next = cur;
				final[i] = cur;
			    }
			}
		    }
		}
	continue;
	    } else if ( buffer[0]==';' ) {
		/* comment, ignore */
	continue;
	    } else if ( isdigit(buffer[0]) || (buffer[0]>='A' && buffer[0]<='F') ) {
		a_char = strtol(buffer,&end,16);
		if ( *end!='\t' )
	continue;
		else if ( end[1]=='<' )
	continue;
		namestart = end+1;
		for ( pt=namestart; *pt && *pt!='\r' && *pt!='\n' && *pt!='\t' && *pt!=';' ; ++pt );
		*pt = '\0';
		if ( a_char>=0 && a_char<(int)(sizeof(uninames[0])/sizeof(uninames[0][0])) )
		    uninames[i][a_char] = strdup(namestart);
	    } else if ( a_char==-1 ) {
	continue;
	    } else if ( buffer[0]=='\t' && buffer[1]==';' ) {
	continue;		/* comment */
	    } else if ( a_char>=0 && a_char<(int)(sizeof(uniannot[0])/sizeof(uniannot[0][0])) ) {
		for ( pt=buffer; *pt && *pt!='\r' && *pt!='\n' ; ++pt );
		if ( *pt=='\r' ) *pt='\n';
		if ( uniannot[i][a_char]==NULL )
		    uniannot[i][a_char] = strdup(buffer);
		else {
		    temp = (char *)(realloc(uniannot[i][a_char],strlen(uniannot[i][a_char])+strlen(buffer)+1));
		    if ( temp==NULL ) goto errorReadNamesList;
		    strcat(temp,buffer);
		    uniannot[i][a_char] = temp;
		}
	    }
	}
	fclose(nl);
    }
    return( 1 );

errorReadNamesList:
    fprintf( stderr,"Out of memory\n" );
    fclose(nl);
errorReadNamesListFO:
    return( 0 );
}

static void dumpstring(char *str,FILE *out) {
    do {
	putc( '"', out);
	for ( ; *str!='\n' && *str!='\0'; ++str ) {
	    if ( *str=='"' || *str=='\\' )
		putc('\\',out);
	    putc(*str,out);
	}
	if ( *str=='\n' && str[1]!='\0' )
	    fprintf( out, "\\n\"\n\t" );
	else
	    putc('"',out);
	if ( *str=='\n' ) ++str;
    } while ( *str );
}

static int dumpinit(FILE *out, FILE *header, int is_fr) {
    /* is_fr => 0=english, 1=french */
    int i;

    fprintf( out, "#include <stdio.h>\n" );
    if ( is_fr==0 )
	fprintf( out, "#include \"uninameslist.h\"\n\n" );
    else
	fprintf( out, "#include \"uninameslist-fr.h\"\n\n" );

    fprintf( out, "/* This file was generated using the program 'buildnameslist.c' */\n\n" );

    if ( is_fr==0 ) {
	/* default Nameslist.txt language=EN file holds these additional functions */
	printcopyright1(out);
	/* Added functions available in libuninameslist version 0.3 and higher. */
	fprintf( out, "/* Retrieve a pointer to the name of a Unicode codepoint. */\n" );
	fprintf( out, "const char *uniNamesList_name(unsigned long uni) {\n" );
	fprintf( out, "\tconst char *pt=NULL;\n\n" );
	fprintf( out, "\tif (uni<0x110000)\n" );
	fprintf( out, "\t\tpt=UnicodeNameAnnot[uni>>16][(uni>>8)&0xff][uni&0xff].name;\n" );
	fprintf( out, "\treturn( pt );\n}\n\n" );
	fprintf( out, "/* Retrieve a pointer to annotation details of a Unicode codepoint. */\n" );
	fprintf( out, "const char *uniNamesList_annot(unsigned long uni) {\n" );
	fprintf( out, "\tconst char *pt=NULL;\n\n" );
	fprintf( out, "\tif (uni<0x110000)\n" );
	fprintf( out, "\t\tpt=UnicodeNameAnnot[uni>>16][(uni>>8)&0xff][uni&0xff].annot;\n" );
	fprintf( out, "\treturn( pt );\n}\n\n" );
	fprintf( out, "/* Retrieve Nameslist.txt version number. */\n" );
	fprintf( out, "const char *uniNamesList_NamesListVersion(void) {\n" );
	fprintf( out, "\treturn( \"Nameslist-Version: %s\" );\n}\n\n", NL_VERSION );
	/* Added functions available in libuninameslist version 0.4 and higher. */
	fprintf( out, "\n/* These functions are available in libuninameslist-0.4.20140731 and higher */\n\n" );
	fprintf( out, "/* Return number of blocks in this NamesList. */\n" );
	fprintf( out, "int uniNamesList_blockCount(void) {\n" );
	fprintf( out, "\treturn( UNICODE_BLOCK_MAX );\n}\n\n" );
	fprintf( out, "/* Return block number for this unicode value, -1 if unlisted unicode value */\n" );
	fprintf( out, "int uniNamesList_blockNumber(unsigned long uni) {\n" );
	fprintf( out, "\tif (uni<0x110000) {\n\t\tint i;\n" );
	fprintf( out, "\t\tfor (i=0; i<UNICODE_BLOCK_MAX; i++) {\n" );
	fprintf( out, "\t\t\tif ( uni<(unsigned long)(UnicodeBlock[i].start) ) break;\n" );
	fprintf( out, "\t\t\tif ( uni<=(unsigned long)(UnicodeBlock[i].end) ) return( i );\n" );
	fprintf( out, "\t\t}\n\t}\n\treturn( -1 );\n}\n\n" );
	fprintf( out, "/* Return unicode value starting this Unicode block (-1 if bad uniBlock). */\n" );
	fprintf( out, "long uniNamesList_blockStart(int uniBlock) {\n" );
	fprintf( out, "\treturn( ((unsigned int)(uniBlock)<UNICODE_BLOCK_MAX ? UnicodeBlock[uniBlock].start : -1) );\n}\n\n" );
	fprintf( out, "/* Return unicode value ending this Unicode block (-1 if bad uniBlock). */\n" );
	fprintf( out, "long uniNamesList_blockEnd(int uniBlock) {\n" );
	fprintf( out, "\treturn( ((unsigned int)(uniBlock)<UNICODE_BLOCK_MAX ? UnicodeBlock[uniBlock].end : -1) );\n}\n\n" );
	fprintf( out, "/* Return a pointer to the blockname for this unicode block. */\n" );
	fprintf( out, "const char *uniNamesList_blockName(int uniBlock) {\n" );
	fprintf( out, "\treturn( ((unsigned int)(uniBlock)<UNICODE_BLOCK_MAX ? UnicodeBlock[uniBlock].name : NULL) );\n}\n\n" );
    }

    fprintf( out, "static const struct unicode_nameannot nullarray[] = {\n" );
    for ( i=0; i<256/4 ; ++i )
	fprintf( out, "\t{ NULL, NULL }, { NULL, NULL }, { NULL, NULL }, { NULL, NULL },\n" );
    fprintf( out, "\t{ NULL, NULL }, { NULL, NULL }, { NULL, NULL }, { NULL, NULL }\n" );
    fprintf( out, "};\n\n" );
    fprintf( out, "static const struct unicode_nameannot nullarray2[] = {\n" );
    for ( i=0; i<256/4 ; ++i )
	fprintf( out, "\t{ NULL, NULL }, { NULL, NULL }, { NULL, NULL }, { NULL, NULL },\n" );
    fprintf( out, "\t{ NULL, NULL }, { NULL, NULL },\n" );
    if ( is_fr ) {
	fprintf( out, "\t{ NULL, \"\t* on est assuré que la valeur ?FFFE n'est en aucune façon un caractère Unicode\" },\n" );
	fprintf( out, "\t{ NULL, \"\t* on est assuré que la valeur ?FFFF n'est en aucune façon un caractère Unicode\" },\n" );
    } else {
	fprintf( out, "\t{ NULL, \"\t* the value ?FFFE is guaranteed not to be a Unicode character at all\" },\n" );
	fprintf( out, "\t{ NULL, \"\t* the value ?FFFF is guaranteed not to be a Unicode character at all\" },\n" );
    }
    fprintf( out, "};\n\n" );
    fprintf( out, "static const struct unicode_nameannot * const nullnullarray[] = {\n" );
    for ( i=0; i<256/8 ; ++i )
	fprintf( out, "\tnullarray, nullarray, nullarray, nullarray, nullarray, nullarray, nullarray, nullarray,\n" );
    fprintf( out, "\tnullarray, nullarray, nullarray, nullarray, nullarray, nullarray, nullarray, nullarray2\n" );
    fprintf( out, "};\n\n" );

    if ( is_fr==1 ) {
	/* default Nameslist.txt language=EN file holds these additional functions */
	fprintf( header, "#ifndef _NAMESLIST_FR_H\n" );
	fprintf( header, "# define _NAMESLIST_FR_H\n\n" );
    } else {
	fprintf( header, "#ifndef _NAMESLIST_H\n" );
	fprintf( header, "# define _NAMESLIST_H\n\n" );
    }
    fprintf( header, "/* This file was generated using the program 'buildnameslist.c' */\n\n" );
    fprintf( header, "#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n" );
    fprintf( header, "struct unicode_block {\n\tint start, end;\n\tconst char *name;\n};\n\n" );
    fprintf( header, "struct unicode_nameannot {\n\tconst char *name, *annot;\n};\n\n" );
    return( 1 );
}

static int dumpend(FILE *header, int is_fr) {
    fprintf( header, "\n/* Index by: UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff] */\n" );
    fprintf( header, "\n/* At the beginning of lines (after a tab) within the annotation string, a: */\n" );
    fprintf( header, "/*  * should be replaced by a bullet U+2022 */\n" );
    fprintf( header, "/*  x should be replaced by a right arrow U+2192 */\n" );
    fprintf( header, "/*  : should be replaced by an equivalent U+224D */\n" );
    fprintf( header, "/*  # should be replaced by an approximate U+2245 */\n" );
    fprintf( header, "/*  = should remain itself */\n\n" );
    if ( is_fr==0 ) {
	/* default Nameslist.txt language=EN file holds these additional functions */
	/* Added functions available in libuninameslist version 0.3 and higher. */
	/* Maintain this sequence for old-programs-binary-backwards-compatibility. */
	fprintf( header, "/* Return a pointer to the name for this unicode value */\n" );
	fprintf( header, "/* This value points to a constant string inside the library */\n" );
	fprintf( header, "const char *uniNamesList_name(unsigned long uni);\n\n" );
	fprintf( header, "/* Return a pointer to the annotations for this unicode value */\n" );
	fprintf( header, "/* This value points to a constant string inside the library */\n" );
	fprintf( header, "const char *uniNamesList_annot(unsigned long uni);\n\n" );
	fprintf( header, "/* Return a pointer to the Nameslist.txt version number. */\n" );
	fprintf( header, "/* This value points to a constant string inside the library */\n" );
	fprintf( header, "const char *uniNamesList_NamesListVersion(void);\n\n" );
	/* Added functions available in libuninameslist version 0.4 and higher. */
	fprintf( header, "\n/* These functions are available in libuninameslist-0.4.20140731 and higher */\n\n" );
	fprintf( header, "/* Version information for this <uninameslist.h> include file */\n" );
	fprintf( header, "#define LIBUNINAMESLIST_MAJOR\t%d\n", LU_VERSION_MJ );
	fprintf( header, "#define LIBUNINAMESLIST_MINOR\t%d\n\n", LU_VERSION_MN );
	fprintf( header, "/* Return number of blocks in this NamesList (Version %s). */\n", NL_VERSION );
	fprintf( header, "int uniNamesList_blockCount(void);\n\n" );
	fprintf( header, "/* Return block number for this unicode value (-1 if bad unicode value) */\n" );
	fprintf( header, "int uniNamesList_blockNumber(unsigned long uni);\n\n" );
	fprintf( header, "/* Return unicode value starting this Unicode block (-1 if bad uniBlock). */\n" );
	fprintf( header, "long uniNamesList_blockStart(int uniBlock);\n\n" );
	fprintf( header, "/* Return unicode value ending this Unicode block (-1 if bad uniBlock). */\n" );
	fprintf( header, "long uniNamesList_blockEnd(int uniBlock);\n\n" );
	fprintf( header, "/* Return a pointer to the blockname for this unicode block. */\n" );
	fprintf( header, "/* This value points to a constant string inside the library */\n" );
	fprintf( header, "const char *uniNamesList_blockName(int uniBlock);\n\n" );
    }
    if ( is_fr==1 ) {
	fprintf( header, "/* French NamesList (Version %s). */\n", NFR_VERSION );
	fprintf( header, "#define LIBUNINAMESLIST_FR_MAJOR\t%d\n", LFR_VERSION_MJ );
	fprintf( header, "#define LIBUNINAMESLIST_FR_MINOR\t%d\n\n", LFR_VERSION_MN );
    }
    fprintf( header, "#ifdef __cplusplus\n}\n#endif\n#endif\n" );
    return( 1 );
}

static int dumpblock(FILE *out, FILE *header, int is_fr ) {
    int bcnt;
    struct block *block;
    unsigned int i, maxa, maxn;

    fprintf( out, "#ifdef __Cygwin\n" );
    fprintf( out, "__declspec(dllexport)\t/* Need this for cygwin to get shared libs */\n" );
    fprintf( out, "#endif /* __Cygwin */\n" );
    fprintf( out, "const struct unicode_block UnicodeBlock[] = {\n" );
    for ( block = head[is_fr], bcnt=0; block!=NULL; block=block->next, ++bcnt ) {
	fprintf( out, "\t{ 0x%x, 0x%x, \"%s\" }%s\n", (unsigned int)(block->start),
		(unsigned int)(block->end), block->name, block->next!=NULL ? "," : "" );
    }
    fprintf( out, "};\n\n" );
    fprintf( header, "/* NOTE: Build your program to access UnicodeBlock[], not UnicodeBlock[%d] */\n", bcnt );
    fprintf( header, "/* because newer version of NamesList.txt can have more blocks than before. */\n" );
    fprintf( header, "/* To allow for future use of libuninameslist without changing your program */\n" );
    fprintf( header, "/* you can test for (UnicodeBlock[i].end>=0x10ffff) to find the last block. */\n" );
    if ( is_fr==0 ) fprintf( header, "#define UNICODE_BLOCK_MAX\t%d\n", bcnt );
    fprintf( header, "extern const struct unicode_block UnicodeBlock[%d];\n", bcnt );

    maxn = maxa = 0;
    for ( i=0; i<sizeof(uniannot[is_fr])/sizeof(uniannot[0][is_fr]); ++i ) {
	if ( uninames[is_fr][i]!=NULL && maxn<strlen(uninames[is_fr][i])) maxn = (unsigned int) strlen(uninames[is_fr][i]);
	if ( uniannot[is_fr][i]!=NULL && maxa<strlen(uniannot[is_fr][i])) maxa = (unsigned int) strlen(uniannot[is_fr][i]);
    }
    if (maxn > max_n ) max_n = maxn;
    if (maxa > max_a ) max_a = maxa;

    fprintf( header, "\n/* NOTE: These %d constants are correct for this version of libuninameslist, */\n", is_fr ? 2: 4 );
    fprintf( header, "/* but can change for later versions of NamesList (use as an example guide) */\n" );
    if ( is_fr==0 ) {
	fprintf( header, "#define UNICODE_NAME_MAX\t%d\n", max_n );
	fprintf( header, "#define UNICODE_ANNOT_MAX\t%d\n", max_a );
	fprintf( header, "#define UNICODE_EN_NAME_MAX\t%d\n", maxn );
	fprintf( header, "#define UNICODE_EN_ANNOT_MAX\t%d\n", maxa );
    }
    if ( is_fr==1 ) {
	fprintf( header, "#define UNICODE_FR_NAME_MAX\t%d\n", maxn );
	fprintf( header, "#define UNICODE_FR_ANNOT_MAX\t%d\n", maxa );
    }
    return( 1 );
}

static int dumparrays(FILE *out, FILE *header, int is_fr ) {
    unsigned int i,j,k,t;
    char *prefix = "una";

    for ( i=0; i<sizeof(uniannot[0])/(sizeof(uniannot[0][0])*65536); ++i ) {	/* For each plane */
	for ( t=0; t<0xFFFE; ++t )
	    if ( uninames[is_fr][(i<<16)+t]!=NULL || uniannot[is_fr][(i<<16)+t]!=NULL )
	break;
	if ( t==0xFFFE )
    continue;		/* Empty plane */
	for ( j=0; j<256; ++j ) {
	    for ( t=0; t<256; ++t ) {
		if ( uninames[is_fr][(i<<16) + (j<<8) + t]!=NULL || uniannot[is_fr][(i<<16) + (j<<8) + t]!=NULL )
	    break;
		else if ( j==0xff && t==0xfe -1 )
	    break;
	    }
	    if ( t==256 || (j==0xff && t==0xfe -1))
	continue;	/* Empty sub-plane */
	    fprintf( out, "static const struct unicode_nameannot %s_%02X_%02X[] = {\n", prefix, i, j );
	    for ( k=0; k<256; ++k ) {
		fprintf( out, "/* %04X */ { ", (i<<16) + (j<<8) + k );
		if ( uninames[is_fr][(i<<16) + (j<<8) + k]==NULL )
		    fprintf( out, "NULL" );
		else
		    dumpstring(uninames[is_fr][(i<<16) + (j<<8) + k],out);
		putc(',',out);
		if ( uniannot[is_fr][(i<<16) + (j<<8) + k]==NULL )
		    fprintf( out, "NULL" );
		else
		    dumpstring(uniannot[is_fr][(i<<16) + (j<<8) + k],out);
		fprintf( out, "}%s\n", k!=255?",":"" );
	    }
	    fprintf( out, "};\n\n" );
	}
    }

    for ( i=0; i<sizeof(uniannot[is_fr])/(sizeof(uniannot[is_fr][0])*65536); ++i ) {	/* For each plane */
	for ( t=0; t<0xFFFE; ++t )
	    if ( uninames[is_fr][(i<<16)+t]!=NULL || uniannot[is_fr][(i<<16)+t]!=NULL )
	break;
	if ( t==0xFFFE )
    continue;		/* Empty plane */
	fprintf( out, "static const struct unicode_nameannot * const %s_%02X[] = {\n", prefix, i );
	for ( j=0; j<256; ++j ) {
	    for ( t=0; t<256; ++t ) {
		if ( uninames[is_fr][(i<<16) + (j<<8) + t]!=NULL || uniannot[is_fr][(i<<16) + (j<<8) + t]!=NULL )
	    break;
		else if ( j==0xff && t==0xfe -1 )
	    break;
	    }
	    if ( t==256 )
		fprintf( out, "\tnullarray%s\n", j!=255?",":"" );
	    else if ( j==0xff && t==0xfe -1 )
		fprintf( out, "\tnullarray2\n" );
	    else
		fprintf( out, "\t%s_%02X_%02X%s\n", prefix, i, j, j!=255?",":"" );
	}
	fprintf( out, "};\n\n" );
    }

    fprintf( header, "extern const struct unicode_nameannot * const *const UnicodeNameAnnot[];\n" );

    fprintf( out, "#ifdef __Cygwin\n" );
    fprintf( out, "__declspec(dllexport)\t/* Need this for cygwin to get shared libs */\n" );
    fprintf( out, "#endif /* __Cygwin */\n" );
    fprintf( out, "const struct unicode_nameannot * const *const UnicodeNameAnnot[] = {\n" );
    for ( i=0; i<sizeof(uniannot[is_fr])/(sizeof(uniannot[is_fr][0])*65536); ++i ) {	/* For each plane */
	for ( t=0; t<0xFFFE; ++t )
	    if ( uninames[is_fr][(i<<16)+t]!=NULL || uniannot[is_fr][(i<<16)+t]!=NULL )
	break;
	if ( t==0xFFFE )
	    fprintf( out, "\tnullnullarray,\n" );
	else
	    fprintf( out, "\t%s_%02X,\n", prefix, i );
    }
    while ( i<0x20 ) {
	fprintf( out, "\tnullnullarray%s\n", i!=0x20-1?",":"" );
	++i;
    }

    fprintf( out, "};\n\n" );
    return( 1 );
}

static int dump(int is_fr) {
    int dumpOK=0;

    FILE *out = fopen(is_fr ? "nameslist-fr.c":"nameslist.c","w");
    if ( out==NULL ) {
	fprintf( stderr, "Cannot open output file\n" );
	return( dumpOK );
    }
    FILE *header = fopen( is_fr ? "uninameslist-fr.h": "uninameslist.h","w");
    if ( header==NULL ) {
	fprintf( stderr, "Cannot open output header file\n" );
	fclose(out);
	return( dumpOK );
    }

    if ( dumpinit(out,header,is_fr) && dumpblock(out,header,is_fr) && \
	 dumparrays(out,header,is_fr) && dumpend(header,is_fr) && \
	 fflush(out)==0 && fflush(header)==0 )
	dumpOK=1;
    fclose(out); fclose(header);
    return( dumpOK );
}

int main(int argc, char **argv) {
    int errCode=1;

    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);
    InitArrays();
    max_a = max_n = 0;
    if ( ReadNamesList() && dump(1/*french*/) && dump(0/*english*/) )
	errCode=0;
    FreeArrays();
    return( errCode );
}
