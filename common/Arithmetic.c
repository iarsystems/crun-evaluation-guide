/*
  Copyright (c) 2014-2023, IAR Systems AB.
  See LICENSE for detailed license information.
*/

/**
  * @brief Demonstration for the C-RUN Arithmetic checking features
  */

#include <stdint.h>

/* Global variables */
int32_t i = 5, j = 0;
int16_t s = 0;
int8_t ch = 0;

/* 
 * [x] Integer overflow
 *    [ ] Including unsigned
 */
int32_t signed_over(int32_t a)
{
  return a + 2;
}

/* 
 * [x] Integer overflow
 *    [x] Including unsigned
 */
uint32_t unsigned_over(uint32_t a)
{
  return a + 2u;
}

/* 
 * [x] Integer conversion
 *    [ ] Including explicit casts
 */
void conv(void)
{
  ch = i * 100;
}

/* 
 * [x] Integer conversion
 *    [x] Including explicit casts
 */
void explicit_conv(void)
{
  ch = (char)(i * 100);
}

/* 
 * [x] Integer shift overflow
 *    [ ] Including unsigned shifts
 */
int32_t signed_shift_left(int32_t a)
{
  return a << 1;
}

/* 
 * [x] Integer shift overflow
 *    [x] Including unsigned shifts
 */
uint32_t unsigned_shift_left(uint32_t a)
{
  return a << 1u;
}

/*
 * [x] Division by zero
 */
void div(void)
{
  j = i / j;  
}

/*
 * [x] Unhandled switch case
 */
void sw(void)
{
  switch(ch)
  {
  case 0: i = 3; break;
  case 5: i = 2; break;
  }
}

/**
  * @brief The main() function
  */
int main(void)
{
  int32_t  a = 0x7FFFFFFF;
  uint32_t b = 0xFFFFFFFF;
  {
    conv();
    explicit_conv();
  }
  {
    a = signed_over(a);
    b = unsigned_over(b);
  }
  {
    a = signed_shift_left(a);
    b = unsigned_shift_left(b);
  }
  div();
  sw();
    
  return 0;
}
