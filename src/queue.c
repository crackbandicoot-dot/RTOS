#include "queue.h"
void initialize_queue(Queue *q,uint32_t *items,uint32_t length)
{
    q->count = 0;
    q->front = 0;
    q->back = 0;
    q->items_length = length;
    q->items = items;
}
uint32_t peek(Queue* queue)
{
    return queue->items[queue->front]; 
}
uint32_t deqeue(Queue* queue)
{
    queue->count--;
    uint32_t element =queue->items[queue->front];
    queue->front=(queue->front+1)%queue->items_length;
    return  element;
}
uint32_t enqeue(Queue* queue,uint32_t element){
    queue->count++;
    queue->items[queue->back]=element;
    queue->back=(queue->back+1)%queue->items_length;
}