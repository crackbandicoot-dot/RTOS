#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdint.h>

typedef struct PriorityQueueItem{
    int32_t priority;
    uint32_t value;
} PriorityQueueItem;

typedef struct PriorityQueue{
    PriorityQueueItem* items;
    uint32_t count;
    uint32_t length;
} PriorityQueue;


#define left(i) (2*(i)+1) 

#define right(i) (2*(i)+2)

#define parent(i) (i<=0?0:((i)-1)/2)
#define SWAP(a,b) do {typeof(a) tmp=a; a=b; b=tmp;} while(0)

void pq_initialize(PriorityQueue* pq,PriorityQueueItem* items,uint32_t length);
uint32_t pq_peek(PriorityQueue* pq);
void pq_fix_heap_invariant(PriorityQueue* pq,uint32_t currentIndex);
uint32_t pq_dequeue(PriorityQueue* pq);
void pq_enqueue(PriorityQueue* pq, uint32_t value,int32_t priority);

#endif
