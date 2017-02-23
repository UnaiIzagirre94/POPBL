/*
 * Leds_services.c
 *
 *  Created on: 24/11/2016
 *      Author: Prueba
 */

#include "config.h"
#include "Leds_services.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xgpio.h"



XGpio Gpio;


void LEDS_SERVICES_init(){

		/*Init AXI GPIO*/
		XGpio_Initialize(&Gpio, XPAR_GPIO_1_DEVICE_ID); //initialize leds trhough axi gpio

		/*AXI GPIO*/
		XGpio_SetDataDirection(&Gpio, 1, 1); 	//LEDs

}

void LEDS_SERVICES_changeState(unsigned char ledNumber){

	 XGpio_DiscreteWrite(&Gpio, 1, ledNumber); //write in led 1

}


/**
* @brief  Get a LEDS value
* @par 	  It gets the bit balue of all the LEDS state
* @param  The button that wants to be read
* @return Boolean
*/
BOOLEAN LEDS_SERVICES_getState(unsigned char ledNumber){

	BOOLEAN StateLed;

	StateLed = ( LEDS_SERVICES_getStates() >> ledNumber ) & 1;

	return StateLed;
}

/**
* @brief  Get the value of all the AXI gpios
* @par 	  Gets all the LEDS value
* @param  Empty
* @return LEDS (unsigned char)
*/
LEDS LEDS_SERVICES_getStates(){
	return XGpio_DiscreteRead(&Gpio, 1);
}
