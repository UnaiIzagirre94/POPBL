/**
****************************************************************************
* @file			analyse_position.c
* @brief 		Analyse and return the position of the user and current timestamp.
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
#include <stdio.h>
#include "back_control.h"
#include "config.h"
#include "Hw_abstraction.h"
#include "refresh_hw.h"
#include "state_machine.h"
#include "analyse_position.h"



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
static POSITION user_position;
static TS_MACHINE backBone;
static int initDone = 0;
/***************************************************************************
 **                                                                       **
 **                      EXPORTED FUNCTIONS                               **
 **                                                                       **
 ***************************************************************************/

/**
* @brief Function that calls to the executer of the state machine (libs/state_machine.c)
*
*/
void ANALYSE_POSITION_execute_SM(){
		if(!initDone){
			backBone = BACK_CONTROL_getBackBone();
			initDone = 1;
		}
		else STATE_MACHINE_execute(&backBone);
}

/**
 * @brief Analyses the state in which the user is currently and changes a string depending on it.
 *
 * @param str[out] The string where the position of the user and the current time will be stored.
 */
 void ANALYSE_POSITION_checkState(char str[]){
	 	char strTime[50];
 		//get the current time
	 	ANALYSE_POSITION_getCurrentTime(strTime);

 		//check the position of the user and change the string that is going to be stored in the SD
 		user_position.current = REFRESH_HW_refreshPosition();

 		switch(user_position.current){
 			  case SITTING: sprintf(str,"2/%s ",strTime);
 				  break;
 			  case STANDING: sprintf(str,"1/%s ",strTime);
 				  break;
 			  case SITTINGWRONG: sprintf(str,"3/%s ",strTime);
 				  break;
 			  case MOVINGFAST: sprintf(str,"4/%s ",strTime);
 				  break;
 			  default: sprintf(str, "Undefined state\n");
 		}

 }

 /**
  * @brief Sets the current time since the beggining of the application in a specific way in the inserted string.
  *
  * @param[out] str The time will be stored here.
  */
 void ANALYSE_POSITION_getCurrentTime(char str[]){
	 	int decimas = 0,segundos = 0,minutos = 0,horas = 0;

	 	decimas = HW_ABSTRACTION_getTimerCount();
		segundos = decimas/100;
		horas = (int)(segundos / 3600);
		minutos=(int)((segundos - horas * 3600) / 60);
		segundos=segundos - (horas * 3600 + minutos * 60);
		decimas = decimas - ((decimas/10)*10);

		sprintf(str,"%i:%i:%i:%i ",horas,minutos,segundos,decimas);
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
