#include "syscall.h"

int main(){
    int fd, type;
    int len;
    char buffer[100];

    PrintString("Open read write testReadWrite.txt\n");
    fd = Open("testReadWrite.txt", 0);

    // test read write console
    PrintString("Enter a text to write to opened file: ");
    len = Read(buffer, 10, 0);
    PrintString("The entered text is: ");
    Write(buffer, len, 1);

    // write the entered text to file
    Write(buffer, len, fd);

    Close(fd);
    PrintString("\nClosed testReadWrite.txt\n");

    Halt();
    return 0;
}