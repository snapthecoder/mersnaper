/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Tx1.h
**     Project     : TEAM_Robot
**     Processor   : MK22FX512VLK12
**     Component   : RingBuffer
**     Version     : Component 01.051, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-10-26, 14:14, # CodeGen: 26
**     Abstract    :
**         This component implements a ring buffer for different integer data type.
**     Settings    :
**          Component name                                 : Tx1
**          SDK                                            : MCUC1
**          Reentrant                                      : yes
**          Critical Section                               : CS1
**          Buffer Elements                                : 256
**          Element Size                                   : 1 Byte
**     Contents    :
**         Clear           - void Tx1_Clear(void);
**         Put             - uint8_t Tx1_Put(Tx1_ElementType elem);
**         Get             - uint8_t Tx1_Get(Tx1_ElementType *elemP);
**         Peek            - uint8_t Tx1_Peek(Tx1_BufSizeType index, Tx1_ElementType *elemP);
**         Update          - uint8_t Tx1_Update(Tx1_BufSizeType index, Tx1_ElementType *elemP);
**         Putn            - uint8_t Tx1_Putn(Tx1_ElementType *elem, Tx1_BufSizeType nof);
**         Getn            - uint8_t Tx1_Getn(Tx1_ElementType *buf, Tx1_BufSizeType nof);
**         Compare         - uint8_t Tx1_Compare(Tx1_BufSizeType index, Tx1_ElementType *elemP,...
**         Delete          - uint8_t Tx1_Delete(void);
**         NofElements     - Tx1_BufSizeType Tx1_NofElements(void);
**         NofFreeElements - Tx1_BufSizeType Tx1_NofFreeElements(void);
**         Deinit          - void Tx1_Deinit(void);
**         Init            - void Tx1_Init(void);
**
**     * Copyright (c) 2014-2017, Erich Styger
**      * Web:         https://mcuoneclipse.com
**      * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**      * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**      * All rights reserved.
**      *
**      * Redistribution and use in source and binary forms, with or without modification,
**      * are permitted provided that the following conditions are met:
**      *
**      * - Redistributions of source code must retain the above copyright notice, this list
**      *   of conditions and the following disclaimer.
**      *
**      * - Redistributions in binary form must reproduce the above copyright notice, this
**      *   list of conditions and the following disclaimer in the documentation and/or
**      *   other materials provided with the distribution.
**      *
**      * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**      * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**      * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**      * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**      * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**      * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**      * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**      * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**      * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**      * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file Tx1.h
** @version 01.00
** @brief
**         This component implements a ring buffer for different integer data type.
*/         
/*!
**  @addtogroup Tx1_module Tx1 module documentation
**  @{
*/         

#ifndef __Tx1_H
#define __Tx1_H

/* MODULE Tx1. */
#include "MCUC1.h" /* SDK and API used */
#include "Tx1config.h" /* configuration */

/* Include inherited components */
#include "MCUC1.h"
#include "CS1.h"


#ifdef __cplusplus
extern "C" {
#endif

#if Tx1_CONFIG_ELEM_SIZE==1
  typedef uint8_t Tx1_ElementType; /* type of single element */
#elif Tx1_CONFIG_ELEM_SIZE==2
  typedef uint16_t Tx1_ElementType; /* type of single element */
#elif Tx1_CONFIG_ELEM_SIZE==4
  typedef uint32_t Tx1_ElementType; /* type of single element */
#else
  #error "illegal element type size in properties"
#endif
#if Tx1_CONFIG_BUF_SIZE<256
  typedef uint8_t Tx1_BufSizeType; /* up to 255 elements (index 0x00..0xff) */
#else
  typedef uint16_t Tx1_BufSizeType; /* more than 255 elements, up to 2^16 */
#endif

uint8_t Tx1_Put(Tx1_ElementType elem);
/*
** ===================================================================
**     Method      :  Tx1_Put (component RingBuffer)
**     Description :
**         Puts a new element into the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - New element to be put into the buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t Tx1_Get(Tx1_ElementType *elemP);
/*
** ===================================================================
**     Method      :  Tx1_Get (component RingBuffer)
**     Description :
**         Removes an element from the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

Tx1_BufSizeType Tx1_NofElements(void);
/*
** ===================================================================
**     Method      :  Tx1_NofElements (component RingBuffer)
**     Description :
**         Returns the actual number of elements in the buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/

void Tx1_Init(void);
/*
** ===================================================================
**     Method      :  Tx1_Init (component RingBuffer)
**     Description :
**         Initializes the data structure
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

Tx1_BufSizeType Tx1_NofFreeElements(void);
/*
** ===================================================================
**     Method      :  Tx1_NofFreeElements (component RingBuffer)
**     Description :
**         Returns the actual number of free elements/space in the
**         buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/

void Tx1_Clear(void);
/*
** ===================================================================
**     Method      :  Tx1_Clear (component RingBuffer)
**     Description :
**         Clear (empty) the ring buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint8_t Tx1_Peek(Tx1_BufSizeType index, Tx1_ElementType *elemP);
/*
** ===================================================================
**     Method      :  Tx1_Peek (component RingBuffer)
**     Description :
**         Returns an element of the buffer without removiing it.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define Tx1_Deinit() \
   /* nothing to deinitialize */
/*
** ===================================================================
**     Method      :  Tx1_Deinit (component RingBuffer)
**     Description :
**         Driver de-initialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint8_t Tx1_Delete(void);
/*
** ===================================================================
**     Method      :  Tx1_Delete (component RingBuffer)
**     Description :
**         Removes an element from the buffer
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t Tx1_Putn(Tx1_ElementType *elem, Tx1_BufSizeType nof);
/*
** ===================================================================
**     Method      :  Tx1_Putn (component RingBuffer)
**     Description :
**         Put a number new element into the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elem            - Pointer to new elements to be put into
**                           the buffer
**         nof             - number of elements
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t Tx1_Compare(Tx1_BufSizeType index, Tx1_ElementType *elemP, Tx1_BufSizeType nof);
/*
** ===================================================================
**     Method      :  Tx1_Compare (component RingBuffer)
**     Description :
**         Compares the elements in the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to elements to compare with
**         nof             - number of elements to compare
**     Returns     :
**         ---             - zero if elements are the same, -1 otherwise
** ===================================================================
*/

uint8_t Tx1_Getn(Tx1_ElementType *buf, Tx1_BufSizeType nof);
/*
** ===================================================================
**     Method      :  Tx1_Getn (component RingBuffer)
**     Description :
**         Get a number elements into a buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * buf             - Pointer to buffer where to store the
**                           elements
**         nof             - number of elements
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t Tx1_Update(Tx1_BufSizeType index, Tx1_ElementType *elemP);
/*
** ===================================================================
**     Method      :  Tx1_Update (component RingBuffer)
**     Description :
**         Updates the data of an element.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

/* END Tx1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __Tx1_H */
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
