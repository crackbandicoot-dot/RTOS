#include "cmsis_os.h"
#include "kernel_objects.h"
#include "queue.h"
#include <strings.h>
#include <stdint.h>
#define MAX_THREADS 8U
#define THREAD_STACK_SIZE_BYTES  (USER_BYTES/MAX_THREADS)

uint32_t ready_arr[MAX_THREADS*4];
uint32_t waiting_arr[MAX_THREADS*4];
uint32_t waiting_arr[MAX_THREADS*4];
Queue ready_queue;
Queue waiting_queue;
static uint32_t current_threads = 0;
static int threads_ids;

void schedule(){

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
    //TODO do some for here
    const int id = ffs(~threads_ids);
    threads_ids<<id;
    return (uint32_t)id;
    
}