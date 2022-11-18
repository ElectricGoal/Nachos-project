#include "syscall.h"
#define MAX_LENGTH 255

#define MODE_READWRITE 0
#define MODE_READ 1

#define stdin 0
#define stdout 1


char *strcat(char *s1, const char *s2) {
  char *s = s1;

  while (*s1)
    s1++;

  while (*s1++ = *s2++)
    ;
  return s;
}

int main() {
    int i;
    int write;
    char buffer[100];
    //int fileid;
    int read1;
    int read2;
    int len1 = 0;
    int len2 = 0;
    char fileName1[MAX_LENGTH];
    char fileName2[MAX_LENGTH];
    int fileId1;
    int fileId2;
    // int length;

    // PrintString("Enter file's name's length: ");
    // length = ReadNum();
    PrintString("Enter first file's name: ");
    ReadString(fileName1, MAX_LENGTH);

    PrintString("Enter second file's name: ");
    ReadString(fileName2, MAX_LENGTH);
    
    PrintString("Open first file \n");
    fileId1 = Open(fileName1, MODE_READ);
    read1 = Read(buffer, 50, fileId1);
    while (buffer[len1] != '\0') ++len1;
    PrintString("Read ");
    PrintNum(len1);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileId1);
    char buffer1[100]=buffer;

    PrintString("Open second file \n");
    fileId2 = Open(fileName2, MODE_READWRITE);
    read2 = Read(buffer, 50, stdin);
    len2 = 0;
    while (buffer[len2] != '\0') ++len2;
    PrintString("Read ");
    PrintNum(len2);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileId2);


    //write = Write(buffer, len2, fileId2);

    //PrintString("Write ");
    //PrintNum(write);
    //PrintString(" characters: ");
    //PrintString(buffer);
    //PrintString("\n");
    //Write(buffer, len2, stdout);
    //PrintString("Enter a string:\n");
        //PrintString("You have entered: ");
    

    Halt();
}