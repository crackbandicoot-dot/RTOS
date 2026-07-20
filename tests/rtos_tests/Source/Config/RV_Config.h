/*-----------------------------------------------------------------------------
 *      Name:         RV_Config.h 
 *      Purpose:      RV Config header
 *----------------------------------------------------------------------------
 *      Copyright(c) KEIL - An ARM Company
 *----------------------------------------------------------------------------*/
#ifndef __RV_CONFIG_H
#define __RV_CONFIG_H

#include "ARMCM3.h"

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

// <h> Common Test Settings
// <o> Print Output Format <0=> Plain Text <1=> XML
// <i> Set the test results output format to plain text or XML
#ifndef PRINT_XML_REPORT
#define PRINT_XML_REPORT            0 
#endif
// <o> Buffer size for assertions results
// <i> Set the buffer size for assertions results buffer
#define BUFFER_ASSERTIONS           128  
// <o> OS Timer tick interval value [us] <1-1000000>
// <i> The OS Timer tick interval value is used to calculate timeout values
#define RTOS_TICK_TIME              1000
// </h>
  
#endif /* __RV_CONFIG_H */
