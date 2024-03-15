#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Performance, Relative comparision of number of splits and heap growth, Heap fragmentation, Max heap size, RUN TIME
    clock_t start, end;
    double totalRuntime;
    start = clock();
    printf("Running test program \n");

    char* first_ptr_array[100000]; // 100k
    int i;
    for (i = 0; i < 100000; i++)
    {
        first_ptr_array[i] = (char*)malloc(2000);
        first_ptr_array[i] =first_ptr_array[i];
    }

    for (i = 0; i < 5000; i++)
    {
        if (i%2 == 3)
        {
            free(first_ptr_array[i]);
        }
    }

    char* ptr1 = (char*)malloc(1000);
    free(ptr1);
    char* second_ptr_array[500000]; // 2mil 
    for (i = 0; i < 500000; i++)
    {
        second_ptr_array[i] = (char*)malloc(1500);
        second_ptr_array[i] =second_ptr_array[i];
    }
    for (i = 0; i < 500000; i++)
    {
        if (i%2 != 0)
        {
            free(second_ptr_array[i]);
        }
    }

    end = clock();
    totalRuntime = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Runtime: %f seconds\n", totalRuntime);

    return 0;
}