#include "syscall.h"

int main()
{
    int num;
    
    num = RandomNum();
    
    PrintString("Random number: ");
    PrintNum(num);
    PrintChar('\n');
    
    Halt();
}