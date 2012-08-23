#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* Reads from NamesList.txt which must be present in the current directory */
/* Builds two arrays of strings for each unicode character. One contains the */
/*  name of the character, the other the annotations for each character */
/* Outputs nameslist.c containing these two sparse arrays */

static char *uninames[2][17*65536];
static char *uniannot[2][17*65536];
static struct block { int start, end; char *name; struct block *next;}
	*head[2]={NULL,NULL}, *final[2]={NULL,NULL};

static char *myfgets(char *buf,int bsize,FILE *file) {
    /* NamesList.txt uses CR as a line seperator */
    int ch;
    char *pt, *end = buf+bsize-2;

    for ( pt=buf ; pt<end && (ch=getc(file))!=EOF && ch!='\n' && ch!='\r'; )
	*pt++ = ch;
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

static void ReadNamesList(void) {
    char buffer[200];
    FILE *nl;
    int a_char = -1, first, last;
    char *end, *namestart, *pt, *temp;
    struct block *cur;
    int i;
    static char *nameslistfiles[] = { "NamesList.txt", "ListeDesNoms.txt", NULL };

    for ( i=0; nameslistfiles[i]!=NULL; ++i ) {
	nl = fopen( nameslistfiles[i],"r" );
	if ( nl==NULL ) {
	    fprintf( stderr, "Cannot find %s. Please copy it from\n\thttp://www.unicode.org/Public/UNIDATA/NamesList.txt\n", nameslistfiles[i] );
exit( 1 );
	}
	while ( myfgets(buffer,sizeof(buffer),nl)!=NULL ) {
	    if ( buffer[0]=='@' ) {
		a_char = -1;
		if ( buffer[1]=='@' && buffer[2]=='\t' ) {
		    first = strtol(buffer+3,&end,16);
		    if ( *end=='\t' ) {
			namestart = end+1;
			for ( pt=namestart; *pt!='\0' && *pt!='\t' ; ++pt );
			if ( *pt=='\t' ) {
			    *pt = '\0';
			    last = strtol(pt+1,&end,16);
			    if ( last>first ) {
				cur = malloc(sizeof(struct block));
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
		if ( a_char>=0 && a_char<sizeof(uninames[0])/sizeof(uninames[0][0]) )
		    uninames[i][a_char] = strdup(namestart);
	    } else if ( a_char==-1 ) {
	continue;
	    } else if ( buffer[0]=='\t' && buffer[1]==';' ) {
	continue;		/* comment */
	    } else if ( a_char>=0 && a_char<sizeof(uniannot[0])/sizeof(uniannot[0][0]) ) {
		for ( pt=buffer; *pt && *pt!='\r' && *pt!='\n' ; ++pt );
		if ( *pt=='\r' ) *pt='\n';
		if ( uniannot[i][a_char]==NULL )
		    uniannot[i][a_char] = strdup(buffer);
		else {
		    temp = realloc(uniannot[i][a_char],strlen(uniannot[i][a_char])+strlen(buffer)+1);
		    if ( temp==NULL ) {
			fprintf( stderr, "Out of memory\n" );
    exit(1);
		    }
		    strcat(temp,buffer);
		    uniannot[i][a_char] = temp;
		}
	    }
	}
	fclose(nl);
    }
}

static void dumpstring(char *str,FILE *out) {
    char *start;

    do {
	putc( '"', out);
	for ( start=str; *str!='\n' && *str!='\0'; ++str ) {
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

static void dumpinit(FILE *out, FILE *header, int is_fr) {
    int i;

    fprintf( out, "#include <stdio.h>\n" );
    fprintf( out, "#include \"nameslist.h\"\n\n" );
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

    fprintf( header, "#ifndef _NAMESLIST_H\n" );
    fprintf( header, "# define _NAMESLIST_H\n\n" );
    fprintf( header, "struct unicode_block {\n    int start, end;\n    const char *name;\n};\n\n" );
    fprintf( header, "struct unicode_nameannot {\n    const char *name, *annot;\n};\n\n" );
}

static void dumpend(FILE *out, FILE *header, int is_fr) {
    fprintf( header, "\n/* Index by: UnicodeNameAnnot[(uni>>16)&0x1f][(uni>>8)&0xff][uni&0xff] */\n" );
    fprintf( header, "\n/* At the beginning of lines (after a tab) within the annotation string, a */\n" );
    fprintf( header, "/*  * should be replaced by a bullet U+2022 */\n" );
    fprintf( header, "/*  x should be replaced by a right arrow U+2192 */\n" );
    fprintf( header, "/*  : should be replaced by an equivalent U+224D */\n" );
    fprintf( header, "/*  # should be replaced by an approximate U+2245 */\n" );
    fprintf( header, "/*  = should remain itself */\n" );
    fprintf( header, "\n#endif\n" );
}

static void dumpblock(FILE *out, FILE *header, int is_fr ) {
    int bcnt;
    struct block *block;
    int i, maxa, maxn;

    fprintf( out, "#ifdef __Cygwin\n" );
    fprintf( out, "__declspec(dllexport)\t/* Need this for cygwin to get shared libs */\n" );
    fprintf( out, "#endif /* __Cygwin */\n" );
    fprintf( out, "const struct unicode_block UnicodeBlock[] = {\n" );
    for ( block = head[is_fr], bcnt=0; block!=NULL; block=block->next, ++bcnt ) {
	fprintf( out, "\t{ 0x%x, 0x%x, \"%s\" }%s\n", block->start, block->end,
		block->name, block->next!=NULL ? "," : "" );
    }
    fprintf( out, "};\n\n" );
    fprintf( header, "extern const struct unicode_block UnicodeBlock[%d];\n", bcnt );

    maxn = maxa = 0;
    for ( i=0; i<sizeof(uniannot[is_fr])/sizeof(uniannot[0][is_fr]); ++i ) {
	if ( uninames[is_fr][i]!=NULL && maxn<strlen(uninames[is_fr][i])) maxn = strlen(uninames[is_fr][i]);
	if ( uniannot[is_fr][i]!=NULL && maxa<strlen(uniannot[is_fr][i])) maxa = strlen(uniannot[is_fr][i]);
    }
    fprintf( header, "\n#define UNICODE_NAME_MAX\t%d\n", maxn );
    fprintf( header, "#define UNICODE_ANNOT_MAX\t%d\n", maxa );
}

static void dumparrays(FILE *out, FILE *header, int is_fr ) {
    int i,j,k, t;
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
}

static void dump(int is_fr) {
    FILE *out = fopen(is_fr ? "nameslist-fr.c":"nameslist.c","w");
    FILE *header = fopen( is_fr ? "/dev/null": "nameslist.h","w");

    if ( out==NULL ) {
	fprintf( stderr, "Cannot open output file\n" );
exit( 1 );
    }
    if ( header==NULL ) {
	fprintf( stderr, "Cannot open output header file\n" );
	fclose(out);
exit( 1 );
    }

    dumpinit(out,header,is_fr);
    dumpblock(out,header,is_fr);
    dumparrays( out, header,is_fr );
    dumpend(out,header,is_fr);
    fclose(out);
}

int main( int argc, char **argv) {
    ReadNamesList();
    dump(0/*english*/);
    dump(1/*french*/);
return( 0 );
}
