/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : BitIoLdd18.h
**     Project     : TEAM_Robot
**     Processor   : MK22FX512VLK12
**     Component   : BitIO_LDD
**     Version     : Component 01.033, Driver 01.03, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-10-26, 14:14, # CodeGen: 26
**     Abstract    :
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : BitIoLdd18
**          Pin for I/O                                    : ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/I2S0_RXD1/FB_RW_b
**          Pin signal                                     : Right_B_J9_13
**          Direction                                      : Input
**          Initialization                                 : 
**            Init. direction                              : Input
**            Init. value                                  : 0
**            Auto initialization                          : yes
**          Safe mode                                      : no
**     Contents    :
**         Init   - LDD_TDeviceData* BitIoLdd18_Init(LDD_TUserData *UserDataPtr);
**         GetVal - bool BitIoLdd18_GetVal(LDD_TDeviceData *DeviceDataPtr);
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
** @file BitIoLdd18.h
** @version 01.03
** @brief
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
*/         
/*!
**  @addtogroup BitIoLdd18_module BitIoLdd18 module documentation
**  @{
*/         

#ifndef __BitIoLdd18_H
#define __BitIoLdd18_H

/* MODULE BitIoLdd18. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "IO_Map.h"
#include "GPIO_PDD.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 



/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define BitIoLdd18_PRPH_BASE_ADDRESS  0x400FF080U
  
/*! Device data structure pointer used when auto initialization property is enabled. This constant can be passed as a first parameter to all component's methods. */
#define BitIoLdd18_DeviceData  ((LDD_TDeviceData *)PE_LDD_GetDeviceStructure(PE_LDD_COMPONENT_BitIoLdd18_ID))

/* Methods configuration constants - generated for all enabled component's methods */
#define BitIoLdd18_Init_METHOD_ENABLED /*!< Init method of the component BitIoLdd18 is enabled (generated) */
#define BitIoLdd18_GetVal_METHOD_ENABLED /*!< GetVal method of the component BitIoLdd18 is enabled (generated) */

/* Definition of implementation constants */
#define BitIoLdd18_MODULE_BASE_ADDRESS PTC_BASE_PTR /*!< Name of macro used as the base address */
#define BitIoLdd18_PORTCONTROL_BASE_ADDRESS PORTC_BASE_PTR /*!< Name of macro used as the base address */
#define BitIoLdd18_PORT_MASK 0x0800U   /*!< Mask of the allocated pin from the port */



/*
** ===================================================================
**     Method      :  BitIoLdd18_Init (component BitIO_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the "Enable
**         in init. code" is set to "yes" value then the device is also
**         enabled(see the description of the Enable() method). In this
**         case the Enable() method is not necessary and needn't to be
**         generated. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* BitIoLdd18_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  BitIoLdd18_GetVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Returns the input/output value. If the direction is [input]
**         then the input value of the pin is read and returned. If the
**         direction is [output] then the last written value is read
**         and returned (see <Safe mode> property for limitations).
**         This method cannot be disabled if direction is [input].
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Input or output value. Possible values:
**                           <false> - logical "0" (Low level)
**                           <true> - logical "1" (High level)
*/
/* ===================================================================*/
bool BitIoLdd18_GetVal(LDD_TDeviceData *DeviceDataPtr);

/* END BitIoLdd18. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif
/* ifndef __BitIoLdd18_H */
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
