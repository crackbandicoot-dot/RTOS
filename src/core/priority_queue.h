#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdint.h>
#include "utils.h"

typedef struct PriorityQueueItem{
    int32_t priority;
    uint32_t value;
} PriorityQueueItem;

typedef struct PriorityQueue{
    PriorityQueueItem* items;
    uint32_t count;
    uint32_t length;
} PriorityQueue;


#define pq_left(i) (2*(i)+1) 

#define pq_right(i) (2*(i)+2)

#define pq_parent(i) (i<=0?0:((i)-1)/2)


inline void pq_initialize(PriorityQueue* pq,PriorityQueueItem* items,uint32_t length);
inline uint32_t pq_peek(PriorityQueue* pq);
inline void pq_fix_heap_invariant(PriorityQueue* pq,uint32_t currentIndex);
uint32_t pq_dequeue(PriorityQueue* pq);
void pq_enqueue(PriorityQueue* pq, uint32_t value,int32_t priority);

#endif