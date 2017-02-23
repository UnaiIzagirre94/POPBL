/**
****************************************************************************
* @file			scheduler.c
* @brief 		Scheduler to manage the periodic tasks.
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
*    0.1.0   | 2016-12-11   |  uizagirre    | Original version
****************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/
#include "scheduler.h"

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

STASK tasks[SCHEDULE_TASK_MAX];

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

/**
 * @brief Deletes a task from the Scheduler
 * @par
 * @param[in] task id to be deleted
 */

static void SCHEDULER_deleteTask(int i){
	tasks[i].Delay = 0;
	tasks[i].Period = 0;
	tasks[i].RunMe = 0;
	tasks[i].pFunction = 0;//NULL
}

void SCHEDULER_backgroundTask(){

}

/**
 * @brief Adds a task to the Scheduler
 * @par
 * @param[in] *pFunction: Pointer to the function of the task
 * @param[in] period: period in which the task will be executed
 * @param[in] delay: the delay of the task.
 */
void SCHEDULER_addTask( void (*pFunction)(void) , int period, int delay){
	unsigned char Index = 0;
	// First find a gap in the array (if there is one)
	while (( tasks[Index].pFunction != 0) && (Index < SCHEDULE_TASK_MAX))
	{
		Index++;
	}
	// Have we reached the end of the list?
	//if (Index == SCHEDULE_TASK_MAX)
	//{
	// Task list is full
	//
	// Set the global error variable
	//Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
	// Also return an error code
	//return SCH_MAX_TASKS;
	//}
	// If we're here, there is a space in the task array
	tasks[Index].pFunction = pFunction;
	tasks[Index].Delay = delay;
	tasks[Index].Period = period;
	tasks[Index].RunMe = 0;
//	return Index; // return position of task (to allow later deletion)
//}
}

/**
 * @brief Updates the state of the scheduler
 * @par
 * @param Empty
 */
void SCHEDULER_update(){
	int i = 0;
	for (i = 0 ; i < SCHEDULE_TASK_MAX ; i++){
		if ( tasks[i].pFunction){
			if ( tasks[i].Delay == 0 ){
				tasks[i].RunMe += 1;
				if (tasks[i].Period ){
					tasks[i].Delay = tasks[i].Period;
				}
			}else{
				tasks[i].Delay -= 1;
			}
		}
	}
}

/**
 * @brief Initializes the scheduler
 * @par
 */
void SCHEDULER_init(){
	//aqui iniciaria el systick. Ya veremos esto.
	int i = 0;
	//125ns
	//SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_8MHZ);


	for (i=0; i < SCHEDULE_TASK_MAX ; i++){
		SCHEDULER_deleteTask(i);
	}
}

/**
 * @brief Main engine of the scheduler
 * @par
 */
void SCHEDULER_schedule(){
	unsigned char Index;
	// Dispatches (runs) the next task (if one is ready)
	for (Index = 0; Index < SCHEDULE_TASK_MAX; Index++)
	{
		if ( tasks[Index].RunMe > 0){
			(*tasks[Index].pFunction)(); // Run the task
			 tasks[Index].RunMe -= 1; // Reset / reduce RunMe flag
			// Periodic tasks will automatically run again
			// - if this is a 'one shot' task, remove it from the array
			if ( tasks[Index].Period == 0){
				SCHEDULER_deleteTask(Index);
			}
		}
	}
	// Report system status
	//SCH_Report_Status();
	// The scheduler enters idle mode at this point
	//SCH_Go_To_Sleep()
}

/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/
