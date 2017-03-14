/**
****************************************************************************
* @file			store_data.c
* @brief 		Stores the information of the sensors in the SD card.
* @version		0.1.0
* @date			2016-12-13
****************************************************************************
* @author		Izagirre, Unai
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |  Revised by   |  Description
*  --------- | ------------ | ------------- | ----------------------------
*    0.1.0   | 2016-12-13   |  uizagirre    | Original version
****************************************************************************/


/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/
#include <string.h>
#include "analyse_position.h"
#include "Store.h"
#include "Back.h"
#include "store_data.h"


/***************************************************************************
 **                                                                       **
 **                      DEFINITIONS AND MACROS                           **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      TYPEDEFS AND STRUCTURES                          **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      PROTOTYPES OF LOCAL FUNCTIONS                    **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      EXPORTED VARIABLES                               **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      GLOBAL VARIABLES                                 **
 **                                                                       **
 ***************************************************************************/

 static char strBig [MAXIMUM_ARRAY];
 static int indx = 0;
 static int dataCounter = 0;
/***************************************************************************
 **                                                                       **
 **                      EXPORTED FUNCTIONS                               **
 **                                                                       **
 ***************************************************************************/

/**
* @brief Perioic task to store the data we take from the BACK buffer in the SD card. We store the data in a temporary string and
* 		 concatenate the received data in the "strBig" string. When this buffer is full, we store all the data at once in the SD card.
* 		 We do this in order to open, write and close the SD card.
* @improveThis The frequency in which we store the data and the length of the buffer str could be improved.
*/
void STORE_DATA_storeInfo(){

	char str [MAXIMUM_CHARAC];
	int newLength = 0;
	int i; // Counter for the "for" loop.

	//Check sensors state
	ANALYSE_POSITION_checkState(str);
	newLength = strlen(str);

	if(indx < MAXIMUM_ARRAY-1 ){
		for(i = 0; i<newLength; i++){
			strBig[indx] = str[i];
			indx++;
		}
		if(dataCounter < 3){
			dataCounter++;

		}else{
			dataCounter = 0;
			strBig[indx] = '\n';
			indx++;
		}
	}else{
		//If we reach the end of the buffer, we store the collected data in the SD card.
		indx = 0;
		dataCounter = 0;
		BACK_storeState(strBig);
	}
}

/***************************************************************************
 **                                                                       **
 **                      LOCAL FUNCTIONS                                  **
 **                                                                       **
 ***************************************************************************/





/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/



