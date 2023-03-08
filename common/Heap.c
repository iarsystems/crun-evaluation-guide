/*
  Copyright (c) 2014-2023, IAR Systems AB.
  See LICENSE for detailed license information.
*/

/**
  * @brief Demonstration for the C-RUN Checked heap features
  */

#include <stdlib.h>
#include <stdio.h>
/* The prototypes for the heap checking functions are in iar-dlmalloc.h */
#include <iar_dlmalloc.h>

//#define FULLEDITION /* For full editions of C-RUN only */

void HeapFunc1()
{
char Temp[10];
char *c1 = (char *)malloc(10);
char *c2 = Temp;

  c1++;

  free(c1); /* not the start of a block */
  free(c2);   /* non-matched new and free */

  free(c1);   /* free a block more than once */

}

void HeapFunc2()
{
char *c = malloc(10000); /* out of space */
  
  free(c);
}

/* This function can only be used with a full edition of C-RUN since the codesize will exceed the size limitation */
void HeapFunc3()
{
  int listsize = 0;
  char *p = malloc(10);
  for (int i = 0; i<10;++i)
  {
    p[i] = i;
  }
  p = 0; // Oops...
  
/* Check the heap for unreferenced blocks, see "Detecting heap memory leaks" 
   in the C-SPY debugging guide for an explanation of how this works 
   At the first check we have one allocated block and a pointer that no longer points to the block. 
   Note: The leak check is conservative, so it can sometimes miss a leaked block if there 
   are for example references to the block left in a CPU register after a function call. */
  __iar_check_leaks();  // Reports a leak
  
/* If we for some reason know that we leak memory intentionally we can mark all 
   blocks as non-leaked at this point. */
   
  __iar_leaks_ignore_all();
  __iar_check_leaks();  // Reports no leak!
  
/* Or we can be more explicit than above. We can mark a specific block as non-leaked. */
  p = malloc(12);
  __iar_leaks_ignore_block((void*)p); // Note that this call requires EWARM 7.30 and up.
  p = malloc(13); // Intentionally leaking previously allocated block.
  __iar_check_leaks();  // Reports no leak

  
  /* Use the delayed-free list to help in finding use-after-free errors */
  /* Freeds block are not immediately returned to the free list, so a heap integrity */
  /* check can pinpoint writes to a block that should not be used */
  /* We must first set a max size for the delayed-free list */
  listsize = __iar_set_delayed_free_size(2);
  
  /* Do some heap stuff */
  free(p);
  p[5] = 'O'; /* Use after free */
  __iar_check_heap_integrity(); /* Detects and reports a free block has been corrupted */
  
  __iar_check_leaks();  /* Still no leak... */

}

int main(void)
{
  HeapFunc1();
  HeapFunc2();

#ifdef FULLEDITION
  HeapFunc3(); /* This function can only be used with a full edition of C-RUN since the codesize will exceed the size limitation */
#endif
 
  return 0;
}

