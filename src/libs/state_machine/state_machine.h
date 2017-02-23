/**
****************************************************************************
* @file			State_machine.h
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

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

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
 **                      TYPEDEFS AND STRUCTURE                           **
 **                                                                       **
 ***************************************************************************/

typedef void	 (*TPFN_ACC)(void); /* Pointer to an action function */
typedef BOOLEAN	 (*TPFN_EVE)(void); /* Pointer to an event function */

/**
* @struct TS_EVEACC Stores the event to be fired, the name of the event, the action to be executed when fires the event state and the next state to be executed.
*/
typedef struct {
	  int		   idNextState;    /* Identifier of next state */
	  char        *name;           /* Name for debug */
	  TPFN_EVE     event;          /* Pointer to an event function */
	  TPFN_ACC     action;         /* Pointer to an action function */
} TS_EVEACC;

/**
* @struct TS_STATE Stores the states of a state machine. It stores de Id of the state, the name, the function to be executed while the state machine is in this current state and the transition to the next state.
*/
typedef struct {
	  int		   id;             /* Identifier of state */
	  char        *name;           /* Name for debug */
	  TPFN_ACC     controls;      /* Control function of state (DO) */
	  TS_EVEACC   *transitions;    /* Pointer of the transitions */
}TS_STATE;

/**
* @struct TS_MACHINE Stores the state machine. Stores the Id of the state machine, the name, the Id of the current state and the states it can be in.
*/
typedef struct {
	  int		   id;               /* Identifier of the machine */
	  char        *name;             /* Name for debug */
	  int		   idCurrentState;   /* Actual state identifier */
	  TS_STATE    **states;          /* array  of STATES */
} TS_MACHINE;


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



#endif /* STATE_MACHINE_H_ */

/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/

