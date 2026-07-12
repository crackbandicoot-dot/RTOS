#ifndef KERNEL_OBJECTS_H
#define KERNEL_OBJECTS_H
/*
Memory avaible is 64 KB for data, and 256 KB for code
This is the memory layout representation:

-------------------------------------

User memory 32KB ( 32768 to be exact)

-------------------------------------- 

Kernel data 28KB (about), but this can change

---------------------------------------


Stack 1KB (1024 bytes to be exact)

---------------------------------------

Heap 3KB (3072 bytes to be exact)

---------------------------------------
*/
//User space memory on bytes 
//(close to 32 KB, but divisible by 4 to be exacts 2^15)
#define USER_BYTES 32768U 
#endif
