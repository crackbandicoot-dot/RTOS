#include "cmsis_os.h"
#include "start.h"
#include <ARMCM3.h>
#include <stdbool.h>

static uint32_t isKernelRunning = false; 

uint32_t osKernelSysTick(void){
    return SysTick->VAL;
}

osStatus osKernelInitialize(void){
    SystemInit();
    SysTick_Config(SystemCoreClock/1000);
    return osOK;
}
osStatus osKernelStart(void){
    isKernelRunning = true;
    return osOK;
}

