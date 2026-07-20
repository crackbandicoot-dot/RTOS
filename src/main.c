#include "target/start.h"
#include "target/cmsis_os.h"
#include "core/queue.h"
#include "core/kernel_objects.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* 
void configureMPU(void)
{

   Enable MPU 
}

void accessRegionsMPU(void)
{
  uint32_t* addrRegion2 = (uint32_t*) 0x20010000U;

  for (size_t i = 0; i <= 257; i++)
  {
     ARM_MPU_AP_NONE No access 
   addrRegion2[i] = i + 1;
  }

}
void ref_main(){
  
  SystemInit();
  SysTick_Config(30);
  __set_PSP(0x20000000U);
  printString("Hello world!");
  logPrint("Control 0x%x\n"
           "PSP 0x%x\n"
           "MSP 0x%x\n\n",
            __get_CONTROL(), __get_PSP(), __get_MSP());
  
  logPrint("Hello world \n");
  
  
  //configureMPU();
  __ASM volatile ("SVC #8\n");

  //accessRegionsMPU();
  
} */
void printA()
{
  while(1){
    printString("A\n");
  }
}
void printB()
{
  uint32_t counter=0;
  while(1){
  printString("EVEN\n");
  }
}
void printC()
{
  uint32_t counter=0;
  while(1){
  printString("ODD\n");
  }
}

int main(void)
{
  osKernelInitialize();
  
  osThreadDef(printA,0,1,0);
  osThreadDef(printB,0,1,0);
  osThreadDef(printC,0,1,0);
  osThreadId thread_a= osThreadCreate(&os_thread_def_printA,NULL);
  osThreadId thread_b = osThreadCreate(&os_thread_def_printB,NULL);
  osThreadId thread_c = osThreadCreate(&os_thread_def_printC,NULL);

  osKernelStart();
  while(1){}
  return 0;
}