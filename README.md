/**	@mainpage Project: BackSense project.
@brief Repository of code for the POPBL project of the BackBone control and monitorization
@version v1.1
@date 2017-2-19
@par Description
	Repository for the POPBL
			
@par DocStrategy
@par
	This C project consists on three main periodic tasks. The tasks are created in the main() function of the app_back.c file. Checking that file would be the best way to start analising the source code. Apart from creating (SCHEDULER_addTask()) and calling to those three periodic tasks, the required hardware is initialized and the task scheduler (SCHEDULER_schedule()) is started.
@par
	The first periodic task STATE_ANALYSE_task() reads the current state of the sensors and stores the information in a buffer ([Back] (file:///C:/MEJORA_Y_MANTENIMIENTO/html/struct_b_a_c_k.html) buffer). Then the STORE_DATA_storeInfo() function (second periodic task) reads the ([Back] (file:///C:/MEJORA_Y_MANTENIMIENTO/html/struct_b_a_c_k.html) buffer and stores the information in the SD card STORE_storeInSD() and finally, the third periodic task VISUALIZE_DATA_visualize() reads the data stored in the SD card and displays it in a VGA monitor.
@par
	The periodic tasks described above are managed by a scheduler and one of the periodic tasks (STATE_ANALYSE_task()) implements a state machine in order to keep track of the current position of the user. That position and the current timestamp is the actual information that will be stored first in the ([Back] (file:///C:/MEJORA_Y_MANTENIMIENTO/html/struct_b_a_c_k.html) buffer and then in the SD card.
@par
	Although all the C files and the functions which were implemented in the POPBL were commented, the following list is a sum up of the most important parts of the code that will help to get a general idea of the project:

	- There are some functions that haven't been implemented yet in the state machine (back_control.c file). So they were added to the Todo list.

	- The back_control.c file, is one of the most important files in the project, because it implements the functions to be executed by the [TS_MACHINE] (file:///C:/MEJORA_Y_MANTENIMIENTO/html/struct_t_s___m_a_c_h_i_n_e.html) backBone state machine. All the functions as well as variables of this important file were commented.

	- The most important data structure of the project (the [Back] (file:///C:/MEJORA_Y_MANTENIMIENTO/html/struct_b_a_c_k.html) buffer) was commented.

	- One of the most relevant functions is the one that stores the information in the SD card and was also commented (STORE_storeInSD()).

	- The function that decides the frequency in which data is stored in the SD card is STORE_DATA_storeInfo(). This function is one of the most critical functions in the code, because if the frequency in which we store the data is too high, the microprocessor is not able to open and close the file of the SD card fast enough and new data coming from the sensors may be lost. The frequency in which data is stored in the SD is decided by the length of a global buffer's length. When the buffer is full, all the data is stored in the SD card at once. That way we don't have to open and close the file every time we get a new value from the sensors. has an alias (improveThis=todo) implemented. The purpose of it is to express that the function is implemented but could be improved in the future.

	- The function STATE_MACHINE_execute(TS_MACHINE *theMachine) is the one that executes the state machine. The best way to understand a state machine, is to represent it as an image. Therefore an image of the actual state machine was added to the function comments, for the better understanding of the functionality.

	- Finally, notice that some directories have been excluded from the html, as they don't play a relevant role in the comprehension of the code and weren't commented (hal and extern_libs directories).

@par Changes made in the base configuration of Doxygen
@par

1. Add the POPBL logo of BackSense to PROJECT_LOGO.

2. Add an Alias (improveThis) in ALIASES to specify the parts of the code that are implemented but should be improved.

3. Exclude some directories that haven't been implemented in this project to make the docummentation cleaner.

4. Include an image for the better understanding of the state machine in IMAGE_PATH.


@par SRC file organization
@par 
All the files are placed inside the src folder divided in the following 5 subdirectories.
@par
 	1.- app => Contains the main (app_back.c) for the scheduler and the different periodic tasks.
  		 - State_analyse => Periodic task that analyses the position of the user. Implemented with a State Machine. (sitting, standing, sitting wrong and moving fast).
 		 - Store_data => Periodic task that saves the recorded data in the SD Card.
 		 - Visualize_data => Periodic task that visualizes the current position of the user and the timestamp where that information was changed from a previous state.
@par
    2.- domain => Code that belongs to this application and interacts with the hal layer.
 		 - Back_control => Definition of the state machine for the backbone application and implementation of the event-action functions.
 		 - Analyse_position => Executes the state machine and checks the current state of the user.
  		 - Back => Buffer for communication between tasks.Receives the data from the HAL and calls Hal functions to store its data in the SD card.
@par
 	3.- extern_libs => 3rd party libraries.
@par
 	4.- hal => Code that interacts with the hardware.
 		 - Buttons => reads the state of the buttons of the Zybo board. It is used to the calibration states.
 		 - Display => to print in the screen. In this case the form of the backbone
 		 - Keyboard => to read from the uart. Not used yet. 
 		 - Timer => counter of ticks
 		 - Leds => to change state of leds on/off.
 		 - Refresh_hw => refreshes needed information from the hardware and returns it to the domain.
 		 - Store_SD => stores data in the SD card.
@par
 	5.- libs => Reusable code for other applications.
 		 - State Machine => The engine of the state machine.
 		 - Scheduler => The engine of the task scheduler.
  
