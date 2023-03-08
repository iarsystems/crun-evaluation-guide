/*
  Copyright (c) 2014-2023, IAR Systems AB.
  See LICENSE for detailed license information.
*/

/**
  *  @brief This module contains the source for IntMax_GetMax()
  *         Used to illustrate the difference for C-RUN Bounds checking when
  *         a function belongs to the instrumented main() code as well as 
  *         for when a function belongs to non-instrumented library code
  */

#include "IntMax.h"

uint32_t MaxInt_Vector[NUM_ELEMENTS] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

uint32_t * MaxInt_extPointer = &MaxInt_Vector[4];

/**
  *  @brief Returns a pointer to maximum value in the `ap` vector
  */
uint32_t * MaxInt_GetMax(uint32_t * ap, uint32_t n)
{
  uint32_t * maxp = 0;
  uint32_t   max  = 0;

  for (uint32_t i = 0; i < n; ++i)
  {
    if (ap[i] > max)
    {
      maxp = &ap[i];
      max  = ap[i];
    }
  }
  return maxp;
}

