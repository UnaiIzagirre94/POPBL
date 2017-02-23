/**
****************************************************************************
* @file			Store.c
* @brief 		We add a new line in a specific file in the SD card called "TEST.txt" with the last information of the user position and the timestamp.
* @version		0.1.0
* @date			2016-12-20
****************************************************************************
* @author		Izagirre, Unai
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |  Revised by   |  Description
*  --------- | ------------ | ------------- | ----------------------------
*    0.1.0   | 2016-12-20   |  uizagirre    | Original version
****************************************************************************/
#include <stdio.h>
#include "ff.h"
#include "integer.h"
#include "xil_types.h"
#include "xstatus.h"
#include "Store.h"

static FIL fil;		/* File object */
static FATFS fatfs;
static char FileName[32] = "TEST.txt";
static char *SD_File;
u32 Platform;

#ifdef __ICCARM__
#pragma data_alignment = 32
u8 DestinationAddress[10*1024*1024];
u8 SourceAddress[10*1024*1024];
#pragma data_alignment = 4
#else
u8 DestinationAddress[10*1024*1024] __attribute__ ((aligned(32)));
u8 SourceAddress[10*1024*1024] __attribute__ ((aligned(32)));
#endif

#define TEST 7


/**
 * @brief Stores the string introduced in a new line of the SD card.
 * @par
 * @param[in] newStr string to be introduced in the SD card.
 * @return integer the process has been successful (0) or error code.
 */
int STORE_storeInSD(char * newStr){

	FRESULT Res;
	UINT NumBytesRead;
	UINT NumBytesWritten;
	TCHAR *Path = "0:/";

	/*
			 * Pointer to beginning of file .
			 */
	Res = f_mount(&fatfs, Path, 0);
		//Res = f_mount(0,&fatfs);

		if (Res != FR_OK) {
			return XST_FAILURE;
		}

		/*
		 * Open file with required permissions.
		 * Here - Creating new file with read/write permissions. .
		 * To open file with write permissions, file system should not
		 * be in Read Only mode.
		 */
		SD_File = (char *)FileName;

		Res = f_open(&fil, SD_File, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
		if (Res) {
			return XST_FAILURE;
		}
			Res = f_lseek(&fil, 0);
			if (Res) {
				return XST_FAILURE;
			}

		/*
		 * Para saber el tamaño
		 */


		//f_stat(SD_File, &fno);
		/*
		 * Pointer to beginning of file .
		 */
		Res = f_lseek(&fil, 0);
		if (Res) {
			return XST_FAILURE;
		}
		int i = 0;
		int kar = 0;
		do{
			Res = f_read(&fil, &kar, 1, &NumBytesRead);
			i++;
		}while( (NumBytesRead!= 0 ) && ( kar != 0) );
		f_lseek(&fil,i-1);
		char str[MAXIMUM_ARRAY];
		sprintf(str,newStr);
		sprintf(SourceAddress, "%s\r\n", str);
		Res = f_write(&fil, (const void*)SourceAddress,  MAXIMUM_ARRAY , &NumBytesWritten);//strlen(str)+400
		if (Res) {
			return XST_FAILURE;
		}


		Res = f_close(&fil);
				if (Res) {
					return XST_FAILURE;
				}

		return XST_SUCCESS;
}
