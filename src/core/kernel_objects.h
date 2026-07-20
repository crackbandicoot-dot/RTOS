#ifndef KERNEL_OBJECTS_H
#define KERNEL_OBJECTS_H
#include <stdint.h>
#include "queue.h"
#include "task.h"
/*
Memory avaible is 64 KB for data, and 256 KB for code
This is the memory layout representation:

-------------------------------------

User memory 32KB ( 32768 to be exact)

-------------------------------------- 

Kernel data 28KB (about), but this can change

---------------------------------------


Stack 1KB (1024 bytes to be exact)

---------------------------------------

Heap 3KB (3072 bytes to be exact)

---------------------------------------
*/





//User space memory on bytes 
//(close to 32 KB, but divisible by 4 to be exacts 2^15)
#define USER_BYTES 32768U 
extern char userMemory[USER_BYTES];

#define MAX_THREADS 8U
#define THREAD_STACK_SIZE_BYTES  (USER_BYTES/MAX_THREADS)
extern uint32_t ready_arr[MAX_THREADS*4];
extern uint32_t waiting_arr[MAX_THREADS*4];
extern Task scheduled_tasks[MAX_THREADS];
extern Queue ready_queue;
extern Queue waiting_queue;
extern uint32_t current_threads;
extern int threads_ids;
extern uint32_t running_thread;
extern Task* pxCurrentTCB;
#endif
