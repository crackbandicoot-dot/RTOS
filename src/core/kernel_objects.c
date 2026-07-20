#include "kernel_objects.h"
#include "task.h"
//User space memory (stack only for simplicity rigth now)
char userMemory[USER_BYTES];

//Kernel structures

//Scheduling structs
uint32_t ready_arr[MAX_THREADS*4];
uint32_t waiting_arr[MAX_THREADS*4];
Task scheduled_tasks[MAX_THREADS];
Queue ready_queue;
Queue waiting_queue;
uint32_t current_threads=0;
int threads_ids=0;
uint32_t running_thread;
Task* pxCurrentTCB;