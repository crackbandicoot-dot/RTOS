#ifndef TEST_QUEUE
#define TEST_QUEUE
#include "minunit.h"

// Now include the source file under test.
// This brings its functions into the test binary.
#include "../../src/core/queue.h"

// Test cases
static int test_queue(void) {

    uint32_t length = 10;
    uint32_t arr[length];
    Queue queue;
    initialize_queue(&queue,arr,length);
    mu_assert(queue.count==0, "Queue initialized with count different than  0");
    for (uint32_t i = 0; i < length; i++)
    {
        enqeue(&queue,i+1);
        mu_assert(queue.count==i+1,"Count was'nt updated after putting %d on the queue",i+1);
        uint32_t front = peek(&queue);
        mu_assert(front==1,"Expected front of the queue to not change until something outs the queue, it should be 1");
    }
    for (uint32_t i = 0; i < length; i++)
    {
        uint32_t front = peek(&queue);
        mu_assert(front==i+1,"Front of queue should have %d as value",i+1);
        uint32_t current = deqeue(&queue);
        mu_assert(current==front,"The element out of the queue should be the prev on the front");
        uint32_t newFront = peek(&queue);
        mu_assert((front==length)|(front+1)==newFront,"Order on queue is invalid prevFront %d newFront %d",front,newFront);
    }
    return 0;
}


// Add more tests as needed...

// Runner that calls all tests
int run_queue_tests(void) {
    mu_run_test(test_queue);
    return tests_failed;
}
#endif