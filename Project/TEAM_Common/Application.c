/**
 * \file
 * \brief Main application file
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This provides the main application entry point.
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
	#include "DIRR.h"
	#include "DIRL.h"
	#include "PWMR.h"
	#include "PWML.h"
	#include "Drive.h"
	#include "Turn.h"

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
#include "Drive.h"

bool letsstart = 0;
bool has_waited = 0;

#if PL_CONFIG_HAS_EVENTS


static void BtnMsg(int btn, const char *msg) {
#if PL_CONFIG_HAS_SHELL
  #if PL_CONFIG_HAS_SHELL_QUEUE
    uint8_t buf[48];

    UTIL1_strcpy(buf, sizeof(buf), "Button pressed: ");
    UTIL1_strcat(buf, sizeof(buf), msg);
    UTIL1_strcat(buf, sizeof(buf), ": ");
    UTIL1_strcatNum32s(buf, sizeof(buf), btn);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    SHELL_SendString(buf);
  #else
    CLS1_SendStr("Button: ", CLS1_GetStdio()->stdOut);
    CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
    CLS1_SendStr(": ", CLS1_GetStdio()->stdOut);
    CLS1_SendNum32s(btn, CLS1_GetStdio()->stdOut);
    CLS1_SendStr("\r\n", CLS1_GetStdio()->stdOut);
  #endif
#endif
}

void APP_EventHandler(EVNT_Handle event) {
  /*! \todo handle events */
  switch(event) {

  case EVNT_STARTUP:
    {
      int i;
      for (i=0;i<5;i++) {
        LED1_Neg();
        WAIT1_Waitms(50);
      }
      LED1_Off();
    }
    break;

  case EVNT_LED_HEARTBEAT:
	  LED1_Neg();
	  break;
#if PL_CONFIG_NOF_KEYS>=1
  case EVNT_SW1_PRESSED:
	#if PL_LOCAL_CONFIG_BOARD_IS_ROBO & PL_CONFIG_HAS_REFLECTANCE
	  letsstart = 1;


	#endif
     BtnMsg(1, "pressed");
     break;
  case EVNT_SW1_LPRESSED:
	  //calib start or stop
	  //REF_CalibrateStartStop();
	#if PL_LOCAL_CONFIG_BOARD_IS_ROBO & PL_CONFIG_HAS_REFLECTANCE & PL_LOCAL_CONFIG_HAS_LINE_FOLLOW
		 LF_StartFollowing();
	#endif
	 BtnMsg(1, "long pressed");
     break;
  case EVNT_SW1_RELEASED:
     BtnMsg(1, "released");
     break;
#endif


#if PL_CONFIG_NOF_KEYS>=2
  case EVNT_SW2_PRESSED:
     BtnMsg(2, "pressed");
     break;
  case EVNT_SW2_LPRESSED:
     BtnMsg(2, "long pressed");
     break;
  case EVNT_SW2_RELEASED:
     BtnMsg(2, "released");
     break;
#endif
#if PL_CONFIG_NOF_KEYS>=3
  case EVNT_SW3_PRESSED:
     BtnMsg(3, "pressed");
     break;
  case EVNT_SW3_LPRESSED:
     BtnMsg(3, "long pressed");
     break;
  case EVNT_SW3_RELEASED:
     BtnMsg(3, "released");
     break;
#endif
#if PL_CONFIG_NOF_KEYS>=4
  case EVNT_SW4_PRESSED:
     BtnMsg(4, "pressed");
     break;
  case EVNT_SW4_LPRESSED:
     BtnMsg(4, "long pressed");
     break;
  case EVNT_SW4_RELEASED:
     BtnMsg(4, "released");
     break;
#endif
#if PL_CONFIG_NOF_KEYS>=5
  case EVNT_SW5_PRESSED:
     BtnMsg(5, "pressed");
     break;
  case EVNT_SW5_LPRESSED:
     BtnMsg(5, "long pressed");
     break;
  case EVNT_SW5_RELEASED:
     BtnMsg(5, "released");
     break;
#endif
#if PL_CONFIG_NOF_KEYS>=6
  case EVNT_SW6_PRESSED:
     BtnMsg(6, "pressed");
     break;
  case EVNT_SW6_LPRESSED:
     BtnMsg(6, "long pressed");
     break;
  case EVNT_SW6_RELEASED:
     BtnMsg(6, "released");
     break;
#endif
#if PL_CONFIG_NOF_KEYS>=7
  case EVNT_SW7_PRESSED:
     BtnMsg(7, "pressed");
     break;
  case EVNT_SW7_LPRESSED:
     BtnMsg(7, "long pressed");
     break;
  case EVNT_SW7_RELEASED:
     BtnMsg(7, "released");
     break;
#endif
    default:
      break;
   } /* switch */
}
#endif /* PL_CONFIG_HAS_EVENTS */

