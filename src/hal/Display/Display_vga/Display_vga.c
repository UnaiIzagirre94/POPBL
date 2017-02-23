/**
****************************************************************************                                   
* @file			Display_vga.c                                     
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
 
#include "display_vga.h"
#include "../display.h"

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
* @par Inits the VGA
* @param Empty
* @return Nothing
*/
void DISPLAY_init(){
	DISPLAY_VGA_FUNCTIONS_displayInit();
}

/**
* @brief Dispays the string
* @par 	Displayis the string through the VGA 
* @param str
* @return Nothing
*/
void DISPLAY_printString(char str[]){
	int i=0;
	DISPLAY_VGA_FUNCTIONS_borrarFrameBuffer();
	while( ( i < 50 ) && ( str[i] != '\0' ) ){
		DISPLAY_VGA_FUNCTIONS_displayChar(250 + ( i * 8 ), 250, str[i]);
		i++;
	}
	DISPLAY_VGA_FUNCTIONS_copiarFrameBuffer();
	DISPLAY_VGA_FUNCTIONS_updateFrame();
}

/**
* @brief Reads the input
* @par 	Reads nothing
* @param Empty
* @return Nothing
*/
int DISPLAY_readInteger(){
	return 0;
}

/**
* @brief Prints two points and a line
* @par 	Reads nothing
* @param Empty
* @return Nothing
*/
int DISPLAY_printTwoPoints(){

	return 0;
}
