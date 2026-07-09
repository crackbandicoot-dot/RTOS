#include "cmsis_os.h"
#include "start.h"
#include <ARMCM3.h>
#include <stdbool.h>
#include <stdio.h>
#include "memory.h"
static uint32_t isKernelRunning = false; 

uint32_t osKernelSysTick(void){
    return SysTick->VAL;
}

osStatus osKernelInitialize(void){
    SystemInit();
    //SysTick_Config(SystemCoreClock/1000);
    
    return osOK;
}
osStatus osKernelStart(void){
    
    isKernelRunning = true;
    //Start scheduler here.
    //__set_PSP(userMemory+USER_BYTES-1);
    return osOK;
}