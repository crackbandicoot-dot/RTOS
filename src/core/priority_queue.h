#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"

typedef struct PriorityQueueItem{
    int32_t priority;
    uint32_t value;
} PriorityQueueItem;

typedef struct PriorityQueue{
    PriorityQueueItem* items;
    uint32_t* valueIdx; //This acts like a dictionary, where values itself are keys, 
                        //is assumed that each value will be in [0,length-1] 
    uint32_t count;     
    uint32_t length;
} PriorityQueue;


#define pq_left(i) (2*(i)+1) 

#define pq_right(i) (2*(i)+2)

#define pq_parent(i) (i<=0?0:((i)-1)/2)

inline void pq_heapify(PriorityQueue* pq, PriorityQueueItem* items,uint32_t* valueIdx,uint32_t length);
inline void pq_initialize(PriorityQueue* pq,PriorityQueueItem* items,uint32_t* valueIdx,uint32_t length);
inline uint32_t pq_peek(PriorityQueue* pq);
inline void pq_sit_up(PriorityQueue* pq,uint32_t currentIndex);
inline void pq_sit_down(PriorityQueue* pq,uint32_t currentIndex);
uint32_t pq_dequeue(PriorityQueue* pq);
void pq_enqueue(PriorityQueue* pq, uint32_t value,int32_t priority);
void pq_change_priority(PriorityQueue*pq,uint32_t value,int32_t priority);
#endif