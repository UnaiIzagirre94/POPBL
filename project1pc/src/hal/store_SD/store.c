/*
 * store.c
 *
 *  Created on: 16 mar. 2017
 *      Author: unai
 */
#include <stdio.h>
#include "store.h"

void STORE_storeInFile(char * data){

	FILE *fp = fopen("test.txt", "ab");
	    if (fp != -1)
	    {
	        fputs(data, fp);
	        fclose(fp);
	    }
}
