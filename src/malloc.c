#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define ALIGN4(s)         (((((s) - 1) >> 2) << 2) + 4)
#define BLOCK_DATA(b)     ((b) + 1)
#define BLOCK_HEADER(ptr) ((struct _block *)(ptr) - 1)

static int atexit_registered = 0;
static int num_mallocs       = 0;
static int num_frees         = 0;
static int num_reuses        = 0;
static int num_grows         = 0; // # of requests for new block
static int num_splits        = 0;
static int num_coalesces     = 0;
static int num_blocks        = 0; // num of blocks in free list 
static int num_requested     = 0;
static int max_heap          = 0;

/*
 *  \brief printStatistics
 *
 *  \param none
 *
 *  Prints the heap statistics upon process exit.  Registered
 *  via atexit()
 *
 *  \return none
 */
void printStatistics( void )
{
  printf("\nheap management statistics\n");
  printf("mallocs:\t%d\n", num_mallocs );
  printf("frees:\t\t%d\n", num_frees );
  printf("reuses:\t\t%d\n", num_reuses );
  printf("grows:\t\t%d\n", num_grows );
  printf("splits:\t\t%d\n", num_splits );
  printf("coalesces:\t%d\n", num_coalesces );
  printf("blocks:\t\t%d\n", num_blocks );
  printf("requested:\t%d\n", num_requested );
  printf("max heap:\t%d\n", max_heap );
}

struct _block 
{
   size_t  size;         /* Size of the allocated _block of memory in bytes */
   struct _block *next;  /* Pointer to the next _block of allocated memory  */
   bool   free;          /* Is this _block free?                            */
   char   padding[3];    /* Padding: IENTRTMzMjAgU3jMDEED                   */
};


struct _block *heapList = NULL; /* Free list to track the _blocks available */

/*
 * \brief findFreeBlock
 *
 * \param last pointer to the linked list of free _blocks
 * \param size size of the _block needed in bytes 
 *
 * \return a _block that fits the request or NULL if no free _block matches
 *
 * \TODO Implement Next Fit
 * \TODO Implement Best Fit
 * \TODO Implement Worst Fit
 */
struct _block *findFreeBlock(struct _block **last, size_t size) 
{
   struct _block *curr = heapList;

#if defined FIT && FIT == 0
   /* First fit */
   //
   // While we haven't run off the end of the linked list and
   // while the current node we point to isn't free or isn't big enough
   // then continue to iterate over the list.  This loop ends either
   // with curr pointing to NULL, meaning we've run to the end of the list
   // without finding a node or it ends pointing to a free node that has enough
   // space for the request.
   // 
   while (curr && !(curr->free && curr->size >= size)) 
   {
      *last = curr;
      curr  = curr->next;
   }

#endif

// \TODO Put your Best Fit code in this #ifdef block
#if defined BEST && BEST == 0
   /** \TODO Implement best fit here */
   /*while (curr && !(curr->free && curr->size >= size) )
   {
      if (curr->free && curr->size >= size)
      {
         while (curr->next && curr->size < curr->next->size && !(curr->next->free))
         {
            *last = curr;
            curr = curr->next;
         }
      }
      else
      {
         return NULL;
      }
   }*/
   size_t smallest = SIZE_MAX;
   struct _block *bestFitBlock = NULL;
   while (curr)
   {
      if (curr->free && curr->size >= size && curr->size < smallest)
      {
         smallest = curr->size;
         bestFitBlock = curr;
      }
      *last = curr;
      curr = curr->next;
   }
   return bestFitBlock;

#endif

// \TODO Put your Worst Fit code in this #ifdef block
#if defined WORST && WORST == 0
   /** \TODO Implement worst fit here */
   size_t largest= 0;
   struct _block *worstFitBlock = NULL;
   while (curr)
   {
      if (curr->free && curr->size >= size && curr->size > largest)
      {
         largest = curr->size;
         worstFitBlock = curr;
      }
      *last = curr;
      curr = curr->next;
   }
   return worstFitBlock;
   

#endif

// \TODO Put your Next Fit code in this #ifdef block
#if defined NEXT && NEXT == 0
   /** \TODO Implement next fit here */
   if (*last != NULL) // need to start where it left off
   {
      curr = (*last)->next; // curr point to one after last
   }
   while (curr && !(curr->free && curr->size >= size)) // if *last->next not available
   {
      *last = curr; // move last to curr 
      curr = curr->next; // move curr to next
   }
   
#endif

   return curr;
}

/*
 * \brief growheap
 *
 * Given a requested size of memory, use sbrk() to dynamically 
 * increase the data segment of the calling process.  Updates
 * the free list with the newly allocated memory.
 *
 * \param last tail of the free _block list
 * \param size size in bytes to request from the OS
 *
 * \return returns the newly allocated _block of NULL if failed
 */
struct _block *growHeap(struct _block *last, size_t size) 
{
   /* Request more space from OS */
   struct _block *curr = (struct _block *)sbrk(0);
   struct _block *prev = (struct _block *)sbrk(sizeof(struct _block) + size);

   assert(curr == prev);

   /* OS allocation failed */
   if (curr == (struct _block *)-1) 
   {
      return NULL;
   }

