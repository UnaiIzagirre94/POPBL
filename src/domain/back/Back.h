/**
****************************************************************************
* @file			analyse_position.h
*
* @version		0.1.0
* @date			2016-12-14
****************************************************************************
* @author		Izagirre, Unai
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |  Revised by   |  Description
*  --------- | ------------ | ------------- | ----------------------------
*    0.1.0   | 2016-12-14   |  uizagirre    | Original version
****************************************************************************/
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
#ifndef BACK_H_
#define BACK_H_

#define ACCELEROMETERS 1 //Number of acelerometers we want to get information from.
#define BITS_PER_SENSOR 24 //Number of bits we want to store per accelerometer
#ifdef BACK_C
#define PUBLIC
#else
#define PUBLIC  extern
#endif

/***************************************************************************
 **                                                                       **
 **                      TYPEDEFS AND STRUCTURE                           **
 **                                                                       **
 ***************************************************************************/
/**
 * @struct BACK The struct BACK stores in a char array the information of the accelerometers. We store 24 bits per accelerometer: 1 byte per X, Z and Y axis. (8 bits * 3 axis = 24 bits).
 */

typedef struct {
/**
 * @var char data[BITS_PER_SENSOR *ACCELEROMETERS]
 * @brief is the actual variable that stores the information.
 */
	char data[BITS_PER_SENSOR*ACCELEROMETERS];
}BACK;

/***************************************************************************
**                                                                       **
**                      EXPORTED VARIABLES                               **
**                                                                       **
***************************************************************************/


/***************************************************************************
**                                                                       **
**                      EXPORTED FUNCTIONS                               **
**                                                                       **
***************************************************************************/
void BACK_init();
void BACK_initBack();
BACK BACK_getBack();
void BACK_setBack(BACK backNew);
void BACK_storeState(char * str);

/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/

#endif /* BACK_H_ */
