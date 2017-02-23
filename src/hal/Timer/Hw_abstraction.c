/**
****************************************************************************                                   
* @file			Hw_abstraction.c                                     
* @brief 		File general description                                     
* @version		0.1.0                                                     
* @date			2016-11-01                                                
****************************************************************************
* @author		Allende, Imanol                                            
* @copyright	                                         
****************************************************************************
* @par Version history                                                     
* @par                                                                     
*  Version   | Date         |  Revised by   |  Description                 
*  --------- | ------------ | ------------- | ----------------------------                
*    0.1.0   | 2016-11-01   |  iallende     | Original version             
****************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/
 
#include "config.h"
#ifdef ZYNQ_7000
#include "platform.h"
#include "xil_printf.h"
#include "xscutimer.h"
#include "xscugic.h"
#endif

#include "Hw_abstraction.h"

/***************************************************************************
 **                                                                       **
 **                      DEFINITIONS AND MACROS                           **
 **                                                                       **
 ***************************************************************************/
 
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define TIMER_DEVICE_ID		XPAR_SCUTIMER_DEVICE_ID
#define INTC_BASE_ADDR		XPAR_SCUGIC_CPU_BASEADDR
#define INTC_DIST_BASE_ADDR	XPAR_SCUGIC_DIST_BASEADDR
#define TIMER_IRPT_INTR		XPAR_SCUTIMER_INTR

static unsigned int count=0;
static float step = 0;
static XScuTimer timerInstance;

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
static void HW_ABSTRACTION_enableInterrupts();
static void HW_ABSTRACTION_setupInterrupts();
static void HW_ABSTRACTION_setupTimer(int msecs);
void HW_ABSTRACTION_timerCallback(XScuTimer * timerInstance);

/***************************************************************************
 **                                                                       **
 **                      LOCAL FUNCTIONS                                  **
 **                                                                       **
 ***************************************************************************/

/**
* @brief Inits the Urt
* @par 	Inits the Zynq's UART
* @param Empty
* @return Nothing
*/
void HW_ABSTRACTION_initUART(){
#ifdef ZYNQ_7000
	init_platform();
#endif
}

/**
* @brief Init of the Timer
* @par 	Executes thre functions
* @param miliseconds
* @return Nothing
*/
void HW_ABSTRACTION_initTimer(unsigned int msecs){
	HW_ABSTRACTION_setupTimer(msecs);
	HW_ABSTRACTION_setupInterrupts();
	HW_ABSTRACTION_enableInterrupts();
}

/**
* @brief Gets the step 
* @param Empty
* @return the step value
*/
unsigned int HW_ABSTRACTION_getStep(){
	return step;
}

/**
* @brief The timer's counter
* @param Empty
* @return count of the timer
*/
unsigned int HW_ABSTRACTION_getTimerCount(){
	return count;
}

/**
* @brief Enable´s the interrupt of the Zynq
* @param Empty
* @return Nothing
*/
static void HW_ABSTRACTION_enableInterrupts(){
	/* Enable non-critical exceptions.*/
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
	XScuTimer_EnableInterrupt(&timerInstance);
	XScuTimer_Start(&timerInstance);
	return;
}

/**
* @brief Configures the interrupts
* @par 	Configures the timer of the HW 
* @param Empty
* @return Nothing
*/
static void HW_ABSTRACTION_setupInterrupts(){
#ifdef ZYNQ_7000
	Xil_ExceptionInit();

	XScuGic_DeviceInitialize(INTC_DEVICE_ID);

	/*Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor*/
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
			(Xil_ExceptionHandler)XScuGic_DeviceInterruptHandler,
			(void *)INTC_DEVICE_ID);
	/*Connect the device driver handler that will be called when an interrupt for the device occurs, the handler defined above performs
	the specific interrupt processing for the device.*/
	XScuGic_RegisterHandler(INTC_BASE_ADDR, TIMER_IRPT_INTR,
			(Xil_ExceptionHandler)HW_ABSTRACTION_timerCallback,
			(void *)&timerInstance);
	/*Enable the interrupt for scu timer.*/
	XScuGic_EnableIntr(INTC_DIST_BASE_ADDR, TIMER_IRPT_INTR);
#endif
	return;
}

/**
* @brief Setups the timer
* @par 	Setups Zynq's timer
* @param miliseconds
* @return Nothing
*/
static void HW_ABSTRACTION_setupTimer(int msecs){
	int status = XST_SUCCESS;
	XScuTimer_Config *ptrConfig;
	int timerLoadValue = 0;
	step = 1000/msecs;
	ptrConfig = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
	status = XScuTimer_CfgInitialize(&timerInstance, ptrConfig,
			ptrConfig->BaseAddr);
	if (status != XST_SUCCESS) {
		xil_printf("In %s: Scutimer Cfg initialization failed...\r\n",
		__func__);
		return;
	}

	status = XScuTimer_SelfTest(&timerInstance);
	if (status != XST_SUCCESS) {
		xil_printf("In %s: Scutimer Self test failed...\r\n",
		__func__);
		return;
	}

	XScuTimer_EnableAutoReload(&timerInstance);
	/*Divided by 2 because the timer frequency is the half of the CPU*/
	timerLoadValue = XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / ( step * 2 );
	XScuTimer_LoadTimer(&timerInstance, timerLoadValue);
	return;
}


/**
* @brief Clears the Interupt status
* @par 	timer callback  
* @param pointer to the timer
* @return Nothing
*/
void HW_ABSTRACTION_timerCallback(XScuTimer * timerInstance){
	count++;
	SCHEDULER_update();
	XScuTimer_ClearInterruptStatus(timerInstance);

}
 
/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/
