#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    clock_t start, end;
    double totalRuntime;
    printf("Running test program \n");
    start = clock();
    
    char* first_ptr_array[10000]; 
    int i; 
    for (i = 0; i < 10000; i++)
    {
        if (i%3 == 0)
        {
            first_ptr_array[i] = (char*)malloc(40);
        }
        else if(i%11 == 0)
        {
            first_ptr_array[i] = (char*)malloc(7);
        }
        else if(i%14 == 0)
        {
            first_ptr_array[i] = (char*)malloc(20);
        }
        else if(i%17 == 0)
        {
            first_ptr_array[i] = (char*)malloc(18);
        }
        else if(i%23 == 0)
        {
            first_ptr_array[i] = (char*)malloc(32);
        }
        else if(i%78 == 0)
        {
            first_ptr_array[i] = (char*)malloc(11);
        }
        else if(i < 5000)
        {
            first_ptr_array[i] = (char*)malloc(10);
        }
        else
        {
            first_ptr_array[i] = (char*)malloc(50);
        }
        first_ptr_array[i] =first_ptr_array[i];
        
    }

    for (i = 0; i < 10000; i++)
    {
        if (i%3 == 0 || i%11 == 0 || i%14 == 0 || i%17 == 0 || i%23 == 0 || i%78 == 0 || i%2 != 0)
        {
            free(first_ptr_array[i]);
        }
    }
    
    char * ptr1 = (char*)malloc(19);
    char * ptr2 = (char*)malloc(23);
    char * ptr3 = (char*)malloc(20);
    char * ptr4 = (char*)malloc(30);
    char * ptr5 = (char*)malloc(60);
    char * ptr6 = (char*)malloc(5);
    char * ptr7 = (char*)malloc(8);
    char * ptr8 = (char*)malloc(12);
    char * ptr9 = (char*)malloc(90);
    char * ptr10 = (char*)malloc(1);
    char * ptr11 = (char*)malloc(2);
    char * ptr12 = (char*)malloc(15);
    char * ptr13 = (char*)malloc(114);
    char * ptr14 = (char*)malloc(6);
    char * ptr15 = (char*)malloc(1);
    char * ptr16 = (char*)malloc(30);
    char * ptr17 = (char*)malloc(18);
    char * ptr18 = (char*)malloc(14);
    char * ptr19 = (char*)malloc(12);
    char * ptr20 = (char*)malloc(90);
    char * ptr21 = (char*)malloc(10);
    char * ptr22 = (char*)malloc(17);
    char * ptr23 = (char*)malloc(12);
    char * ptr24 = (char*)malloc(3);
    char * ptr25 = (char*)malloc(200);
    char * ptr26 = (char*)malloc(5);
    char * ptr27 = (char*)malloc(20);
    char * ptr28 = (char*)malloc(37);
    char * ptr29 = (char*)malloc(32);
    char * ptr30 = (char*)malloc(12);
    char * ptr31 = (char*)malloc(97);
    char * ptr32 = (char*)malloc(73);
    char * ptr33 = (char*)malloc(68);
    char * ptr34 = (char*)malloc(4);
    char * ptr35 = (char*)malloc(43);
    char * ptr36 = (char*)malloc(52);
    char * ptr37 = (char*)malloc(1);
    char * ptr38 = (char*)malloc(56);
    char * ptr39 = (char*)malloc(72);
    char * ptr40 = (char*)malloc(97);
    char * ptr41 = (char*)malloc(34);
    char * ptr42 = (char*)malloc(28);
    char * ptr43 = (char*)malloc(29);
    char * ptr44 = (char*)malloc(33);
    char * ptr45 = (char*)malloc(25);
    char * ptr46 = (char*)malloc(14);
    char * ptr47 = (char*)malloc(13);
    char * ptr48 = (char*)malloc(26);
    char * ptr49 = (char*)malloc(46);
    char * ptr50 = (char*)malloc(47);
    char * ptr51 = (char*)malloc(48);
    char * ptr52 = (char*)malloc(59);
    char * ptr53 = (char*)malloc(111);
    char * ptr54 = (char*)malloc(53);
    char * ptr55 = (char*)malloc(52);
    char * ptr56 = (char*)malloc(5);
    char * ptr57 = (char*)malloc(4);
    char * ptr58 = (char*)malloc(7);
    char * ptr59 = (char*)malloc(100);
    char * ptr60 = (char*)malloc(30);
    char * ptr61 = (char*)malloc(1);
    char * ptr62 = (char*)malloc(2);
    char * ptr63 = (char*)malloc(8);
    char * ptr64 = (char*)malloc(20);
    char * ptr65 = (char*)malloc(31);
    char * ptr66 = (char*)malloc(38);
    char * ptr67 = (char*)malloc(239);
    char * ptr68 = (char*)malloc(1);

    end = clock();
    totalRuntime = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Runtime: %f seconds\n", totalRuntime);

    return 0;
}