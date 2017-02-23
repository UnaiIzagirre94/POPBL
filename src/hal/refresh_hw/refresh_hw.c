/**
****************************************************************************
* @file			refresh_hw.c
* @brief 		Refreshes the hardware state so that we keep track of what is going on in the back of the user.
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
*    0.1.0   | 2016-12-11   |  iallende     | Original version
****************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/
#include "config.h"
#include "Buttons_services.h"
#include "keyboard.h"
#include "Leds_services.h"
#include "refresh_hw.h"

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
/**
 * @brief received Needs to be a global variable, as it stores the last received number from the keyboard.
 *
 */
int received = 0;
int last = 0;
/***************************************************************************
 **                                                                       **
 **                      EXPORTED FUNCTIONS                               **
 **                                                                       **
 ***************************************************************************/

/**
 * @brief Refreshes the buttons state and establishes a user position state depending on it.
 * @par
 * @param Empty
 * @return integer indicating users position
 */
int REFRESH_HW_refreshPosition(){

	int ret = SITTING;

	received = KEYBOARD_readString();
	if((received != last) && (received > 0) && (received < 5)){ //para asegurarnos de que los datos se reciben son correctos y no basura
		last = received;
		xil_printf("\n\r Received from keyboard: %i", received);
	}

	//--Using buttons:
	/*
	if(BUTTONS_SERVICES_getState(0) == FALSE){
		ret = SITTING;
		if(BUTTONS_SERVICES_getState(1) == TRUE){
			ret = SITTINGWRONG;
		}else{
			if(BUTTONS_SERVICES_getState(2)==TRUE){
				ret = MOVINGFAST;
			}
		}
	}else{
		ret = STANDING;
	}
	*/
	//--Using Keyboard:

	switch(last){

	case 1:
		ret = SITTING;
		break;
	case 2:
		ret = SITTINGWRONG;
		break;
	case 3:
		ret = MOVINGFAST;
		break;
	case 4:
		ret = STANDING;
		break;
	default:
		ret = SITTING;
		break;
	}
	return ret;
}

/***************************************************************************
 **                                                                       **
 **                      LOCAL FUNCTIONS                                  **
 **                                                                       **
 ***************************************************************************/

/**
 * @brief Initializes the services needed
 * @par
 * @param Empty
 * @return nothing
 */
void REFRESH_HW_init(){
	LEDS_SERVICES_init();
	BUTTONS_SERVICES_init();
}


/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/



