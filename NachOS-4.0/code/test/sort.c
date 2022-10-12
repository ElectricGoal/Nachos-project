#include "syscall.h"

int main()
{
    int n;
    int arr[100];
    char choose; // = i for increasing, d for decreasing
    int i, j, tmp;

    PrintString("Enter a number of elements in array (0 < n <= 100): ");
    n = ReadNum();

    // Handle n out range (0; 100]
    while (n <= 0 || n > 100)
    {
        PrintString("Invalid number! \n");
        PrintString("Enter a number of elements in array (0 < n <= 100): ");
        n = ReadNum();
    }
    
    PrintString("Enter elements of array: \n");
    for (i = 0; i < n; ++i)
        arr[i] = ReadNum();

    /* Choose sort array by increasing or decreasing */
    PrintString("Choose the order to sort: \n");
    PrintString("   i for increasing order. \n");
    PrintString("   d for decreasing order. \n");
    PrintString("Enter the order: ");
    choose = ReadChar();

    switch (choose)
    {
    case 'i': // bubble sort by increasing
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n - i -1; ++j)
            {
                if (arr[j] > arr[j + 1])
                {
                    tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
        }
        break;
    case 'd': // bubble sort by decreasing
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n - i - 1; ++j)
            {
                if (arr[j] < arr[j + 1])
                {
                    tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
        }
        break;
    default: // choose != 'i' or 'd'
        PrintString("Invalid order! \n");
        Halt();
        return 0;
    }
    
    // Print result
    PrintString("Sorted array: \n");
    for (i = 0; i < n; ++i)
    {
        PrintNum(arr[i]);
        PrintChar(' ');
    }
    PrintString("\n");

    Halt();
    return 0;
}