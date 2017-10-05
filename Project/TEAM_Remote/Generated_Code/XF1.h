/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : XF1.h
**     Project     : TEAM_Remote
**     Processor   : MK20DX128VFT5
**     Component   : XFormat
**     Version     : Component 01.021, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-10-05, 14:06, # CodeGen: 0
**     Abstract    :
**
**     Settings    :
**          Component name                                 : XF1
**          SDK                                            : MCUC1
**          Floating Point                                 : no
**     Contents    :
**         xvformat  - unsigned XF1_xvformat(void (*outchar)(void *,char), void *arg, const char *...
**         xformat   - unsigned XF1_xformat(void (*outchar)(void *,char), void *arg, const char *...
**         xsprintf  - int XF1_xsprintf(char *buf, const char *fmt, ...);
**         xsnprintf - int XF1_xsnprintf(char *buf, size_t max_len, const char *fmt, ...);
**
**     *  Copyright : (c) Copyright Mario Viara, 2014-2017, https://github.com/MarioViara/xprintfc
**      * Adopted for Processor Expert: Erich Styger
**      * xsnprintf() contributed by Engin Lee
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
** @file XF1.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup XF1_module XF1 module documentation
**  @{
*/         

#ifndef __XF1_H
#define __XF1_H

/* MODULE XF1. */
#include "MCUC1.h" /* SDK and API used */
#include "XF1config.h" /* configuration */

/* other includes needed */
#include <stdarg.h> /* open argument list support */
#include <stddef.h> /* for size_t */
/* GCC have printf type attribute check. */
#ifdef __GNUC__
  /* inform the GNU compiler about printf() style functions, so the compiler can check the arguments */
  #define XF1_PRINTF_ATTRIBUTE(a,b) __attribute__ ((__format__ (__printf__, a, b)))
#else
  #define XF1_PRINTF_ATTRIBUTE(a,b)
#endif /* __GNUC__ */


unsigned XF1_xformat(void (*outchar)(void *,char), void *arg, const char * fmt, ...) XF1_PRINTF_ATTRIBUTE(3,4);
/*
** ===================================================================
**     Method      :  XF1_xformat (component XFormat)
**     Description :
**         Printf() like function using variable arguments
**     Parameters  :
**         NAME            - DESCRIPTION
**         outchar         - Function pointer to output one new
**                           character
**         arg             - Argument for the output function
**         fmt             - Format options for the list of parameters
**         openArgList     - Open argument list
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

unsigned XF1_xvformat(void (*outchar)(void *,char), void *arg, const char * fmt, va_list args);
/*
** ===================================================================
**     Method      :  XF1_xvformat (component XFormat)
**     Description :
**         Printf() like format function
**     Parameters  :
**         NAME            - DESCRIPTION
**         outchar         - Function pointer to the function
**                           to output one char.
**       * arg             - Argument for the output function.
**         fmt             - Format options for the list of parameters.
**         args            - List of parameters
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

int XF1_xsprintf(char *buf, const char *fmt, ...) XF1_PRINTF_ATTRIBUTE(2,3);
/*
** ===================================================================
**     Method      :  XF1_xsprintf (component XFormat)
**     Description :
**         sprintf() like function
**     Parameters  :
**         NAME            - DESCRIPTION
**       * buf             - Pointer to buffer to be written
**       * fmt             - Pointer to formatting string
**         argList         - Open Argument List
**     Returns     :
**         ---             - number of characters written, negative for
**                           error case
** ===================================================================
*/

int XF1_xsnprintf(char *buf, size_t max_len, const char *fmt, ...) XF1_PRINTF_ATTRIBUTE(3,4);
/*
** ===================================================================
**     Method      :  XF1_xsnprintf (component XFormat)
**     Description :
**         snprintf() like function, returns the number of characters
**         written, negative in case of error.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * buf             - Pointer to buffer to be written
**         max_len         - size of output buffer (in size)
**       * fmt             - Pointer to formatting string
**         argList         - Open Argument List
**     Returns     :
**         ---             - number of characters written, negative for
**                           error case
** ===================================================================
*/

/* END XF1. */

#endif
/* ifndef __XF1_H */
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
