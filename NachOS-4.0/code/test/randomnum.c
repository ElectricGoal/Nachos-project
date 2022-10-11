#include "syscall.h"

int main()
{
    int num;
    num = RandomNum();
    
    PrintNum(num);
    Halt();
}