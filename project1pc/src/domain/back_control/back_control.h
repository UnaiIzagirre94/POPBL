/**
****************************************************************************
* @file			back_control.h
*
* @version		0.1.0
* @date			2016-11-21
****************************************************************************
* @author		Izagirre, Unai
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |     Revised by   |  Description
*  --------- | ------------ | ---------------- | ----------------------------
*    0.1.0   | 2016-11-21   |    uizagirre     | Original version

****************************************************************************/
/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/
#include "config.h"
#include "state_machine.h"

/***************************************************************************
 **                                                                       **
 **                      DEFINITIONS AND MACROS                           **
 **                                                                       **
 ***************************************************************************/
#ifndef BACKCONTROL_H_
#define BACKCONTROL_H_



/***************************************************************************
 **                                                                       **
 **                      TYPEDEFS AND STRUCTURE                           **
 **                                                                       **
 ***************************************************************************/
  /**
  * @struct POSITION Will store the current position of the user with an integer value.
  */
typedef struct {
	int current;
}POSITION;
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

void BACK_CONTROL_getUserPosition();
TS_MACHINE BACK_CONTROL_getBackBone();
void BACK_CONTROL_visualize_back();

void BACK_CONTROL_acc_standing_to_sitting();
void BACK_CONTROL_acc_moving_fast_to_sitting();
void BACK_CONTROL_acc_moving_fast_to_standing();
void BACK_CONTROL_acc_sitting_to_standing();
void BACK_CONTROL_acc_sitting_to_moving_fast();
void BACK_CONTROL_acc_sitting_wrong_to_sitting();
void BACK_CONTROL_acc_sitting_to_sitting_wrong();
void BACK_CONTROL_acc_sitting_wrong_to_standing();

void BACK_CONTROL_do_standing();
void BACK_CONTROL_do_sitting();
void BACK_CONTROL_do_sitting_wrong();
void BACK_CONTROL_do_moving_fast();

BOOLEAN BACK_CONTROL_ev_standing_to_sitting();
BOOLEAN BACK_CONTROL_ev_moving_fast_to_sitting();
BOOLEAN BACK_CONTROL_ev_moving_fast_to_standing();
BOOLEAN BACK_CONTROL_ev_sitting_to_standing();
BOOLEAN BACK_CONTROL_ev_sitting_to_moving_fast();
BOOLEAN BACK_CONTROL_ev_sitting_wrong_to_sitting();
BOOLEAN BACK_CONTROL_ev_sitting_to_sitting_wrong();
BOOLEAN BACK_CONTROL_ev_sitting_wrong_to_standing();


/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/

#endif /* BACKCONTROL_H_ */
