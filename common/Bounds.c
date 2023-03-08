/*
  Copyright (c) 2014-2023, IAR Systems AB.
  See LICENSE for detailed license information.
*/

/**
  * @brief Demonstration for the C-RUN bounds checking features in cases where 
  *        it is possible to control the compilation of the entire program
  */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "IntMax.h"

#define NUM_ELEMENTS (10)

uint32_t vector[NUM_ELEMENTS] = { 1, 3, 5, 7, 11, 0, 8, 6, 4, 2 };

void main(void)
{
  uint32_t *ap = 0;
  int8_t   *cp = 0;
  
  ap = MaxInt_GetMax(vector, NUM_ELEMENTS);
  printf("Max value from vector: %i \n", *ap);
  
  ap = MaxInt_GetMax(MaxInt_Vector, NUM_ELEMENTS);
  printf("Max value from MaxInt_Vector: %i\n", *ap);                   // OK
  printf("Some other value from MaxInt_Vector: %i\n", *(ap + 1));      // Is this out of bounds?
  printf("And yet another value from MaxInt_Vector: %i\n", *(ap + 2)); // Is this out of bounds?
  
  /**
    *  Indirect pointer access requires an entry in C-RUN's `Global bounds table`
    */
  printf("MaxInt_Vector accessed via another pointer: %i\n", *MaxInt_extPointer);

  cp = malloc(NUM_ELEMENTS);
  cp[10] = 'A';
}







