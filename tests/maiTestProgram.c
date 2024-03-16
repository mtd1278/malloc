#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    
    // must split, coalesce, resuse 
    clock_t start, end;
    double totalRuntime;
    printf("Running test program \n");
    start = clock();
    char* ptr1 = (char*)malloc(1000);
    
    char* first_ptr_array[80000]; 
    int i; 
    for (i = 0; i < 80000; i++)
    {
        if (i%2 == 0)
        {
            first_ptr_array[i] = (char*)malloc(2000);
        }
        else
        {
             first_ptr_array[i] = (char*)malloc(1000);
        }
        first_ptr_array[i] =first_ptr_array[i];
        
    }
    free(ptr1);
    free(first_ptr_array[3]);
    free(first_ptr_array[7]);
    char* ptr2 = (char*)malloc(3000);

    for (i = 0; i < 80000; i++)
    {
        if (i%5 == 0 || i%8 == 0)
        {
            free(first_ptr_array[i]);
        }

    }
   
    
    for (i = 0; i < 80000; i++)
    {
        if (i%5 == 0)
        {
            first_ptr_array[i] = (char*)malloc(500);
        }
        else if(i%8 == 0)
        {
            first_ptr_array[i] = (char*)malloc(1000);
        }
        first_ptr_array[i] =first_ptr_array[i];
        
    }

    end = clock();
    totalRuntime = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Runtime: %f seconds\n", totalRuntime);

    return 0;
}