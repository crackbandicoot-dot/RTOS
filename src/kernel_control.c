#include "cmsis_os.h"
#include "start.h"
#include <ARMCM3.h>

uint32_t osKernelSysTick(void){
    return SysTick->VAL;
}

osStatus osKernelInitialize(void){
    SystemInit();
    SysTick_Config(60);
    return osOK;
}	

