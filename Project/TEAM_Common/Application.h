/**
 * \file
 * \brief Main application interface
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This provides the main application entry point.
 */

#ifndef SOURCES_FS2016_COMMON_APPLICATION_H_
#define SOURCES_FS2016_COMMON_APPLICATION_H_

#include "Platform.h"

#if PL_CONFIG_HAS_EVENTS
#include "Event.h"

void APP_EventHandler(EVNT_Handle event);
#endif
void APP_Drive(void);
void APP_Start(void);
void APP_AdoptToHardware(void);
typedef enum {
  NONE=0,     /* no line, sensors do not see a line */
  STRAIGHT=1, /* forward line |, sensors see a line underneath */
  TURNLEFT=2,     /* left half of sensors see line */
  TURNRIGHT=3,    /* right half of sensors see line */

} DriveState;

#endif /* SOURCES_FS2016_COMMON_APPLICATION_H_ */
