/**
****************************************************************************
* @file			back.c
* @brief 		Buffer where the back state is stored and getters/setters for that buffer.
* @version		0.1.0
* @date			2016-12-15
****************************************************************************
* @author		Izagirre, Unai
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |  Revised by   |  Description
*  --------- | ------------ | ------------- | ----------------------------
*    0.1.0   | 2016-12-15   |  uizagirre    | Original version
****************************************************************************/


/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/
#define BACK_C

//#include "display.h"
//#include "scheduler.h"
#include "store.h"
//#include "Keyboard.h"
//#include "hw_abstraction.h"
#include "Back.h"

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

static BACK back_buffer;

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

/***************************************************************************
 **                                                                       **
 **                      EXPORTED FUNCTIONS                               **
 **                                                                       **
 ***************************************************************************/

/**
 * @brief Initializes the back_buffer.data array to '0' values.
 * @par
 */
void BACK_initBack(){
	int i = 0;

	for(i = 0; i<BITS_PER_SENSOR*ACCELEROMETERS; i++) back_buffer.data[i]='0';
}

/**
 * @brief Getter of the "back_buffer" buffer
 * @par
 */
BACK BACK_getBack(){
	return back_buffer;
}

/**
 * @brief Setter of the "back_buffer" buffer
 * @par
 * @param[in] backNew Sets the new BACK structure to be stored in the "back_buffer" buffer
 */
void BACK_setBack(BACK backNew){
	back_buffer = backNew;
}

/**
 * @brief Initializes all the hal needed for our app "app_back".
 * @par
 */
void BACK_init(){

	//Initialize display, timer, scheduler and buttons.
	//DISPLAY_init();
	//HW_ABSTRACTION_initTimer(10);
	//REFRESH_HW_init();
	//KEYBOARD_init();
	BACK_initBack();
	//SCHEDULER_init();
}

/**
 * @brief Stores the user's back state and the timestamp in the SD card.
 * @par
 * @param[in] str String to store with the back state and current timestamp.
 */
void BACK_storeState(char * str){
	//STORE_storeInSD(str);
	STORE_storeInFile(str);
}

