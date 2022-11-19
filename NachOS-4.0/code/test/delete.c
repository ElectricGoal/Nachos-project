#include "syscall.h"
#define MAX_LENGTH 255

int main() {
    char fileName[MAX_LENGTH];
    // int length;

    // PrintString("Enter file's name's length: ");
    // length = ReadNum();
    PrintString("Enter file's name: ");
    ReadString(fileName, MAX_LENGTH);

    if (RemoveFile(fileName) == 0) {
        PrintString("File ");
        PrintString(fileName);
        PrintString(" deleted successfully!\n");
    } else
        PrintString("Delete file failed\n");

    Halt();
}