
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "Board_LED.h"                  // ::Board Support:LED

/*----------------------------------------------------------------------------
 *      Thread 1 'LED0_THREAD': LED thread
 *---------------------------------------------------------------------------*/
 
void LED0_THREAD (void const *argument);                 // thread function
osThreadId tid_LED0_THREAD;                              // thread id
osThreadDef(LED0_THREAD, osPriorityNormal, 1, 0);        // thread object


void LED1_THREAD (void const *argument);                 // thread function
osThreadId tid_LED1_THREAD;                              // thread id
osThreadDef(LED1_THREAD, osPriorityNormal, 1, 0);        // thread object


osSemaphoreDef(sem1);
osSemaphoreId sem1ID;

int Initialize_LED0_THREAD (void) {

  
	sem1ID = osSemaphoreCreate(osSemaphore(sem1),1);
	tid_LED0_THREAD = osThreadCreate(osThread(LED0_THREAD), NULL);
	tid_LED1_THREAD = osThreadCreate(osThread(LED1_THREAD), NULL);
}

void LED0_THREAD (void const *argument) {
  
	for(;;)
	{
		osSemaphoreWait(sem1ID,osWaitForever);
		LED_On(3);
		osDelay(3000);
		LED_Off(3);
		osDelay(100);
		osSemaphoreRelease(sem1ID);
	}

	
}


void LED1_THREAD (void const *argument) {
  
	for(;;)
	{
		osSemaphoreWait(sem1ID,osWaitForever);
		LED_On(2);
		osDelay(200);
		LED_Off(2);
		osDelay(1000);
		osSemaphoreRelease(sem1ID);
	}

	
}



