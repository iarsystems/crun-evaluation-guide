/*
  Copyright (c) 2014-2023, IAR Systems AB.
  See LICENSE for detailed license information.
*/

/**
  *  @brief This header exports variables and fucntions from IntMax.c
  */

#ifndef _INTMAX_H_
#define _INTMAX_H_

#if defined(__AS_BOUNDS__) && (PROJECT != maxlib)
#warning This example was created to demonstrate C-RUN Bounds checking
/**
  * Project > Options > Runtime checking > C-RUN Runtime Checking
  * [x] Enable
  *    [ ] Use checked heap
  *    [x] Enable bounds checking
  */
#endif /* __AS_BOUNDS__ */

#include <stdint.h>

#define NUM_ELEMENTS (10)

/** 
  *  Exported variables 
  */
extern uint32_t   MaxInt_Vector[NUM_ELEMENTS];
extern uint32_t * MaxInt_extPointer; // Pointer a element from MaxInt_Vector

/** 
  *  @brief Returns pointer to max value in the `ap` vector
  */
extern uint32_t * MaxInt_GetMax(uint32_t * ap, uint32_t n);

#endif /* _INTMAX_H_ */
