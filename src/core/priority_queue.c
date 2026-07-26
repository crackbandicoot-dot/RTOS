#include "priority_queue.h"

void pq_initialize(PriorityQueue* pq, PriorityQueueItem* items, uint32_t length)
{
    pq->items = items;
    for (uint32_t i = 0; i < length; i++)
    {
        pq->items[i].priority = INT32_MAX;
    }
    pq->count = 0;
    pq->length = length;
}
uint32_t pq_peek(PriorityQueue* pq)
{
    return pq->items[0].value;
}

//Fix the heap invariant starting from currentIndex as subtree root
void pq_fix_heap_invariant(PriorityQueue* pq,uint32_t currentIndex)
{
    int32_t minPriority, rightPriority;
    uint32_t minIndex, rightIndex;
    do
    {
        minPriority = rightPriority = INT32_MAX;

        minIndex = left(currentIndex);
        if(minIndex < pq->count) minPriority = pq->items[minIndex].priority;

        rightIndex =right(currentIndex);
        if(rightIndex < pq->count) rightPriority = pq->items[rightIndex].priority;
        
        if(rightPriority<minPriority)
        {
            minIndex = rightIndex;
            minPriority=rightPriority;
        }
        if(pq->items[currentIndex].priority<=minPriority) return;
        
        SWAP(pq->items[currentIndex],pq->items[minIndex]);
        //If currentIndex was 0, it will be 0 again, and because heap invariant was fixed, it
        //will return successfully
        currentIndex = parent(currentIndex);
    }
    while(1);
}
void pq_enqueue(PriorityQueue* pq, uint32_t value, int32_t priority)
{
   uint32_t currentIndex = pq->count++;
   PriorityQueueItem* item = pq->items+currentIndex;
   item->priority = priority;
   item->value = value;
   pq_fix_heap_invariant(pq,parent(currentIndex));
}
uint32_t pq_dequeue(PriorityQueue* pq)
{
    uint32_t result = pq->items[0].value;
    PriorityQueueItem* removedNode = pq->items+(--pq->count);
    pq->items[0] = *removedNode;
    removedNode->priority = INT32_MAX;
    //Find the path where the second min will live, and always go to the smallest child
    uint32_t current=0;
    int32_t minPriority,rightPriority;
    uint32_t minIndex,rightIndex;
    while(1)
    {
        minPriority = rightPriority = INT32_MAX;
        
        minIndex = left(current);
        if( minIndex < pq->count) minPriority = pq->items[minIndex].priority;
    
        rightIndex = right(current);
        if(rightIndex < pq->count) rightPriority = pq->items[rightIndex].priority;
        
        if(minPriority>rightPriority)
        {
            minIndex = rightIndex;
            minPriority = rightPriority;
        }
        if( minIndex>=pq->count || pq->items[current].priority < minPriority)
            break;
        
        SWAP(pq->items[current],pq->items[minIndex]);
        current = minIndex;   
    }
    return result;
}