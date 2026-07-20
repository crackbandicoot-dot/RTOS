#include "uart.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

/* Base address of the UART0 https://www.ti.com/product/LM3S6965 */
#define UART0_BASE 0x4000c000

#define UARTDR(base) (*((volatile uint32_t *)(base + 0x000)))

/*
 * This function is a primitive for printf. This is the base function that
 * printf uses.
 */
int __io_putchar(int ch)
{
  UARTDR(UART0_BASE) = ch;
  return ch;
}
void printNumber(uint32_t num)
{
 if(num==0){
    __io_putchar('0');
    return;
 }
 char stack[10];
 uint32_t top=0;
 while(num){
    stack[top++] = num%10 + '0';
    num = num/10;
 }
 while(top){
    __io_putchar(stack[--top]);
 }
}
void printString(const char* ptr)
{
  while (*ptr != '\0') {
      __io_putchar(*ptr);
      ptr++;
  }
}


