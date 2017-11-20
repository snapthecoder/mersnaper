/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_CONFIG_HAS_RTOS
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
  #include "FRTOS1.h"
  #include "RTOS.h"
#if PL_CONFIG_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
#endif
#if PL_CONFIG_HAS_MOTOR
  #include "Motor.h"
	#include "DIRR.h"
	#include "DIRL.h"
	#include "PWMR.h"
	#include "PWML.h"
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


void DriveTask (void *pvParameters){
	  (void)pvParameters; /* not used */
	  DIRL_PutVal(0);
	  DIRR_PutVal(1);
	 // DirLPutVal(MOT_DIR_FORWARD);
	  //DirLPutVal(MOT_DIR_FORWARD);
	  for(;;) {
		  APP_Drive();
		  FRTOS1_vTaskDelay(pdMS_TO_TICKS(30));
	  }

}
void MyAPPTask (void *pvParam){
	   for(;;) {
		#if PL_CONFIG_HAS_DEBOUNCE
		   KEYDBNC_Process();
		#else
		   KEY_Scan(); /* scan keys and set events */
		#endif
		//WAIT1_WaitOSms(50);
		FRTOS1_vTaskDelay(pdMS_TO_TICKS(10));
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

#endif

void RTOS_Init(void) {
  /*! \todo Create tasks here */
	 BaseType_t res ;
	xTaskHandle taskHndl ;
	#if PL_LOCAL_CONFIG_BOARD_IS_ROBO & PL_CONFIG_HAS_REFLECTANCE
	res= FRTOS1_xTaskCreate(DriveTask,"Drive",200, NULL,tskIDLE_PRIORITY,&taskHndl);
	#endif
	res= FRTOS1_xTaskCreate(MyAPPTask,"APP",200, NULL,tskIDLE_PRIORITY+1,&taskHndl);
	//res= FRTOS1_xTaskCreate(MyAPPTask,"ReflTask",200, NULL,tskIDLE_PRIORITY+1,&taskHndl);

	 if ( res !=pdPASS) { }

}

void RTOS_Deinit(void) {
  /* nothing needed for now */
}

