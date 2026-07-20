#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>

typedef struct Queue
{
    uint32_t* items;
    uint32_t count;
    uint32_t items_length;
    uint32_t back;
    uint32_t front;
} Queue;
/// @brief Create a queue, if items have length >= 2
/// @param items The array that the queue will use 
/// @param length The length of the initial array the code will use
/// @return 
void initialize_queue(Queue* q,uint32_t* items,uint32_t length);
uint32_t peek(Queue* queue);
uint32_t deqeue(Queue* queue);
uint32_t enqeue(Queue* queue,uint32_t element);
#endif