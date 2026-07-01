#include "start.h"

/* #include <ARMCM3.h> */
#include "cmsis_os.h"
#include <stdlib.h>
#include <stdint.h>

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
int main(void)
{
  osKernelInitialize();
  while(1){
    printString("Hello world");
  }
  return 0;
}

