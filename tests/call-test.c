/* Test libuninameslist library calls
Copyright (C) 2017, Joe Da Silva

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301, USA.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(DO_CALL_TEST3) || defined(DO_CALL_TEST4)
#include "uninameslist-fr.h"
#else
#include "uninameslist.h"
#ifdef DO_CALL_TEST5
#include "uninameslist-fr.h"
#endif
#endif

static const char NOTCMP[]="Annotation can vary, check to exist, string not compared";
static const char NOBLKT[]="Block Names can vary, check to exist, string not compared";

static int test(long val, const char *result, const char *expect) {

    printf("test code=");
    if ( val<0 )
	printf("%ld,",val);
    else if ( val<65536 )
	printf("U+%04lx,",val);
    else
	printf("0x%08lx,",val);

    if ( result==NULL ) {
	if ( expect!=NULL ) {
	    printf("\n  ret=NULL\n  exp=\"%s\".\n",expect);
	    return( 0 );
	}
	printf("  return=NULL value\n");
	return( 1 );
    }

    printf("\n  ret=\"%s\"\n  exp=\"%s\"\n",result,expect);
    return( (int)(strcmp(result,expect)==0 || NOTCMP==expect || NOBLKT==expect ? 1:0) );
}

#if defined(DO_CALL_TEST0) || defined(DO_CALL_TEST3)
static const char *test_name(unsigned long uni) {
    const char *pt;

    pt=UnicodeNameAnnot[uni>>16][(uni>>8)&0xff][uni&0xff].name;
    return( pt );
}

static const char *test_annot(unsigned long uni) {
    const char *pt;

    pt=UnicodeNameAnnot[uni>>16][(uni>>8)&0xff][uni&0xff].annot;
    return( pt );
}
#endif

#ifdef DO_CALL_TEST0
static int test_calls_2012(void) {
/* Verify backwards compatibility for older programs. */
    return( ((test(32,test_name(32),"SPACE") && \
	      test(7,test_annot(7),"\t= BELL") && \
	      test(58,test_name(58),"COLON") && \
	      test(126,test_name(126),"TILDE"))?0:-1) );
}
#endif

#ifdef DO_CALL_TEST1
static int test_calls_03(void) {
    const char *cc;

    if ( uniNamesList_name(-100)==NULL && \
	 uniNamesList_name(0x300000)==NULL && \
	 test(32,uniNamesList_name(32),"SPACE") && \
	 test(59,uniNamesList_name(59),"SEMICOLON") && \
	 test(63,uniNamesList_name(63),"QUESTION MARK") && \
	 test(0x1F3A9,uniNamesList_name(0x1F3A9),"TOP HAT") )
	;
    else {
	printf("error with uniNamesList_name(code)\n");
	return( -1 );
    }

    if ( uniNamesList_annot(-100)==NULL && \
	 uniNamesList_annot(0x300000)==NULL && \
	 test(7,uniNamesList_annot(7),"\t= BELL") && \
	 test(66,uniNamesList_annot(66),NOTCMP) && \
	 test(126,uniNamesList_annot(126),NOTCMP) && \
	 test(0x1F3B5,uniNamesList_annot(0x1F3B5),NOTCMP) )
	;
    else {
	printf("error with uniNamesList_annot(code)\n");
	return( -2 );
    }

    cc = uniNamesList_NamesListVersion();
    printf("test uniNamesList_NamesListVersion(), return=\"%s\"\n",cc);
    if ( cc==NULL || cc[0]!='N' || cc[1]!='a' || cc[2]!='m' )
	return( -3 );

    return( 0 );
}
#endif

#ifdef DO_CALL_TEST2
static int test_calls_04(void) {
    int ret;
    const char *cc;

    ret = uniNamesList_blockCount();
    printf("test, return=%d=uniNamesList_blockCount(void);\n",ret);
    if ( ret<100) {
        printf("error, expected positive value (over 100).\n");
        return( -1 );
    }

    if ( uniNamesList_blockNumber(-100)==-1 && \
	 uniNamesList_blockNumber(0x300000)==-1 && \
	 uniNamesList_blockNumber(7)==0 && \
	 uniNamesList_blockNumber(0x100)==2 && \
	 uniNamesList_blockNumber(960)>5 )
	;
    else {
        printf("error with uniNamesList_blockNumber(code).\n");
        return( -2 );
    }

    if ( uniNamesList_blockName(-100)==NULL && \
	 uniNamesList_blockName(0x300000)==NULL && \
	 test(0,uniNamesList_blockName(0),NOBLKT) && \
	 test(1,uniNamesList_blockName(1),NOBLKT) && \
	 test(12,uniNamesList_blockName(12),NOBLKT) && \
	 test(50,uniNamesList_blockName(50),NOBLKT) )
	;
    else {
	printf("error with uniNamesList_blockName(uniBlock)\n");
	return( -3 );
    }

    return( 0 );
}
#endif

