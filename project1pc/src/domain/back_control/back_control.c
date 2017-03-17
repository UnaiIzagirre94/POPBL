/**
****************************************************************************
* @file			back_control.c
* @brief 		Implementation of the event-actions of the state machine.
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
#include "analyse_position.h"
#include "Back.h"
//#include "Display.h"
//#include "Leds_services.h"
#include "refresh_hw.h"
#include "back_control.h"


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
/**
* @var TS_EVEACC standing[]
* @brief The events and actions of the state machine that are executed when the user is standing.
*/
TS_EVEACC standing[] = {
		{SITTING, "t_STANDING_2_SITTING", BACK_CONTROL_ev_standing_to_sitting, BACK_CONTROL_acc_standing_to_sitting}, //siguiente estado, nombre para debugging, puntero a funcion  evento, puntero a funcion accion
		{0, 0, 0, 0}
};
/**
* @var TS_EVEACC sitting[]
* @brief The events and actions of the state machine that are executed when the user is sitting.
*/
TS_EVEACC sitting[] = {
		{STANDING, "t_SITTING_2_STANDING", BACK_CONTROL_ev_sitting_to_standing, BACK_CONTROL_acc_sitting_to_standing},
		{SITTINGWRONG, "t_SITTING_2_SITTINGWRONG", BACK_CONTROL_ev_sitting_to_sitting_wrong, BACK_CONTROL_acc_sitting_to_sitting_wrong},
		{MOVINGFAST, "t_SITTING_2_MOVINGFAST", BACK_CONTROL_ev_sitting_to_moving_fast, BACK_CONTROL_acc_sitting_to_moving_fast},
		{0, 0, 0, 0}
};
/**
* @var TS_EVEACC sitting_wrong[]
* @brief The events and actions of the state machine that are executed when the user is sitting wrong.
*/
TS_EVEACC sitting_wrong[] = {
		{SITTING, "t_SITTINGWRONG_2_SITTING", BACK_CONTROL_ev_sitting_wrong_to_sitting, BACK_CONTROL_acc_sitting_wrong_to_sitting}, //de estar mal sentado a estar sentado bien
		{STANDING, "t_SITTINGWRONG_2_STANDING", BACK_CONTROL_ev_sitting_wrong_to_standing, BACK_CONTROL_acc_sitting_wrong_to_standing}, //de estar mal sentado a estar de pie
		{0, 0, 0, 0}
};

/**
* @var TS_EVEACC moving_fast[]
* @brief The events and actions of the state machine that are executed when the user is moving fast.
*/
TS_EVEACC moving_fast[] = {
		{SITTING, "t_MOVINGFAST_2_SITTING", BACK_CONTROL_ev_moving_fast_to_sitting, BACK_CONTROL_acc_moving_fast_to_sitting}, //de estar mal sentado a estar sentado bien
		{STANDING, "t_MOVINGFAST_2_STANDING", BACK_CONTROL_ev_moving_fast_to_standing, BACK_CONTROL_acc_moving_fast_to_standing},
		{0, 0, 0, 0}
};

/**
 * @var TS_STATE stateStanding
 * @brief The state of the state machine that is activated when the user is standing.
 */
TS_STATE stateStanding = {STANDING, 'e_Standing', BACK_CONTROL_do_standing, standing};
/**
 * @var TS_STATE stateSitting
 * @brief The state of the state machine that is activated when the user is sitting.
 */
TS_STATE stateSitting = {SITTING, 'e_Sitting',BACK_CONTROL_do_sitting, sitting};
/**
 * @var TS_STATE stateSittingWrong
 * @brief The state of the state machine that is activated when the user is sitting wrong.
 */
TS_STATE stateSittingWrong = {SITTINGWRONG, 'e_SittingWrong', BACK_CONTROL_do_sitting_wrong, sitting_wrong};
/**
 * @var TS_STATE stateMovingFast
 * @brief The state of the state machine that is activated when the user is moving fast.
 */
TS_STATE stateMovingFast = {MOVINGFAST, 'e_MovingFast', BACK_CONTROL_do_moving_fast, moving_fast};

TS_STATE* statesBackBone[] = {
		&stateStanding,
		&stateSitting,
		&stateSittingWrong,
		&stateMovingFast,
		0

};

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
BOOLEAN displayed=FALSE; //This variable keeps track of whether the current state of the user has to be displayed or its already been diplayed.

/**
* @var user_position
* @brief Is the buffer where the current position of the user is stored.
*/
POSITION user_position = {SITTING};
/**
* @var backBone
* @brief Is the state machine. Stores it's name, the current state of the user and the list of states in which it can be.
*/
TS_MACHINE backBone = { 0, "State_machine_backBone", SITTING , statesBackBone};

