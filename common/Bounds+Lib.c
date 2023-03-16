/*
  Copyright (c) 2014-2023, IAR Systems AB.
  See LICENSE for detailed license information.
*/

/**
  * @brief Demonstration for the C-RUN bounds checking features
  *        for applications relying on pre-built libraries
  */

#include <stdint.h>
#include <stdio.h>

/** 
  * The internal symbol __AS_BOUNDS__ can be used to identify when the application
  * was built with C-RUN `bounds checking` instrumentation. Alongside the pragma 
  * `default_no_bounds`, it can be used to inform the linker that the library 
  * `MaxLib` was built with no `bounds checking` capabilities.
  */
#ifdef __AS_BOUNDS__
#pragma default_no_bounds=on
#include "IntMax.h"
#pragma default_no_bounds=off
#else
#include "IntMax.h"
#endif /* __AS_BOUNDS__ */

/**
  * [x] Check pointers from non-instrumented functions
  *  +-> In this case, we need to give external pointers new bounds 
  *  +-> with the built-in function `__as_make_bounds()`
  */
#if defined(__AS_BOUNDS__) && defined(CHECK_POINTERS) // set @ Preprocessor
#define CRUN_MAKE_BOUNDS(pointer, size)  ( pointer = __as_make_bounds(pointer, size) )
#define CRUN_MAKE_BOUNDS_VARIANT(pA, pB, size) ( pA = __as_make_bounds(pA, pB, size) )
#else
#define CRUN_MAKE_BOUNDS(pointer, size)
#define CRUN_MAKE_BOUNDS_VARIANT(pA, pB, size)
#endif

uint32_t vector[NUM_ELEMENTS] = { 1, 3, 5, 7, 11, 0, 8, 6, 4, 2 };

void main(void)
{
  uint32_t * ap = 0;

  ap = MaxInt_GetMax(vector, NUM_ELEMENTS);
  CRUN_MAKE_BOUNDS(ap, 1);
  printf("Max value from vector: %i\n", *ap);
  
  ap = MaxInt_GetMax(MaxInt_Vector, NUM_ELEMENTS);
  CRUN_MAKE_BOUNDS(ap, 1);
  printf("Max value from MaxInt_Vector: %i\n", *ap); // OK
  printf("Another value from MaxInt_Vector: %i\n", *(ap + 1)); 
  
  /** 
    * MaxInt_extPointer is an external indirect pointer without bounds checking
    * For performing indirect access, use: __as_make_bounds(pA, pB, size)
    */
  CRUN_MAKE_BOUNDS_VARIANT(MaxInt_extPointer, MaxInt_Vector, MaxInt_Vector + 9);
  printf("MaxInt_Vector accessed via another pointer: %i \n", *MaxInt_extPointer);
}