#if PL_CONFIG_HAS_MOTOR /* currently only used for robots */
static const KIN1_UID RoboIDs[] = {
  /* 0: L20, V2 */ {{0x00,0x03,0x00,0x00,0x67,0xCD,0xB7,0x21,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}},
  /* 1: L21, V2 */ {{0x00,0x19,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4E,0x45,0x27,0x99,0x10,0x02,0x00,0x25}},
  /* 2: L4, V1  */ {{0x00,0x10,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4E,0x45,0x27,0x99,0x10,0x02,0x00,0x25}},
  /* 3: L23, V2 */ {{0x00,0x0A,0x00,0x00,0x67,0xCD,0xB8,0x21,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}},
  /* 4: L11, V2 */ {{0x00,0x19,0x00,0x00,0x67,0xCD,0xB9,0x11,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}},
  /* 5: L5, V2 */  {{0x00,0x38,0x00,0x00,0x67,0xCD,0xB5,0x41,0x4E,0x45,0x32,0x15,0x30,0x02,0x00,0x13}},
  /* 6: L3, V1 */  {{0x00,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4E,0x45,0x27,0x99,0x10,0x02,0x00,0x0A}},
  /* 7: L1, V1 */  {{0x00,0x19,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4E,0x45,0x27,0x99,0x10,0x02,0x00,0x25}},
};
#endif

void APP_AdoptToHardware(void) {
  KIN1_UID id;
  uint8_t res;

  res = KIN1_UIDGet(&id);
  if (res!=ERR_OK) {
    for(;;); /* error */
  }
#if PL_CONFIG_HAS_MOTOR
  if (KIN1_UIDSame(&id, &RoboIDs[0])) { /* L20 */
#if PL_CONFIG_HAS_QUADRATURE
    (void)Q4CRight_SwapPins(FALSE);
#endif
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert left motor */
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TRUE); /* invert left motor */
  } else if (KIN1_UIDSame(&id, &RoboIDs[1])) { /* V2 L21 */
	MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert right motor */
	#if PL_CONFIG_HAS_QUADRATURE
		(void)Q4CLeft_SwapPins(TRUE);
		(void)Q4CRight_SwapPins(TRUE);
	#endif
  } else if (KIN1_UIDSame(&id, &RoboIDs[2])) { /* V1 L4 */
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* revert left motor */
#if PL_CONFIG_HAS_QUADRATURE
    (void)Q4CLeft_SwapPins(TRUE);
    (void)Q4CRight_SwapPins(TRUE);
#endif
  } else if (KIN1_UIDSame(&id, &RoboIDs[3])) { /* L23 */
#if PL_CONFIG_HAS_QUADRATURE
    (void)Q4CRight_SwapPins(FALSE);
#endif
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert left motor */
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TRUE); /* invert left motor */
  } else if (KIN1_UIDSame(&id, &RoboIDs[4])) { /* L11 */
#if PL_CONFIG_HAS_QUADRATURE
    (void)Q4CRight_SwapPins(FALSE);
#endif
  } else if (KIN1_UIDSame(&id, &RoboIDs[5])) { /* L5, V2 */
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TRUE); /* invert right motor */
    (void)Q4CRight_SwapPins(FALSE);
  } else if (KIN1_UIDSame(&id, &RoboIDs[6])) { /* L3, V1 */
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert right motor */
#if PL_CONFIG_HAS_QUADRATURE
    (void)Q4CLeft_SwapPins(FALSE);
    (void)Q4CRight_SwapPins(FALSE);
#endif
  } else if (KIN1_UIDSame(&id, &RoboIDs[7])) { /* L1, V1 */
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert right motor */
#if PL_CONFIG_HAS_QUADRATURE
    (void)Q4CLeft_SwapPins(FALSE);
    (void)Q4CRight_SwapPins(FALSE);
#endif
  }
#endif
#if PL_CONFIG_HAS_QUADRATURE && PL_CONFIG_BOARD_IS_ROBO_V2
  /* pull-ups for Quadrature Encoder Pins */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 10, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 10, PORT_PDD_PULL_ENABLE);
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 11, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 11, PORT_PDD_PULL_ENABLE);
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 16, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 16, PORT_PDD_PULL_ENABLE);
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 17, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 17, PORT_PDD_PULL_ENABLE);
#endif
}

DriveState status = REF_LINE_NONE;
int front;
int back;
int right;
int left;