/**
* @var back_buffer
* @brief Is the buffer where the current position of the user and the timestamp are stored.
*/
BACK back_buffer;
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
 * @brief Gets and stores the user position from the hal in the buffer "user_position".
 * @par
 */
void BACK_CONTROL_getUserPosition(){

	user_position.current = REFRESH_HW_refreshPosition();

}


/**
* @brief Event of the state machine to check the transition from "standing" to "sitting"
* @par
* @return BOOLEAN (event activated or not)
*/
 BOOLEAN BACK_CONTROL_ev_standing_to_sitting(){
	 BOOLEAN ret = 0;

	 if(user_position.current == SITTING){
		 ret = TRUE;
	 }else{
		 ret = FALSE;
	 }

 	return ret;
 }

 /**
 * @brief Action performed when the event "standing_to_sitting_wrong" has been activated
 * @par
 */
 void BACK_CONTROL_acc_standing_to_sitting(){
	 displayed = FALSE;
	 back_buffer.data[0] = '0';
	 BACK_setBack(back_buffer);

  }
 /**
  * @brief Function performed while being in the state "standing".
  * @par
  * @todo Implement code to be executed while the user is standing.
  */
 void BACK_CONTROL_do_standing(){

	 //printf("Im standing\n\r");
  }


 /**
 * @brief Event of the state machine to check the transition from "moving fast" to "sitting"
 * @par
 * @return BOOLEAN (event activated or not)
 */
 BOOLEAN BACK_CONTROL_ev_moving_fast_to_sitting(){
	 BOOLEAN ret = 0;

	 if(user_position.current == SITTING){
		 ret = TRUE;
	 }else{
		 ret = FALSE;
	 }

 	return ret;
 }

 /**
 * @brief Action performed when the event "moving_fast_to_sitting" has been activated
 * @par
 */
 void BACK_CONTROL_acc_moving_fast_to_sitting(){
	 displayed = FALSE;
	 back_buffer.data[0] = '0';
	 BACK_setBack(back_buffer);

  }

 /**
 * @brief Event of the state machine to check the transition from "moving fast" to "standing"
 * @par
 * @return BOOLEAN (event activated or not)
 */
 BOOLEAN BACK_CONTROL_ev_moving_fast_to_standing(){
 	 BOOLEAN ret = 0;

 	 if(user_position.current == STANDING){ //if we press it, we will be standing
 		 ret = TRUE;
 	 }else{
 		 ret = FALSE;
 	 }

  	return ret;
  }

 /**
 * @brief Action performed when the event "moving_fast_to_standing" has been activated
 * @par
 */
  void BACK_CONTROL_acc_moving_fast_to_standing(){
	  displayed = FALSE;
 	 back_buffer.data[0] = '1';
 	 BACK_setBack(back_buffer);

   }

  /**
   * @brief Function performed while being in the state "moving fast"
   * @par
   * @todo Implement code to be executed while the user is moving fast.
   */
 void BACK_CONTROL_do_moving_fast(){

	 //printf("Im moving fast\n\r");

  }

 /**
 * @brief Event of the state machine to check the transition from "sitting" to "moving fast"
 * @par
 * @return BOOLEAN (event activated or not)
 */
 BOOLEAN BACK_CONTROL_ev_sitting_to_moving_fast(){
	 BOOLEAN ret = 0;

	 if(user_position.current == MOVINGFAST){
		 ret = TRUE;
	 }else{
		 ret = FALSE;
	 }

 	return ret;
 }

 /**
 * @brief Action performed when the event "sitting_to_moving_fast" has been activated
 * @par
 */
 void BACK_CONTROL_acc_sitting_to_moving_fast(){
	 displayed = FALSE;
	 back_buffer.data[0] = '3';
	 BACK_setBack(back_buffer);
  }

 /**
  * @brief Function performed while being in the state "sitting"
  * @par
  * @todo Implement code to be executed while the user is sitting.
  */
 void BACK_CONTROL_do_sitting(){

	 //printf("Im sitted\n\r");
   }

 /**
 * @brief Event of the state machine to check the transition from "standing" to "sitting"
 * @par
 * @return BOOLEAN (event activated or not)
 */
 BOOLEAN BACK_CONTROL_ev_sitting_to_standing(){

	 BOOLEAN ret = 0;
	 if(user_position.current == STANDING){
		 ret = TRUE;
	 }else{
		 ret = FALSE;
	 }

 	return ret;
 }

 /**
 * @brief Action performed when the event "sitting_to_standing" has been activated
 * @par
 */
  void BACK_CONTROL_acc_sitting_to_standing(){
	  displayed = FALSE;
	  back_buffer.data[0] = '1';
	  BACK_setBack(back_buffer);

  }

  /**
  * @brief Action performed when the event "sitting_to_sitting_wrong" has been activated
  * @par
  */

  void BACK_CONTROL_acc_sitting_to_sitting_wrong(){
	  displayed = FALSE;
	  back_buffer.data[0] = '2';
	  BACK_setBack(back_buffer);

  }

  /**
  * @brief Event of the state machine to check the transition from "sitting" to "sitting wrong"
  * @par
  * @return BOOLEAN (event activated or not)
  */
  BOOLEAN BACK_CONTROL_ev_sitting_to_sitting_wrong(){

 	 BOOLEAN ret = 0;

 	 if(user_position.current == SITTINGWRONG){ //si no lo presionamos, vamos a estar sentados
 		ret = TRUE;
 	 }else{
 		ret = FALSE;
 	 }

  	return ret;
  }


  /**
  * @brief Action performed when the event "sitting_wrong_to_sitting" has been activated
  * @par
  */
  void BACK_CONTROL_acc_sitting_wrong_to_sitting(){
	  displayed = FALSE;
	  back_buffer.data[0] = '0';
	  BACK_setBack(back_buffer);

  }

  /**
  * @brief Event of the state machine to check the transition from "sitting wrong" to "sitting"
  * @par
  * @return BOOLEAN (event activated or not)
  */
  BOOLEAN BACK_CONTROL_ev_sitting_wrong_to_sitting(){

 	 BOOLEAN ret = 0;

 	 if(user_position.current == SITTING){ //si no lo presionamos, vamos a estar sentados
 		ret = TRUE;
 	 }else{
 		ret = FALSE;
 	 }

  	return ret;
  }
  /**
  * @brief Action performed when the event "sitting_wrong_to_standing" has been activated
  * @par
  */
  void BACK_CONTROL_acc_sitting_wrong_to_standing(){

	  displayed = FALSE;
	  back_buffer.data[0] = '1';
	  BACK_setBack(back_buffer);

  }

  /**
  * @brief Event of the state machine to check the transition from "sitting wrong" to "standing"
  * @par
  * @return BOOLEAN (event activated or not)
  */
  BOOLEAN BACK_CONTROL_ev_sitting_wrong_to_standing(){

 	 BOOLEAN ret = 0;

 	 if(user_position.current == STANDING){ //estamos mal sentados y nos ponemos de pie
 		ret = TRUE;
 	 }else{
 		ret = FALSE;
 	 }

  	return ret;
  }

  /**
   * @brief Function performed while being in the state "sitting wrong"
   * @par
   * @todo Implement code to be executed while the user is sitting wrong.
   */
  void BACK_CONTROL_do_sitting_wrong(){

	  //printf("Im sitting wrong\n\r");
  }


  /**
   * @brief Visualizes back information and switch on leds depending on position.
   * @par
   * @param string to store with the back state and current timestamp.
   */
  void BACK_CONTROL_visualize_back(){

	  char str_display[50], strTime[50];
	  int leds;
	  BACK current_back = BACK_getBack();
	  sscanf(current_back.data, "%d", &leds);
	  switch(user_position.current){

	  case SITTING: 		sprintf(str_display, "User sitting\r\n");
	  	  	  	  			//LEDS_SERVICES_changeState(leds);
	  	  	  	  			break;

	  case STANDING: 		sprintf(str_display, "User standing\r\n");
	  	  	  	  	 		//LEDS_SERVICES_changeState(leds);
	  	  	  	  	 		break;

	  case SITTINGWRONG: 	sprintf(str_display, "User sitting wrong\r\n");
	  	  	  	  	  	 	//LEDS_SERVICES_changeState(leds);
	  	  	  	  	  	 	break;

	  case MOVINGFAST: 		sprintf(str_display, "User moving fast\r\n");
	  	  	  	  	   	    //LEDS_SERVICES_changeState(leds);
	  	  	  	  	   	    break;

	  default: 				sprintf(str_display, "Undefined state");


	  }

	  //This condition keeps track of whether the current state of the user has to be displayed or its already been diplayed.
	  if(!displayed) {
		  //ANALYSE_POSITION_getCurrentTime(strTime);
		  //sprintf(str_display, "%s %s",str_display,strTime);
		  printf("--------%s\n",str_display);
		  //DISPLAY_printString(str_display);
		  displayed = TRUE;
	  }

	  return;
  }

  /**
  * @brief Returns the backBone state machine.
  * @par
  * @return TS_MACHINE (state machine data structure).
  */
  TS_MACHINE BACK_CONTROL_getBackBone(){

   	return backBone;

  }

  /***************************************************************************
   **                                                                       **
   **                      EOF                                              **
   **                                                                       **
   ***************************************************************************/



