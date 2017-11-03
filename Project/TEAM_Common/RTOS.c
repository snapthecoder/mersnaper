/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#include "Application.h"
#include "Event.h"
#include "LED.h"
#include "WAIT1.h"
#include "CS1.h"
#include "KeyDebounce.h"
#include "CLS1.h"
#include "KIN1.h"
#if PL_CONFIG_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_CONFIG_HAS_SHELL
  #include "CLS1.h"
  #include "Shell.h"
  #include "RTT1.h"
#endif
#if PL_CONFIG_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_CONFIG_HAS_RTOS
  #include "FRTOS1.h"
  #include "RTOS.h"
#endif
#if PL_CONFIG_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
#endif
#if PL_CONFIG_HAS_MOTOR
  #include "Motor.h"
#endif
#if PL_CONFIG_BOARD_IS_ROBO_V2
  #include "PORT_PDD.h"
#endif
#if PL_CONFIG_HAS_LINE_FOLLOW
  #include "LineFollow.h"
#endif
#if PL_CONFIG_HAS_LCD_MENU
  #include "LCD.h"
#endif
#if PL_CONFIG_HAS_SNAKE_GAME
  #include "Snake.h"
#endif
#if PL_CONFIG_HAS_REFLECTANCE
  #include "Reflectance.h"
#endif
#include "Sumo.h"

#define normalTaskStackSize (200/sizeof(StackType_t));

void RTOS_Init(void) {
  /*! \todo Create tasks here */
	 BaseType_t res ;
	xTaskHandle taskHndl ;
	res= FRTOS1_xTaskCreate(MyBlinkyTask,"Blinky",200, NULL,tskIDLE_PRIORITY,&taskHndl);
	 if ( res !=pdPASS) { }

}

void RTOS_Deinit(void) {
  /* nothing needed for now */
}

void MyBlinkyTask (void *pvParam){
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;){
		LED1_Neg();
		WAIT1_Waitms(200);
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));
	}
}
void MyAPPTask (void *pvParam){
	   for(;;) {
		#if PL_CONFIG_HAS_DEBOUNCE
		   KEYDBNC_Process();
		#else
		   KEY_Scan(); /* scan keys and set events */
		#endif
		WAIT1_WaitOSms(50);
		EVNT_HandleEvent(APP_EventHandler, TRUE);
	  }
}



void  RTOS_APP_Start(void){
	  PL_Init();
	  APP_AdoptToHardware();
	  __asm volatile("cpsid i"); /* disable interrupts */
	  __asm volatile("cpsie i"); /* enable interrupts */
	  EVNT_SetEvent(EVNT_STARTUP);
	  CLS1_SendStr("\nHello World\n", CLS1_GetStdio()->stdOut);
	  FRTOS1_vTaskStartScheduler();
}





