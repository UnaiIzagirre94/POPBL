/**
****************************************************************************                                   
* @file			Keyboard.c
* @brief 		File general description                                     
* @version		0.1.0                                                     
* @date			2016-11-5
****************************************************************************
* @author		Allende, Imanol                                            
* @copyright	                                         
****************************************************************************
* @par Version history                                                     
* @par                                                                     
*  Version   | Date         |  Revised by   |  Description                 
*  --------- | ------------ | ------------- | ----------------------------                
*    0.1.0   | 2016-11-5   |  iallende     | Original version
****************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/

#include <stdio.h>
#include "Keyboard.h"
#include "config.h"

#if defined ZYNQ_7000
	#include "xil_printf.h"
	#include "xuartps.h"
	#include "xparameters.h"
#endif



/***************************************************************************
 **                                                                       **
 **                      DEFINITIONS AND MACROS                           **
 **                                                                       **
 ***************************************************************************/

#if defined ZYNQ_7000
	#define UART_BASEADDR XPAR_PS7_UART_1_BASEADDR
#endif
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
* @brief Init the Display
* @par Inits the uart
* @param Empty
* @return Nothing
*/
void KEYBOARD_init(){
	#if defined ZYNQ_7000
		HW_ABSTRACTION_initUART();
	#endif
}


 /**
 * @brief Reads the input
 * @par Reads from the UART
 * @param Empty
 * @return ret = the read value
 */
int KEYBOARD_readString(){
 	char uartRead[20];
 	char character;
 	int ret = 0;
 	int i = 0;

	//#if defined ZYNQ_7000
		//while(character !='\r'){
			//while (!XUartPs_IsReceiveData(UART_BASEADDR)){}
 		if(XUartPs_IsReceiveData(UART_BASEADDR)){
			character = XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
			xil_printf("%c", character);
			uartRead[i] = character;
			//i++;
		//}
		//uartRead[i] = '\0';
 		}
	//#endif
 	sscanf(uartRead, "%i", &ret);
 	return ret;
 }

 
/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/
