/** @file Heap.c
 *  Demonstration for the C-RUN Checked-heap features
 *
 *  Copyright (c) 2014-2024, IAR Systems AB.
 *  See LICENSE for detailed license information.
 */


#include <stdlib.h>
#include <stdio.h>
/* The prototypes for the heap checking functions are in iar-dlmalloc.h */
#include <iar_dlmalloc.h>

/** Enables HeapFunc3() for detecting `heap memory leaks`
 *  Requires a ***full edition of C-RUN***
 */
//#define CRUN_FULL_EDITION


/** @brief `Heap usage error` demonstration
 */
void HeapFunc1()
{
  char Temp[10];
  char *c1 = (char *)malloc(10);
  char *c2 = Temp;

  c1++;
  /* Heap usage error: not the start of a heap block */
  free(c1);
  /* Heap usage error: non-matched new and free */
  free(c2);
  /* Heap usage error: free a heap block more than once */
  free(c1);
}

/** @brief `Out of heap space` demonstration
 */
void HeapFunc2()
{
  /* Out of heap space: There is no more heap to allocate */
  char *c = malloc(0x1000);

  free(c);
}

/** @brief `Heap memory leak detection` demonstration
 */
void HeapFunc3()
{
#ifdef CRUN_FULL_EDITION
  int listsize = 0;
  char *p = malloc(10);

  /** At this first check we have one allocated heap block and a pointer that
   *  no longer points to the block. The leak check is conservative, so
   *  it can sometimes miss a leaked block if there are, for example, references
   *  to the block left in a CPU register after a function call.
   *
   *  NOTE: See `Detecting heap memory leaks` in the `C-SPY Debugging Guide` for detailed information.
   */
  for (int i = 0; i < 10; ++i)
  {
    p[i] = i;
  }
  p = 0;                // Oops...
  __iar_check_leaks();  // Reports a leak!

/* If we for some reason know that we leak memory intentionally we can mark all
   blocks as non-leaked at this point. */
  __iar_leaks_ignore_all();
  __iar_check_leaks();  // Reports no leak.

  /* Or we can be more explicit than above. We can mark a specific block as non-leaked. */
  p = malloc(12);
  __iar_leaks_ignore_block((void*)p);
  /* Intentionally leaking previously allocated block */
  p = malloc(13);
  __iar_check_leaks();  // Reports no leak.

  /** Use the delayed-free list to help in finding use-after-free errors.
   *  We must first set a max size for the delayed-free list.
   *
   *  NOTE: Freed blocks are not immediately returned to the free list, so the
   *  heap integrity check can pinpoint writes to a block that should not be used
   */
  listsize = __iar_set_delayed_free_size(2);

  /* Do some heap stuff */
  free(p);
  /* Use after free */
  *(p + 5) = 'O';
  /* Detects and reports a free block has been corrupted */
  __iar_check_heap_integrity();
  __iar_check_leaks();  // Reports no leak.
#endif /* CRUN_FULL_EDITION */
}

int main(void)
{
  HeapFunc1();
  HeapFunc2();
  /* HeapFunc3() can only be used with a full edition of C-RUN
     since the resource consumption will exceed the code size limitation  */
  HeapFunc3();

  return 0;
}
