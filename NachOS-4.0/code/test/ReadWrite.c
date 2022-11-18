#include "syscall.h"

#define MODE_READWRITE 0
#define MODE_READ 1

#define stdin 0
#define stdout 1

int main() {
    
    int i;
    int write;
    char buffer[100];
    int fileid;
    int read;
    int len = 0;

    PrintString("Open file text1.txt \n");
    fileid = Open("test1.txt", MODE_READ);
    read = Read(buffer, 50, fileid);
    while (buffer[len] != '\0') ++len;
    PrintString("Read ");
    PrintNum(len);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);

    PrintString("Open file test2.txt \n");
    fileid = Open("test2.txt", MODE_READWRITE);
    write = Write(buffer, len, fileid);

    PrintString("Write ");
    PrintNum(write);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);

    PrintString("Enter a string:\n");
    
    Read(buffer, 50, stdin);
    len = 0;
    while (buffer[len] != '\0') ++len;
    PrintString("You have entered: ");
    Write(buffer, len, stdout);
    PrintString("\n");

    Halt();
}