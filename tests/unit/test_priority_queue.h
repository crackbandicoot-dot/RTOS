#ifndef TEST_PRIORITY_QUEUE
#define TEST_PRIORITY_QUEUE
#include "minunit.h"
#include <stdint.h>
#include <math.h>
// Now include the source file under test.
// This brings its functions into the test binary.
#include "../../src/core/priority_queue.h"
#define PRIORITY_QUEUE_LENGTH 7 

void check(uint32_t* permutation,uint32_t length,void* context)
{
    PriorityQueue* pq = (PriorityQueue*)context;
    mu_assert(pq->count==0,"Priority queue count is not 0 just after initialize it");
    uint32_t min = UINT32_MAX;
    for (uint32_t i=0;i<length;i++)
    {
        printf("%d",permutation[i]);
        if(permutation[i]<min){
            min=permutation[i];
        }
        pq_enqueue(pq,permutation[i],permutation[i]);
        mu_assert(pq->count==i+1,"Priority queue count is not %d"
                                "after inserting %d-th element",
        
                                i+1,i+1);
        mu_assert(pq_peek(pq)==min,"The element on the top of the priority queue is not the minimum after push");
    }
    //pq_initialize(pq,pq->items,length);
    for (uint32_t i =1; i<=length; i++)
    {
        uint32_t top = pq_peek(pq);
        uint32_t extracted = pq_dequeue(pq);
        mu_assert(top==extracted,"The element on the top of the priority queue"
            "is not the minimum after pop");
        mu_assert(pq->count==length-i,"Priority queue count is not %d"
                                    "after extracting %d-th element",
                                    length-i,i);
        mu_assert(extracted==i,"Extracted element is not the minimum after pop");
    } 
    printf(" OK\n");
}
// Test cases
static int test_priority_queue(void) {
    PriorityQueueItem arr[PRIORITY_QUEUE_LENGTH];
    PriorityQueue pq;
    pq_initialize(&pq,arr,PRIORITY_QUEUE_LENGTH);
    mu_assert_permutations(PRIORITY_QUEUE_LENGTH,check,&pq);
    return 0; 
}


// Runner that calls all tests
int run_priority_queue_tests(void) {
    mu_run_test(test_priority_queue);
    return tests_failed;
}
#endif