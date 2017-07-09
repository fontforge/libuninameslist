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
#include "uninameslist.h"

const char NOTCMP[]="Annotation can vary, check to exist, string not compared";

int test(long val, const char *result, const char *expect) {

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
    return( (strcmp(result,expect)==0 || NOTCMP==expect ? 1:0) );
}

#ifdef DO_CALL_TEST0
const char *test_name(unsigned long uni) {
    const char *pt;

    pt=UnicodeNameAnnot[uni>>16][(uni>>8)&0xff][uni&0xff].name;
    return( pt );
}

const char *test_annot(unsigned long uni) {
    const char *pt;

    pt=UnicodeNameAnnot[uni>>16][(uni>>8)&0xff][uni&0xff].annot;
    return( pt );
}

int test_calls_2012(void) {
/* Verify backwards compatibility for older programs. */
    return( ((test(32,test_name(32),"SPACE") && \
	      test(32,test_annot(32),NOTCMP) && \
	      test(58,test_name(58),"COLON") && \
	      test(126,test_name(126),"TILDE"))?0:-1) );
}
#endif

#ifdef DO_CALL_TEST1
int test_calls_03(void) {
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
	 test(32,uniNamesList_annot(32),NOTCMP) && \
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
int test_calls_04(void) {
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
	 test(0,uniNamesList_blockName(0),NOTCMP) && \
	 test(1,uniNamesList_blockName(1),NOTCMP) && \
	 test(12,uniNamesList_blockName(12),NOTCMP) && \
	 test(50,uniNamesList_blockName(50),NOTCMP) )
	;
    else {
	printf("error with uniNamesList_blockName(uniBlock)\n");
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
    return ret;
}
