#ifndef MINUNIT_H
#define MINUNIT_H
#include <stdio.h>
#include <stdint.h>
static int tests_run = 0;         // number of assertions
static int tests_failed = 0;      // assertions that failed
static int test_cases_run = 0;    // number of test functions executed

#define mu_assert(test, format, ...)                                  \
    do {                                                              \
        tests_run++;                                                  \
        if (!(test)) {                                                \
            printf("FAIL: " format " (%s:%d)\n",                      \
                   ##__VA_ARGS__, __FILE__, __LINE__);                \
            tests_failed++;                                           \
            return 1;                                                 \
        }                                                             \
    } while (0)



#define mu_run_test(test) do { \
    printf("Running %s...\n", #test); \
    test_cases_run++;          /* count the test function */ \
    if (test()) { tests_failed++; } \
} while (0)

#define mu_print_results() do { \
    printf("\n--- Test Results ---\n"); \
    printf("  Test cases: %d\n", test_cases_run); \
    printf("  Assertions : %d\n", tests_run); \
    printf("  Failed     : %d\n", tests_failed); \
    if (tests_failed == 0) { \
        printf("  ALL TESTS PASSED\n"); \
    } else { \
        printf("  SOME TESTS FAILED\n"); \
    } \
} while (0)



typedef void (*PermutationChecker)(uint32_t* permutation,uint32_t length,void* context);
void test_permutations(uint32_t visited, uint32_t idx,uint32_t length,uint32_t* permutation, PermutationChecker check,void* context)
{
    if(idx==length){
        check(permutation,length,context);
        return;
    }
    for(uint32_t i=0;i<length;i++){
        //If it has'nt been visited
        if((visited&(1<<i))==0)
        {
            permutation[idx]=i+1;
            //Mark as visited
            test_permutations(visited|(1<<i),idx+1,length,permutation,check,context);    
        }
    }

} 
#define mu_assert_permutations(length,check,context) do { \
    uint32_t permutation[length] ; \
    test_permutations(0,0,length,permutation,check,context);\
} while (0)

#endif