#ifdef DO_CALL_TEST3
static int test_calls_2012F(void) {
/* Verify backwards compatibility for older programs. */
    return( ((test(32,test_name(32),"ESPACE") && \
	      test(5,test_annot(5),"\t= DEMANDE") && \
	      test(42,test_name(42),"ASTÉRISQUE") && \
	      test(44,test_name(44),"VIRGULE"))?0:-1) );
}
#endif

#ifdef DO_CALL_TEST4
static int test_calls_FR(void) {
    const char *cc;

    if ( uniNamesList_nameFR(-100)==NULL && \
	 uniNamesList_nameFR(0x300000)==NULL && \
	 test(32,uniNamesList_nameFR(32),"ESPACE") && \
	 test(42,uniNamesList_nameFR(42),"ASTÉRISQUE") && \
	 test(44,uniNamesList_nameFR(44),"VIRGULE") )
	;
    else {
	printf("error with uniNamesList_FRname(code)\n");
	return( -1 );
    }

    if ( uniNamesList_annotFR(-100)==NULL && \
	 uniNamesList_annotFR(0x300000)==NULL && \
	 test(5,uniNamesList_annotFR(5),"\t= DEMANDE") && \
	 test(7,uniNamesList_annotFR(7),"\t= SONNERIE") && \
	 test(126,uniNamesList_annotFR(126),NOTCMP) && \
	 test(0x1F3B5,uniNamesList_annotFR(0x1F3B5),NOTCMP) )
	;
    else {
	printf("error with uniNamesList_annotFR(code)\n");
	return( -2 );
    }

    cc = uniNamesList_NamesListVersionFR();
    printf("test uniNamesList_NamesListVersionFR(), return=\"%s\"\n",cc);
    if ( cc==NULL || cc[0]!='N' || cc[1]!='a' || cc[2]!='m' )
	return( -3 );

    return( 0 );
}
#endif

#ifdef DO_CALL_TEST5
static int test_calls_both(void) {
    if ( uniNamesList_name(-100)==NULL && \
	 uniNamesList_name(0x300000)==NULL && \
	 test(32,uniNamesList_name(32),"SPACE") && \
	 test(59,uniNamesList_name(59),"SEMICOLON") && \
	 test(63,uniNamesList_name(63),"QUESTION MARK") && \
	 test(0x1F3A9,uniNamesList_name(0x1F3A9),"TOP HAT") )
	;
    else {
	printf("error with uniNamesList_name(code)\n");
	return( -1 );
    }

    if ( uniNamesList_nameFR(-100)==NULL && \
	 uniNamesList_nameFR(0x300000)==NULL && \
	 test(32,uniNamesList_nameFR(32),"ESPACE") && \
	 test(42,uniNamesList_nameFR(42),"ASTÉRISQUE") && \
	 test(44,uniNamesList_nameFR(44),"VIRGULE") )
	;
    else {
	printf("error with uniNamesList_FRname(code)\n");
	return( -2 );
    }

    return( 0 );
}
#endif

#ifdef DO_CALL_TEST6
static int test_normalize(void) {
    int a,b,c;
    long u,w;
    const char *p;

    if ( uniNamesList_names2cnt()<25 ) {
	printf("error with uniNamesList_names2cnt(void)\n");
	return( -1 );
    }

    u = uniNamesList_names2val(2);
    w = uniNamesList_names2val(-1);
    if ( u<100 || u>10000 || w!=-1 ) {
	printf("error with uniNamesList_names2val(code), expected 0x709,-1, Received 0x%04lX %ld\n", u, w );
	return( -2 );
    }

    a = uniNamesList_names2getU(0x0709);
    c = uniNamesList_names2lnU(0x0709);
    p = uniNamesList_names2anU(0x0709);
    printf("name2code_index:%d, value:%d, str='%s'\n", a, c, p );
    if ( uniNamesList_names2anU(0x01A0)!=NULL || c!=34 || p[3]!='I' ) {
	printf("error with uniNamesList_names2anU(Ucode), expected NULL,'I'\n" );
	return( -3 );
    }

    return( 0 );
}
#endif

int main(int argc, char **argv) {
    int ret;

#ifdef DO_CALL_TEST0
    /* test 20120731 version calls for older programs */
    ret=test_calls_2012();
#endif
#ifdef DO_CALL_TEST1
    /* test function calls available for 0.3.20130423 */
    ret=test_calls_03();
#endif
#ifdef DO_CALL_TEST2
    /* test function calls available for 0.4.20140731 */
    ret=test_calls_04();
#endif
#ifdef DO_CALL_TEST3
    /* test 20120731 version calls for older programs */
    ret=test_calls_2012F();
#endif
#ifdef DO_CALL_TEST4
    /* try test a function call to the French library */
    ret=test_calls_FR();
#endif
#ifdef DO_CALL_TEST5
    /* verify we can use both libraries at same time! */
    ret=test_calls_both();
#endif
#ifdef DO_CALL_TEST6
    /* errors happen! check a few normalized aliases. */
    ret=test_normalize();
#endif
    return ret;
}
