/*
 * Memory mapping with the regions that are allocated in the program.
 */

#include "start.h"
#include <ARMCM3.h>

void SVC_Handler(void)
{
  logPrint("SVC Call, switching to Priviledge\n");
  __set_CONTROL(__get_CONTROL() & ~CONTROL_nPRIV_Msk);
}

void PendSV_Handler(void){
  logPrint("I don't know what is this call XD PendSV_Handler..");
}
void SysTick_Handler(void){ 
  logPrint("TIMER");
}