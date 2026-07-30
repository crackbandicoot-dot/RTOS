#include "priority_queue.h"

//Fix the heap invariant starting from currentIndex as subtree root
void pq_sit_up(PriorityQueue* pq,uint32_t currentIndex)
{
    int32_t minPriority, rightPriority;
    uint32_t minIndex, rightIndex;
    do
    {
        minPriority = rightPriority = INT32_MAX;

        minIndex = pq_left(currentIndex);
        if(minIndex < pq->count) minPriority = pq->items[minIndex].priority;

        rightIndex =pq_right(currentIndex);
        if(rightIndex < pq->count) rightPriority = pq->items[rightIndex].priority;
        
        if(rightPriority<minPriority)
        {
            minIndex = rightIndex;
            minPriority=rightPriority;
        }
        if(pq->items[currentIndex].priority<=minPriority) return;
        SWAP(pq->items[currentIndex],pq->items[minIndex]);
        pq->valueIdx[ pq->items[currentIndex].value ] = currentIndex;
        pq->valueIdx[ pq->items[minIndex].value ] = minIndex; 
        //If currentIndex was 0, it will be 0 again, and because heap invariant was fixed, it
        //will return successfully
        currentIndex = pq_parent(currentIndex);
    }
    while(1);
}
void pq_sit_down(PriorityQueue* pq,uint32_t currentIndex)
{
    int32_t minPriority,rightPriority;
    uint32_t minIndex,rightIndex;
    while(1)
    {
        minPriority = rightPriority = INT32_MAX;
        
        minIndex = pq_left(currentIndex);
        if( minIndex < pq->count) minPriority = pq->items[minIndex].priority;
    
        rightIndex = pq_right(currentIndex);
        if(rightIndex < pq->count) rightPriority = pq->items[rightIndex].priority;
        
        if(minPriority>rightPriority)
        {
            minIndex = rightIndex;
            minPriority = rightPriority;
        }
        if( minIndex>=pq->count || pq->items[currentIndex].priority < minPriority)
            break;
        
        SWAP(pq->items[currentIndex],pq->items[minIndex]);
        pq->valueIdx[ pq->items[currentIndex].value ] = currentIndex;
        pq->valueIdx[ pq->items[minIndex].value ] = minIndex;
        currentIndex = minIndex;   
    }
}
void pq_initialize(PriorityQueue* pq, PriorityQueueItem* items, uint32_t* valueIdx,uint32_t length)
{
    pq->items = items;
    pq->valueIdx = valueIdx;
    for (uint32_t i = 0; i < length; i++)
    {
        pq->items[i].priority = INT32_MAX;
        pq->valueIdx[i] = UINT32_MAX;
    }
    pq->count = 0;
    pq->length = length;
}

void pq_heapify(PriorityQueue* pq, PriorityQueueItem* items, uint32_t* valueIdx,uint32_t length)
{
    pq->items = items;
    pq->valueIdx = valueIdx;
    pq->length=length;
    pq->count =0;
    if(length>0)
    {
        uint32_t start = (uint32_t)ceil(log2(length));
        for(uint32_t i = 1<<(start-2);i>0;i--)
        {
            pq_sit_down(pq,i);
        }
        pq_sit_down(pq,0);
    }
}

uint32_t pq_peek(PriorityQueue* pq)
{
    return pq->items[0].value;
}


void pq_enqueue(PriorityQueue* pq, uint32_t value, int32_t priority)
{
   uint32_t currentIndex = pq->count++;
   PriorityQueueItem* item = pq->items+currentIndex;
   item->priority = priority;
   item->value = value;
   pq->valueIdx[value] = currentIndex;
   pq_sit_up(pq,pq_parent(currentIndex));
}
uint32_t pq_dequeue(PriorityQueue* pq)
{
    uint32_t result = pq->items[0].value;
    PriorityQueueItem* removedNode = pq->items+(--pq->count);
    pq->items[0] = *removedNode;
    removedNode->priority = INT32_MAX;
    pq->valueIdx[result] =-1;
    pq_sit_down(pq,0);
    return result;
}
void pq_change_priority(PriorityQueue*pq,uint32_t value,int32_t priority)
{
    //Because both pq_sit_up and pq_sit_down do nothing in case they can't up or down
    //This remains O(log n)
    if(pq->valueIdx[value]!=UINT32_MAX){
        pq->items[pq->valueIdx[value]].priority = priority;
        pq_sit_up(pq,pq->valueIdx[value]);  
        pq_sit_down(pq,pq->valueIdx[value]);
    }
}