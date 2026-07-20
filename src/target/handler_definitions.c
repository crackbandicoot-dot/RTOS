#include "start.h"
#include <ARMCM3.h>
#include <stdlib.h>
/**
 * @brief Supervisor Call (SVC) Handler
 * Role: Used by unprivileged tasks to request privileged OS services (System Calls).
 */
void SVC_Handler(void)
{
  // 1. Logging the event
  logPrint("SVC Call, switching to Priviledge\n");
  
  /* 
   * NOTE ON YOUR CODE BELOW:
   * Cortex-M handlers ALWAYS run in Privileged Handler Mode automatically.
   * Modifying the CONTROL register here to clear nPRIV is redundant inside the handler.
   * To permanently make the returning thread privileged, you must modify the stacked 
   * CONTROL register value or EXC_RETURN value before exiting.
   */
  

  // TODO FOR YOU: 
  // 1. Read the stacked PC (Program Counter) to find the SVC number argument.
  // 2. Use a switch-case statement to execute different OS functions based on that number.
  // 3. Example: case 0 = Yield, case 1 = Terminate Task, case 2 = Allocate Memory.
  
}

/**
 * @brief Pended System Call (PendSV) Handler
 * Role: The workhorse for RTOS context switching.
 */
void PendSV_Handler( void ) __attribute__( ( naked ) );
//TODO this should be a naked function
void PendSV_Handler(void)
{   //TCB current-task info 
    __ASM volatile
    (
      "mrs r0, psp;" //Stores psp into r0
      "isb;"         //It's recommended for some weird reason this instruction after dealing with sp
      
      "ldr r3, =pxCurrentTCB;" //copy into r3 the address of the global variable holding the TCB pointer(a pointer to a pointer)
      "ldr r2, [r3];" //Loads a pointer to the current TCB(the current task) into r2.
      "stmdb r0!, {r4-r11};" //Stores multiple registers r4-r11 inclusive into process stack
      "str r0, [r2];" // Save the new top of stack into the first member of the TCB.

      //Push r3(holding a pointer to the current task) and r14(link register which on interrupts has a magic value that)
      //captures the mode in which was before(in this case it probably will be thread privileged mode)
      "stmdb sp!, {r3, r14};" 

      //This is for avoiding interruptions on the critical section in which the context switch occurs

      "mov r0, %0;" //Copy configMAX_SYSCALL_INTERRUPT_PRIORITY priority to r0 so we can set BASEPRI later
      
      //Set basepri to configMAX_SYSCALL_INTERRUPT_PRIORITY,
      //Any interrupt with priority <= configMAX_SYSCALL_INTERRUPT_PRIORITY is now disabled.
      "msr basepri, r0;"
      "bl next_task;" //This calls the context switch function, which can be written on C, no parameters
      
      "mov r0, #0;" //We will use this to set base pri to 0(the default value)
      "msr basepri, r0;" //Set basepri to 0
      "ldmia sp!, {r3, r14};" //Pop into r3,r14 what was on the stack

      //Restore the context, including the critical nesting
      "ldr r1, [r3];" // now r1 holds the pointer to the TCB 
      "ldr r0, [r1];"/* The first item in pxCurrentTCB is the task top of stack. */
      "ldmia r0!, {r4-r11};" /* Pop the registers. */
      "msr psp, r0;" // Restore the psp  value
      "isb;" //It's recommended for some weird reason this instruction after dealing with sp
      "bx r14;" //Branch with the info on r14, the link registers(it should go back to privilege thread mode)
      
      //Assembler directive to dump the literal pool (the constant from ldr r3, =pxCurrentTCB and the %0 immediate) 
      //near this code.
      ".ltorg;"
      ::"i" (0 /*configMAX_SYSCALL_INTERRUPT_PRIORITY */)
    );
}

/**
 * @brief System Tick (SysTick) Handler
 * Role: Generates periodic heartbeats/interrupts for timekeeping and scheduling.
 */
void SysTick_Handler(void){ 
  // Currently just a placeholder log.
  /* 
   * TODO FOR YOU: 
   * 1. Increment a global volatile system tick variable (e.g., system_ticks++;).
   * 2. Handle software timers or task delays that are waiting for time to pass.
   * 3. If a task's time-slice expires, trigger a context switch by pending PendSV:
    */
  SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}