#include "cmsis_os.h"
#include "start.h"
#include <ARMCM3.h>
#include <stdbool.h>
#include <stdio.h>

static uint32_t isKernelRunning = false; 

uint32_t osKernelSysTick(void){
    return SysTick->VAL;
}
void useless(){

    logString("%d");    
}
osStatus osKernelInitialize(void){
    SystemInit();
    useless();
    SysTick_Config(SystemCoreClock/1000);
    __ASM volatile ("SVC #8\n");
   
    return osOK;
}
osStatus osKernelStart(void){
    isKernelRunning = true;
    return osOK;
}