void APP_Drive(void){

	status = REF_GetLineKind();

	front = DIST_GetDistance(1);
	back = DIST_GetDistance(2);
	right = DIST_GetDistance(8);
	left = DIST_GetDistance(4);

	if(!has_waited){
		FRTOS1_vTaskDelay(5000/portTICK_PERIOD_MS); // 8000 for 5 sec
		has_waited = 1;
	}
	if(letsstart){

		switch (status){

		case REF_LINE_NONE:     /* no line, sensors do not see a line */

			DRV_SetMode(DRV_MODE_STOP);
			DRV_SetMode(DRV_MODE_SPEED);
			DRV_SetSpeed(-8000,-8000);
			//DRV_SetPos(Q4CLeft_GetPos()-700,Q4CRight_GetPos()-700);
			FRTOS1_vTaskDelay(300);
			DRV_SetMode(DRV_MODE_STOP);
			TURN_Turn(TURN_LEFT180, NULL);

		break;
		case REF_LINE_STRAIGHT: /* forward line |, sensors see a line underneath */
			DRV_SetMode(DRV_MODE_STOP);
			DRV_SetMode(DRV_MODE_SPEED);
			DRV_SetSpeed(-8000,-8000);
			//DRV_SetPos(Q4CLeft_GetPos()-700,Q4CRight_GetPos()-700);
			FRTOS1_vTaskDelay(300);
			DRV_SetMode(DRV_MODE_STOP);
			TURN_Turn(TURN_LEFT90, NULL);

		break;
		case REF_LINE_LEFT:    /* left half of sensors see line */

			DRV_SetMode(DRV_MODE_STOP);
			DRV_SetMode(DRV_MODE_SPEED);
			DRV_SetSpeed(-8000,-8000);
			//DRV_SetPos(Q4CLeft_GetPos()-700,Q4CRight_GetPos()-700);
			FRTOS1_vTaskDelay(200);
			//DRV_SetMode(DRV_MODE_STOP);
			TURN_Turn(TURN_LEFT90, NULL);

		break;
		case REF_LINE_RIGHT:   /* right half of sensors see line */

			DRV_SetMode(DRV_MODE_STOP);
			DRV_SetMode(DRV_MODE_SPEED);
			DRV_SetSpeed(-8000,-8000);
			//DRV_SetPos(Q4CLeft_GetPos()-700,Q4CRight_GetPos()-700);
			FRTOS1_vTaskDelay(200);
			DRV_SetMode(DRV_MODE_STOP);
			TURN_Turn(TURN_RIGHT90, NULL);

		break;
		case REF_LINE_FULL:     /* all sensors see a line */
			if((right<200)&(right>0)){
				TURN_Turn(TURN_RIGHT45, NULL);
				FRTOS1_vTaskDelay(50);
			}
			else if((left<200)&(left>0)){
				TURN_Turn(TURN_LEFT45, NULL);
				FRTOS1_vTaskDelay(50);
			}

			else if((front<200)&(front>0)){
				DRV_SetMode(DRV_MODE_SPEED);
				DRV_SetSpeed(8000,8000);
			}
			else if((back<100)&(back>0)){
				DRV_SetMode(DRV_MODE_SPEED);
				DRV_SetSpeed(-8000,-8000);
			}
			else{
				DRV_SetMode(DRV_MODE_SPEED);
				DRV_SetSpeed(7000,7000);
			}
		break;
		case REF_NOF_LINES:        /* Sentinel */
		break;

		}
	}
	else{
		DRV_SetMode(DRV_MODE_STOP);
	}
}


void APP_Start(void) {
  PL_Init();
  APP_AdoptToHardware();
  __asm volatile("cpsid i"); /* disable interrupts */
  __asm volatile("cpsie i"); /* enable interrupts */
   EVNT_SetEvent(EVNT_STARTUP);
   CLS1_SendStr("\nHello World\n", CLS1_GetStdio()->stdOut);

   EVNT_SetEvent(EVNT_STARTUP);
   CLS1_SendStr("\nHello World\n", CLS1_GetStdio()->stdOut);
  EVNT_SetEvent(EVNT_STARTUP);
  CLS1_SendStr("\nHello World\n", CLS1_GetStdio()->stdOut);
   //BUZ_PlayTune(0);
   //BUZ_PlayTune(2);
   //BUZ_PlayTune(3);
   for(;;) {
		#if PL_CONFIG_HAS_DEBOUNCE
	   	   KEYDBNC_Process();
		#else
	   	   KEY_Scan(); /* scan keys and set events */
		#endif
	   	WAIT1_WaitOSms(50);
	    EVNT_HandleEvent(APP_EventHandler, TRUE);

  }

	#if PL_CONFIG_HAS_DEBOUNCE
	   KEYDBNC_Process();
	#else
	   KEY_Scan(); /* scan keys and set events */
	#endif
	WAIT1_WaitOSms(50);
	EVNT_HandleEvent(APP_EventHandler, TRUE);
	}






