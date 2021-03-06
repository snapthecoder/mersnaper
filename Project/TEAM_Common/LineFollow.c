/**
 * \file
 * \brief Implements line following of the robot
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This is the implementation of the line following.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_LINE_FOLLOW
#include "LineFollow.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "Shell.h"
#include "Motor.h"
#include "Reflectance.h"
#if PL_CONFIG_HAS_TURN
  #include "Turn.h"
#endif
#include "WAIT1.h"
#include "Pid.h"
#include "Drive.h"
#include "Shell.h"
#if PL_CONFIG_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_CONFIG_HAS_DRIVE
  #include "Drive.h"
#endif

#if 1 /*! \todo */
#include "RNet_App.h"
#endif

typedef enum {
  STATE_IDLE,              /* idle, not doing anything */
  STATE_FOLLOW_SEGMENT,    /* line following segment, going forward */
  STATE_TURN,              /* reached an intersection, turning around */
  STATE_FINISHED,          /* reached finish area */
  STATE_STOP               /* stop the engines */
} StateType;

/* task notification bits */
#define LF_START_FOLLOWING (1<<0)  /* start line following */
#define LF_STOP_FOLLOWING  (1<<1)  /* stop line following */

static volatile StateType LF_currState = STATE_IDLE;
static xTaskHandle LFTaskHandle;

void LF_StartFollowing(void) {
  (void)xTaskNotify(LFTaskHandle, LF_START_FOLLOWING, eSetBits);
}

void LF_StopFollowing(void) {
  (void)xTaskNotify(LFTaskHandle, LF_STOP_FOLLOWING, eSetBits);
}

void LF_StartStopFollowing(void) {
  if (LF_IsFollowing()) {
    (void)xTaskNotify(LFTaskHandle, LF_STOP_FOLLOWING, eSetBits);
  } else {
    (void)xTaskNotify(LFTaskHandle, LF_START_FOLLOWING, eSetBits);
  }
}

/* forward declaration */
static void StateMachine(void);

/*!
 * \brief follows a line segment.
 * \return Returns TRUE if still on line segment
 */
static bool FollowSegment(void) {
  uint16_t currLine;
  REF_LineKind currLineKind;

  currLine = REF_GetLineValue();
  currLineKind = REF_GetLineKind();
  if (currLineKind==REF_LINE_STRAIGHT) {
    PID_Line(currLine, REF_MIDDLE_LINE_VALUE); /* move along the line */
    return TRUE;
  } else {
    return FALSE; /* intersection/change of direction or not on line any more */
  }
}

static void StateMachine(void) {
  REF_LineKind lineKind;

  switch (LF_currState) {
    case STATE_IDLE:
      break;

    case STATE_FOLLOW_SEGMENT:
      if (!FollowSegment()) {
        //SHELL_SendString((unsigned char*)"No line, stopped!\r\n");
        //LF_currState = STATE_STOP; /* stop if we do not have a line any more */
        LF_currState = STATE_TURN;
      }
      break;

    case STATE_TURN:
      lineKind = REF_GetLineKind();
      if (lineKind==REF_LINE_NONE) {
        LF_currState = STATE_FINISHED;
        DRV_SetMode(DRV_MODE_NONE); /* disable position mode */}
       else {
    	LF_currState = STATE_STOP;
       }
       if (lineKind==REF_LINE_FULL) {
        TURN_Turn(TURN_LEFT180, NULL);
        FRTOS1_vTaskDelay(50);
       //LF_currState = STATE_FOLLOW_SEGMENT;
        LF_currState = STATE_STOP;
      }
      break;
    case STATE_FINISHED:
      SHELL_SendString("Finished!\r\n");
      LF_currState = STATE_STOP;
      break;
    case STATE_STOP:
#if 0
      RNETA_SendSignal('C'); /*! \todo */
#endif
      SHELL_SendString("Stopped!\r\n");
      TURN_Turn(TURN_STOP, NULL);
     LF_currState = STATE_IDLE;
     // LF_currState =STATE_FOLLOW_SEGMENT;
      break;
  } /* switch */
}


static void stateMachineZweiPunktNull(void) {
		REF_LineKind status;
		status = REF_GetLineKind();
		if(REF_IsReady()){

		switch (status){
		case REF_LINE_NONE:     /* no line, sensors do not see a line */
			TURN_TurnAngle((int16_t)-20, NULL);
			FRTOS1_vTaskDelay(50);
			TURN_TurnAngle((int16_t)40, NULL);
			DRV_SetMode(DRV_MODE_NONE);
			FRTOS1_vTaskDelay(50);
			//LF_StopFollowing();
		break;
		case REF_LINE_STRAIGHT: /* forward line |, sensors see a line underneath */
			FollowSegment();
		break;
		case REF_LINE_LEFT:    /* left half of sensors see line */
			FollowSegment();
		break;
		case REF_LINE_RIGHT:   /* right half of sensors see line */
			FollowSegment();
		break;
		case REF_LINE_FULL:     /* all sensors see a line */
		    TURN_TurnAngle((int16_t)180, NULL);
		    TURN_Turn(TURN_STOP, NULL);
		    DRV_SetMode(DRV_MODE_NONE);
		    FRTOS1_vTaskDelay(50);

		break;

	}
		}
	}


bool LF_IsFollowing(void) {
  return LF_currState!=STATE_IDLE;
}

static void LineTask (void *pvParameters) {
  uint32_t notifcationValue;

  (void)pvParameters; /* not used */
  for(;;) {
    (void)xTaskNotifyWait(0UL, LF_START_FOLLOWING|LF_STOP_FOLLOWING, &notifcationValue, 0); /* check flags */
    if (notifcationValue&LF_START_FOLLOWING) {
#if 0
      RNETA_SendSignal('B'); /*! \todo */
#endif
      DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode */
      PID_Start();
      LF_currState = STATE_FOLLOW_SEGMENT;
    }
    if (notifcationValue&LF_STOP_FOLLOWING) {
      LF_currState = STATE_STOP;
    }

#if 0
    StateMachine();
#else
    stateMachineZweiPunktNull();
#endif
    FRTOS1_vTaskDelay(5/portTICK_PERIOD_MS);
  }
}

static void LF_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"line", (unsigned char*)"Group of line following commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows line help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  start|stop", (unsigned char*)"Starts or stops line following\r\n", io->stdOut);
}

static void LF_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"line follow", (unsigned char*)"\r\n", io->stdOut);
  switch (LF_currState) {
    case STATE_IDLE: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"IDLE\r\n", io->stdOut);
      break;
    case STATE_FOLLOW_SEGMENT: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"FOLLOW_SEGMENT\r\n", io->stdOut);
      break;
    case STATE_STOP: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"STOP\r\n", io->stdOut);
      break;
    case STATE_TURN: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"TURN\r\n", io->stdOut);
      break;
    case STATE_FINISHED: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"FINISHED\r\n", io->stdOut);
      break;
    default: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"UNKNOWN\r\n", io->stdOut);
      break;
  } /* switch */
}

uint8_t LF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"line help")==0) {
    LF_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"line status")==0) {
    LF_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"line start")==0) {
    LF_StartFollowing();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"line stop")==0) {
    LF_StopFollowing();
    *handled = TRUE;
  }
  return res;
}

void LF_Deinit(void) {
  /* nothing needed */
}

void LF_Init(void) {
  LF_currState = STATE_IDLE;
  if (xTaskCreate(LineTask, "Line", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &LFTaskHandle) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_CONFIG_HAS_LINE_FOLLOW */
