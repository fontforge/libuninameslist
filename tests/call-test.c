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

//#include <math.h>
//#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uninameslist.h"

int main(int argc, char **argv) {
    int ret;
    const char *cc;
    char *c;

    /* expect "LATIN CAPITAL LETTER A" */
    cc = uniNamesList_name(65);
    printf("test, return=\"%s\"=uniNamesList_name(65);\n",cc);

    cc = uniNamesList_NamesListVersion();
    printf("test, return=\"%s\"=uniNamesList_NamesListVersion(void);\n",cc);

    ret = uniNamesList_blockCount();
    printf("test, return=%d=uniNamesList_blockCount(void);\n",ret);
    if ( ret<10) {
        printf("error, expected positive value\n");
        return -1;
    }

    ret = 0;
    return ret;
}
