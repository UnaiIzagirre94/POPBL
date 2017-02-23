/**
****************************************************************************
* @file			scheduler.h
*
* @version		0.1.0
* @date			2016-12-11
****************************************************************************
* @author		Izagirre, Unai
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |  Revised by   |  Description
*  --------- | ------------ | ------------- | ----------------------------
*    0.1.0   | 2016-12-11   |  uizagirre     | Original version
****************************************************************************/

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

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

#define SCHEDULE_TASK_MAX 10

/***************************************************************************
 **                                                                       **
 **                      TYPEDEFS AND STRUCTURE                           **
 **                                                                       **
 ***************************************************************************/

// Store in DATA area, if possible, for rapid access
// Total memory per task is 7 bytes
typedef  struct{
	// Pointer to the task (must be a 'void (void)' function)
	void (*pFunction)(void);
	// Delay (ticks) until the function will (next) be run
	// - see SCH_Add_Task() for further details
	int Delay;
	// Interval (ticks) between subsequent runs.
	// - see SCH_Add_Task() for further details
	int Period;
	// Incremented (by scheduler) when task is due to execute
	unsigned char RunMe;
} STASK;

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

void SCHEDULER_init();
void SCHEDULER_schedule();
void SCHEDULER_backgroundTask();
/*
 * Esta serie el API simple
 */
void SCHEDULER_addTask( void (*pFunction)(void) , int period, int delay);
void SCHEDULER_update();

#endif

/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/
