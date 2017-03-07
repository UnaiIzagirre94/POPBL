/**
****************************************************************************
* @file			app_back.c
* @brief 		Main file of the app.
* @version		0.1.0
* @date			2016-12-10
****************************************************************************
* @author		Izagirre, Unai
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |  Revised by   |  Description
*  --------- | ------------ | ------------- | ----------------------------
*    0.1.0   | 2016-12-10   |  uizagirre    | Original version
****************************************************************************/


#include "Back.h"
#include "scheduler.h"
#include "state_analyse.h"
#include "store_data.h"
#include "visualize_data.h"

#define APP_BACK_C


/**
* @brief Main function of the app. We initialize the hardware and the Scheduler and enter in the main loop to execute and update the Sceduler.
* @par
*/
int main()
{
	//Initialization.
	BACK_init();

	//Create the tasks.
	SCHEDULER_addTask( STATE_ANALYSE_task , 1, 5);      //Periodico = 1 (tarea periodica) / Delay = 10 = 10ms = 0,01s //estaba en 1
	SCHEDULER_addTask( STORE_DATA_storeInfo, 1, 10);    //Periodico = 1 (tarea periodica) / Delay = 10 = 100ms = 0,1s
	SCHEDULER_addTask( VISUALIZE_DATA_visualize, 1, 50);//Periodico = 1 (tarea periodica) / Delay = 10 = 20ms = 0,02s

	//Main loop.
	while(1){

		SCHEDULER_schedule();

   }
   return 0;
}







