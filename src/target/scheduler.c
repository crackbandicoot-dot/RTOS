#include "cmsis_os.h"
#include "../core/kernel_objects.h"
#include "../core/queue.h"
#include <strings.h>
#include <stdint.h>
#include "scheduler.h"

/**
  * @brief  This function initializes a stack with data for debugging and the PC pointing to start of the task
  *and r0 holding a pointer to the tasks arguments       
  *       
  * @param  task  is a pointer to the task code
  *         p_arg is a pointer to a user supplied data area that will be passed to 
  *               the task when the task first executes.
  *         ptos  is a pointer to the top of stack.  It is assumed that 'ptos' points to
  *               a 'free' entry on the task stack.
  * @retval Always returns the location of the new top-of-stack once the processor registers 
  *         have been placed on the stack in the proper order.
  */
uint32_t *OSTaskStkInit (os_pthread task, void *p_arg, uint32_t *ptos)
{
    uint32_t *stk;
    stk       = ptos;
                                                   /* Load stack pointer                 */
                                                   /* Registers stacked as if auto-saved on exception    */
    *(--stk)  = (uint32_t)0x01000000L;             /* xPSR                                               */
    *(--stk)  = (uint32_t)task;                    /* Entry Point                                        */
    *(--stk)  = (uint32_t)0xFFFFFFFD;              /* R14 (LR) (init value will cause fault if ever used)*/
    *(--stk)  = (uint32_t)0x12121212L;             /* R12                                                */
    *(--stk)  = (uint32_t)0x03030303L;             /* R3                                                 */
    *(--stk)  = (uint32_t)0x02020202L;             /* R2                                                 */
    *(--stk)  = (uint32_t)0x01010101L;             /* R1                                                 */
    *(--stk)  = (uint32_t)p_arg;                   /* R0 : argument                                      */

                                                   /* Remaining registers saved on process stack         */
    *(--stk)  = (uint32_t)0x11111111L;             /* R11                                                */
    *(--stk)  = (uint32_t)0x10101010L;             /* R10                                                */
    *(--stk)  = (uint32_t)0x09090909L;             /* R9                                                 */
    *(--stk)  = (uint32_t)0x08080808L;             /* R8                                                 */
    *(--stk)  = (uint32_t)0x07070707L;             /* R7                                                 */
    *(--stk)  = (uint32_t)0x06060606L;             /* R6                                                 */
    *(--stk)  = (uint32_t)0x05050505L;             /* R5                                                 */
    *(--stk)  = (uint32_t)0x04040404L;             /* R4                                                 */
    return (stk);
}

void first_task()
{
    
    running_thread = deqeue(&ready_queue); 
    logPrint("INFO:Starting first task with id %d and function name \n",running_thread);
    pxCurrentTCB = &(scheduled_tasks[running_thread]);
}
/// @brief Stores the interrupted task into one of the respective queues
/// @param interrupted_task The interrupted task snapshot
/// @return The new scheduled task

void next_task()
{

    enqeue(&ready_queue,running_thread);
    
    running_thread = deqeue(&ready_queue); 
    pxCurrentTCB = &(scheduled_tasks[running_thread]);
   
}
osThreadId osThreadCreate(const osThreadDef_t * thread_def,
void * 	argument )
{   
    const uint32_t desired_threads=current_threads+thread_def->instances;
    if(desired_threads>MAX_THREADS)
    {
        return NULL;
    }
    current_threads=desired_threads;
    //TODO do, add every instance, not just one instance(now is assumed thread_def->instances=1)
    int id = ffs(~threads_ids)-1;
    
    //Put thread id on queue
    enqeue(&ready_queue,id);

    //Added function to initial task.
    uint32_t psp =(uint32_t)userMemory+THREAD_STACK_SIZE_BYTES*(id+1);
    
    //Initialize the task stack
    scheduled_tasks[id].psp = (uint32_t)OSTaskStkInit(thread_def->pthread,argument,(uint32_t*)psp);
    
    
    //Set thread id as taken
    threads_ids |=(1U<<id); 
    return (uint32_t)id;
}