/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : RTOSCNTRLDD1.c
**     Project     : TEAM_Robot
**     Processor   : MK22FX512VLK12
**     Component   : TimerUnit_LDD
**     Version     : Component 01.164, Driver 01.11, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-11-03, 14:14, # CodeGen: 29
**     Abstract    :
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
**     Settings    :
**          Component name                                 : RTOSCNTRLDD1
**          Module name                                    : PIT
**          Counter                                        : PIT_CVAL0
**          Counter direction                              : Down
**          Counter width                                  : 32 bits
**          Value type                                     : Optimal
**          Input clock source                             : Internal
**            Counter frequency                            : 60 MHz
**          Counter restart                                : On-match
**            Period device                                : PIT_LDVAL0
**            Period                                       : 0.1 ms
**            Interrupt                                    : Enabled
**              Interrupt                                  : INT_PIT0
**              Interrupt priority                         : medium priority
**          Channel list                                   : 0
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnCounterRestart                           : Enabled
**              OnChannel0                                 : Disabled
**              OnChannel1                                 : Disabled
**              OnChannel2                                 : Disabled
**              OnChannel3                                 : Disabled
**              OnChannel4                                 : Disabled
**              OnChannel5                                 : Disabled
**              OnChannel6                                 : Disabled
**              OnChannel7                                 : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init    - LDD_TDeviceData* RTOSCNTRLDD1_Init(LDD_TUserData *UserDataPtr);
**         Deinit  - void RTOSCNTRLDD1_Deinit(LDD_TDeviceData *DeviceDataPtr);
**         Enable  - LDD_TError RTOSCNTRLDD1_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable - LDD_TError RTOSCNTRLDD1_Disable(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file RTOSCNTRLDD1.c
** @version 01.11
** @brief
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
*/         
/*!
**  @addtogroup RTOSCNTRLDD1_module RTOSCNTRLDD1 module documentation
**  @{
*/         

/* MODULE RTOSCNTRLDD1. */

#include "FRTOS1.h"
#include "RTOSCNTRLDD1.h"
#include "FreeRTOS.h" /* FreeRTOS interface */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 


typedef struct {
  LDD_TUserData *UserDataPtr;          /* RTOS device data structure */
} RTOSCNTRLDD1_TDeviceData;

typedef RTOSCNTRLDD1_TDeviceData *RTOSCNTRLDD1_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {FreeRTOS RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static RTOSCNTRLDD1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {FreeRTOS RTOS Adapter} Global variable used for passing a parameter into ISR */
static RTOSCNTRLDD1_TDeviceDataPtr INT_PIT0__BAREBOARD_RTOS_ISRPARAM;

#define AVAILABLE_EVENTS_MASK (LDD_TEventMask)(LDD_TIMERUNIT_ON_COUNTER_RESTART)

/* Internal method prototypes */
/*
** ===================================================================
**     Method      :  RTOSCNTRLDD1_Init (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* RTOSCNTRLDD1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  RTOSCNTRLDD1_TDeviceData *DeviceDataPrv;
  /* {FreeRTOS RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  /* Interrupt vector(s) allocation */
  /* {FreeRTOS RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_PIT0__BAREBOARD_RTOS_ISRPARAM = DeviceDataPrv;
  /* SIM_SCGC6: PIT=1 */
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
  /* PIT_MCR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,MDIS=0,FRZ=0 */
  PIT_MCR = 0x00U;                     /* Enable device clock */
  /* PIT_TCTRL0: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHN=0,TIE=0,TEN=0 */
  PIT_TCTRL0 = 0x00U;                  /* Clear control register */
  /* PIT_TFLG0: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TIF=1 */
  PIT_TFLG0 = PIT_TFLG_TIF_MASK;       /* Clear timer flag register */
  /* PIT_LDVAL0: TSV=0x176F */
  PIT_LDVAL0 = PIT_LDVAL_TSV(0x176F);  /* Set up load register */
  /* NVICIP48: PRI48=0x80 */
  NVICIP48 = NVIC_IP_PRI48(0x80);
  /* NVICISER1: SETENA|=0x00010000 */
  NVICISER1 |= NVIC_ISER_SETENA(0x00010000);
  /* PIT_TCTRL0: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHN=0,TIE=1,TEN=1 */
  PIT_TCTRL0 = (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK); /* Set up control register */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_RTOSCNTRLDD1_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the device data structure */
}

/*
** ===================================================================
**     Method      :  RTOSCNTRLDD1_Deinit (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Deinitializes the device. Switches off the device, frees the
**         device data structure memory, interrupts vectors, etc.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by Init method
*/
/* ===================================================================*/
void RTOSCNTRLDD1_Deinit(LDD_TDeviceData *DeviceDataPtr)
{
  RTOSCNTRLDD1_TDeviceData *DeviceDataPrv = (RTOSCNTRLDD1_TDeviceData *)DeviceDataPtr;

  (void)DeviceDataPrv;
  PIT_PDD_EnableDevice(PIT_BASE_PTR, PIT_PDD_CHANNEL_0, PDD_DISABLE);
  /* Interrupt vector(s) deallocation */
  /* {FreeRTOS RTOS Adapter} Restore interrupt vector: IVT is static, no code is generated */
  PIT_PDD_ModuleClock(PIT_BASE_PTR, PIT_PDD_CLOCK_DISABLED);
  /* Unregistration of the device structure */
  PE_LDD_UnregisterDeviceStructure(PE_LDD_COMPONENT_RTOSCNTRLDD1_ID);
  /* Deallocation of the device structure */
  /* {FreeRTOS RTOS Adapter} Driver memory deallocation: Dynamic allocation is simulated, no deallocation code is generated */
}

/*
** ===================================================================
**     Method      :  RTOSCNTRLDD1_Enable (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Enables the component - it starts the signal generation.
**         Events may be generated (see SetEventMask). The method is
**         not available if the counter can't be disabled/enabled by HW.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError RTOSCNTRLDD1_Enable(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  PIT_PDD_EnableDevice(PIT_BASE_PTR, PIT_PDD_CHANNEL_0, PDD_ENABLE); /* Enable the device */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  RTOSCNTRLDD1_Disable (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Disables the component - it stops signal generation and
**         events calling. The method is not available if the counter
**         can't be disabled/enabled by HW.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError RTOSCNTRLDD1_Disable(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  PIT_PDD_EnableDevice(PIT_BASE_PTR, PIT_PDD_CHANNEL_0, PDD_DISABLE);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  RTOSCNTRLDD1_Interrupt (component TimerUnit_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(RTOSCNTRLDD1_Interrupt)
{
  /* {FreeRTOS RTOS Adapter} ISR parameter is passed through the global variable */
  RTOSCNTRLDD1_TDeviceDataPtr DeviceDataPrv = INT_PIT0__BAREBOARD_RTOS_ISRPARAM;

  PIT_PDD_ClearInterruptFlag(PIT_BASE_PTR, PIT_PDD_CHANNEL_0); /* Clear interrupt flag */
  RTOSCNTRLDD1_OnCounterRestart(DeviceDataPrv->UserDataPtr); /* Invoke OnCounterRestart event */
}

/* END RTOSCNTRLDD1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
