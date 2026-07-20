#include "cmsis_os.h"
#include "start.h"
#include <ARMCM3.h>
#include <stdbool.h>
#include <stdio.h>
#include "../core/kernel_objects.h"
#include "../core/queue.h"
#include "scheduler.h"
static uint32_t isKernelRunning = false; 

uint32_t osKernelSysTick(void){
    return SysTick->VAL;
}

osStatus osKernelInitialize(void){
    SystemInit();
    __set_PRIMASK(1);
    //Initialize schdeduler structs
    initialize_queue(&ready_queue,ready_arr,MAX_THREADS);
    initialize_queue(&waiting_queue,waiting_arr,MAX_THREADS);
    
    
    SysTick_Config(SystemCoreClock/1000*100);
    
    return osOK;
}
osStatus osKernelStart(void){
    
    isKernelRunning = true;
    //__ASM volatile ("SVC #8\n");
    //Start scheduler here.
    first_task();
    __set_PSP(pxCurrentTCB->psp);
    NVIC_SetPriority(PendSV_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
    __ISB();
    __set_PRIMASK(0);
    __set_CONTROL(3);
    while(1){}
    return osOK;
}