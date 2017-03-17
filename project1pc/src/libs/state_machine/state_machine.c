/**
****************************************************************************
* @file			State_machine.c
* @brief 		State machine engine.
* @version		0.1.0
* @date			2016-11-21
****************************************************************************
* @author		Izagirre, Unai
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |  Revised by        |  Description
*  --------- | ------------ | -----------------  | ----------------------------
*    0.1.0   | 2016-11-21   |  aarruabarrena     | Original version
*    0.1.1   | 2016-11-21   |  iallende		     | Functions added
*    0.1.2   | 2016-12-9    |  uizagirre	     | More states and evaccc added
*
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

 void STATE_MACHINE_executeState(TS_STATE *theState , TS_MACHINE *theMachine);


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

 /**
  * @brief Executes the state machine
  * @par
  * @param theMachine Pointer to the state machine to be executed
  * @image html state_machine.PNG
  */
 void STATE_MACHINE_execute(TS_MACHINE *theMachine){
	 	TS_STATE **Indx;    /* Valor indice rastreador */

	 	/* if (la_maquina->StopCond()){
	 	 * crear en la maquinaEstado StopAcc y llamarla aqui
	 	return;
	 	 */

	 	for (Indx = theMachine->states; *Indx != NULL; ++Indx){
	 		if (theMachine->idCurrentState == (*Indx)->id){
	 			STATE_MACHINE_executeState(*Indx , theMachine);
	 			return;
	 		}
	 	}
	 }

 /**
  * @brief Executes the current state of the state machine that is executing
  * @par
  * @param[in] *theState: pointer to the state to be executed | *theMachine: pointer to the state machine that is executing

  */
 void STATE_MACHINE_executeState(TS_STATE *theState , TS_MACHINE *theMachine){
 	 TS_EVEACC *Indx;   /* Indice de rastreo */

 	 theState->controls(); /* Aqui se llama a las funciones DO */

 	 	for (Indx = theState->transitions; Indx->event != NULL; ++Indx){ /* Busqueda del estado actual */
 	 		if (Indx->event() == TRUE){
 	 			if (Indx->action != NULL){ /* Mirar si accion esta vacio */
 	 				Indx->action();
 	 			}
 	 			if (Indx->idNextState != theMachine->idCurrentState){
 	 				//el_estado->exit();
 	 				theMachine->idCurrentState = Indx->idNextState;
 	 				//el_estado = busqueda estado actual (en una funcion y arriba poner el mismo) y ejecuta su entry
 	 				//el_estado->entry();
 	 				return;
 	 			}
 	 		}
 	 	}
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
