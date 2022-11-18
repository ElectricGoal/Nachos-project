#include "syscall.h"

#define MODE_READWRITE 0
#define MODE_READ 1

#define MAX_LENGTH 32

int main() {
    char buffer[100];
    int i;
    int read;
    int write;
    int fileid;
    int len;

    char fileRead[MAX_LENGTH];
    char fileWrite[MAX_LENGTH];

    PrintString("Nhap vao ten file nguon: ");
	ReadString(fileRead, MAX_LENGTH);

    PrintString("Nhap vao ten file dich: ");
	ReadString(fileWrite, MAX_LENGTH);

    fileid = Open(fileRead, 1);
    read = Read(buffer, 50, fileid);
    len = 0;
    while (buffer[len] != '\0') ++len;
    PrintString("Read ");
    PrintNum(len);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);

    fileid = Open(fileWrite, 0);
    write = Write(buffer, len, fileid);

    PrintString("Write ");
    PrintNum(write);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);

    Halt();
}