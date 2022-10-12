#include "syscall.h"

int main()
{
    char ch;

    PrintString("Enter a character: ");
    ch = ReadChar();

    PrintString("You have entered: ");
    PrintChar(ch);
    PrintChar('\n');
    
    Halt();
}