   /* Update heapList if not set */
   if (heapList == NULL) 
   {
      heapList = curr;
   }

   /* Attach new _block to previous _block */
   if (last) 
   {
      last->next = curr;
   }

   /* Update _block metadata:
      Set the size of the new block and initialize the new block to "free".
      Set its next pointer to NULL since it's now the tail of the linked list.
   */
   curr->size = size;
   curr->next = NULL;
   curr->free = false;
   return curr;
}

/*
 * \brief malloc
 *
 * finds a free _block of heap memory for the calling process.
 * if there is no free _block that satisfies the request then grows the 
 * heap and returns a new _block
 *
 * \param size size of the requested memory in bytes
 *
 * \return returns the requested memory allocation to the calling process 
 * or NULL if failed
 */
void *malloc(size_t size) 
{
   num_requested += size;
   if( atexit_registered == 0 )
   {
      atexit_registered = 1;
      atexit( printStatistics );
   }

   /* Align to multiple of 4 */
   size = ALIGN4(size);

   /* Handle 0 size */
   if (size == 0) 
   {
      return NULL;
   }

   /* Look for free _block.  If a free block isn't found then we need to grow our heap. */

   struct _block *last = heapList;
   struct _block *next = findFreeBlock(&last, size);

   /* TODO: If the block found by findFreeBlock is larger than we need then:
            If the leftover space in the new block is greater than the sizeof(_block)+4 then
            split the block.
            If the leftover space in the new block is less than the sizeof(_block)+4 then
            don't split the block.
   */
   /*from lecture 2.26 
      1. 25, next point at 3.
      2. 500
      3. 25, free = false, next point at end of 4. 
      4. 475 
      if leftover space, 1. 25. 2. size = 1000
      save next to temp next 
      set ptr->size = requested size : this shrinks 1000 to 500 
      set old size = ptr->size
      ptr->next = (struct _block*)(long long)ptr->next - (oldsize - size), so now next points to the end of 500
      ptr->next = (struct _block)((long long)ptr->next + size)
      ptr->next->inuse = false 
      ptr->next->next = oldnext
      ptr->next->size = oldsize - size - sizeof(struct _block)
      */
   
   if (next->size > (size + sizeof(struct _block)+4))
   {
      

   }

   /* Could not find free _block, so grow heap */
   if (next == NULL) 
   {
      next = growHeap(last, size);
   }

   /* Could not find free _block or grow heap, so just return NULL */
   if (next == NULL) 
   {
      return NULL;
   }
   
   /* Mark _block as in use */
   next->free = false;
   num_mallocs++;
   size_t totalSize = 0;
   totalSize += size;

   max_heap = totalSize + 1024;

   /* Return data address associated with _block to the user */
   return BLOCK_DATA(next);
}

/*
 * \brief free
 *
 * frees the memory _block pointed to by pointer. if the _block is adjacent
 * to another _block then coalesces (combines) them
 *
 * \param ptr the heap memory to free
 *
 * \return none
 */
void free(void *ptr) 
{
   if (ptr == NULL) 
   {
      return;
   }

   /* Make _block as free */
   struct _block *curr = BLOCK_HEADER(ptr);
   assert(curr->free == 0);
   curr->free = true;
   num_frees++;

   /* lecture 2.26
   struct _block *heap_ptr = heapList;
   int largest = 0;
   printf("Heap contents\n");
   while (heap_ptr)
   {
      printf("Size: %d InUse %d\n,", (int)heap_ptr->size, heap_ptr->free); 
      if (heap_ptr->size > largest)
      {
         largest = heap_ptr->size;
      }
      heap_ptr = heap_ptr->next;
   }
   
   */
   /* TODO: Coalesce free _blocks.  If the next block or previous block 
            are free then combine them with this block being freed.
   */
   while (curr != NULL && curr->next != NULL)
   {
      if (curr->free && curr->next->free)
      {
         curr->size = curr->size + sizeof(struct _block*) + curr->next->size;
         curr = curr->next;
         num_coalesces ++;
      }
      curr = curr->next;
   }
}

void *calloc( size_t nmemb, size_t size )
{
   // man calloc: allocate space for nmemb objects that are size bytes
   // returns ptr to allocated mem, mem is bytes of 0 
   // get amount then call malloc then set each byte to 0
   // \TODO Implement calloc

   size_t amount = nmemb * size;
   char *ptr = (char*)malloc(amount);
   int i;
   for (i = 0; i < amount; i++)
   {
      ptr[i] = 0;
   }
   return (void*)ptr;
}

void *realloc( void *ptr, size_t size )
{
   // man realloc: change size of ptr, returns ptr
   // creates new allocation, copies old data pointed to by ptr as will fit, 
   // frees the old allocation
   // if ptr is NULL, realloc is idental to malloc 
   // if size - 0 and ptr is not NULL, a new, minimum sized object is allocated and the original object is freed
   // \TODO Implement realloc
   void *newPtr = malloc(size);
   memcpy(newPtr, ptr, size);
   free(ptr);
   return newPtr;
}



/* vim: IENTRTMzMjAgU3ByaW5nIDIwMjM= -----------------------------------------*/
/* vim: set expandtab sts=3 sw=3 ts=6 ft=cpp: --------------------------------*/
