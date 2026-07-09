#include "start.h"
#include <ARMCM3.h>

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
void PendSV_Handler(void){
  // Currently just a placeholder log.
  logPrint("Context switch handling...");

  /* 
   * TODO FOR YOU: 
   * 1. REMOVE the logPrint() completely. Context switches must be incredibly fast.
   * 2. REWRITE this handler using inline assembly or a pure assembly (.s) file.
   * 3. Assembly steps needed:
   *    a) Save current task registers (R4-R11) to the current Process Stack Pointer (PSP).
   *    b) Save old PSP to your Task Control Block (TCB) structure.
   *    c) Call your scheduler C-function to pick the next task.
   *    d) Load the next task's PSP from its TCB.
   *    e) Restore registers (R4-R11) from the new PSP.
   *    f) Exit handler back to the new task using the process stack.
   */
  //__set_CONTROL(__get_CONTROL() & ~CONTROL_nPRIV_Msk);
  
}

/**
 * @brief System Tick (SysTick) Handler
 * Role: Generates periodic heartbeats/interrupts for timekeeping and scheduling.
 */
void SysTick_Handler(void){ 
  // Currently just a placeholder log.
  logPrint("TIMER");

  /* 
   * TODO FOR YOU: 
   * 1. Increment a global volatile system tick variable (e.g., system_ticks++;).
   * 2. Handle software timers or task delays that are waiting for time to pass.
   * 3. If a task's time-slice expires, trigger a context switch by pending PendSV:
   *    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
   */
 // __set_CONTROL(__get_CONTROL() & ~CONTROL_nPRIV_Msk);
}
