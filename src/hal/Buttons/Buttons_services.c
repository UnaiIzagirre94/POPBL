/**
****************************************************************************                                   
* @file			Buttons_services.c                                     
* @brief 		File general description                                     
* @version		0.1.0                                                     
* @date			2016-11-01                                                
****************************************************************************
* @author		Allende, Imanol                                            
* @copyright	                                         
****************************************************************************
* @par Version history                                                     
* @par                                                                     
*  Version   | Date         |  Revised by   |  Description                 
*  --------- | ------------ | ------------- | ----------------------------                
*    0.1.0   | 2016-11-01   |  iallende     | Original version             
****************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/
 
#include "New_types.h"
#include "Buttons_services.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xgpio.h"

/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/
 
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

XGpio GpioInput;

/***************************************************************************
 **                                                                       **
 **                      EXPORTED FUNCTIONS                               **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      LOCAL FUNCTIONS                                  **
 **                                                                       **
 ***************************************************************************/

/**
* @brief  Initialization of the buttons
* @par 	  It inits the axi gpios 
* @param  Empty
* @return Nothing
*/
void BUTTONS_SERVICES_init(){

		/*Init AXI GPIO*/
		XGpio_Initialize(&GpioInput, XPAR_GPIO_0_DEVICE_ID); //initialize buttons trhough axi gpio

		/*AXI GPIO*/
		XGpio_SetDataDirection(&GpioInput, 1, 0); 	//BTNs

}

/**
* @brief  Get a buttons value
* @par 	  It gets the bit balue of all the buttons state
* @param  The button that wants to be read
* @return Boolean
*/
BOOLEAN BUTTONS_SERVICES_getState(unsigned char buttonNumber){

	BOOLEAN stateButton;

	stateButton = ( BUTTONS_SERVICES_getStates() >> buttonNumber ) & 1;

	return stateButton;
}

/**
* @brief  Get the value of all the AXI gpios
* @par 	  Gets all the buttons value
* @param  Empty
* @return Buttons (unsigned char)
*/
BUTTONS BUTTONS_SERVICES_getStates(){
	return XGpio_DiscreteRead(&GpioInput, 1);
}
