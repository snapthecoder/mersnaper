/**
 * \file
 * \brief RTOS interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module the main tasks of the RTOS.
 */

#ifndef RTOS_H_
#define RTOS_H_

#include "Platform.h"
#if PL_CONFIG_HAS_RTOS
/*! \brief Initializes the RTOS module */
void RTOS_Init(void);

/*! \brief De-Initializes the RTOS module */
void RTOS_Deinit(void);

void DriveTask (void *pvParameters);
void MyAPPTask (void *pvParam);
void  RTOS_APP_Start(void);

#endif /* PL_CONFIG_HAS_RTOS */

#endif /* RTOS_H_ */
