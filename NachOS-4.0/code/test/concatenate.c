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
    int write;
    char buffer1[100];
    char buffer2[100];
    char* buffer;
    int fileid;
    int fileid1;
    int fileid2;
    int read1;
    int read2;
    int len = 0;
    int len1 = 0;
    int len2 = 0;
    char fileName1[MAX_LENGTH];
    char fileName2[MAX_LENGTH];
    char fileName3[MAX_LENGTH];

    PrintString("Enter first file's name: ");
    ReadString(fileName1, MAX_LENGTH);
    PrintString("Open first file \n");
    fileid1 = Open(fileName1, MODE_READ);
    read1 = Read(buffer1, 50, fileid1);
    while (buffer1[len1] != '\0') ++len1;
    PrintString("Read ");
    PrintNum(len1);
    PrintString(" characters: ");
    PrintString(buffer1);
    PrintString("\n");
    Close(fileid1);

    PrintString("Enter second file's name: ");
    ReadString(fileName2, MAX_LENGTH);
    PrintString("Open second file \n");
    fileid2 = Open(fileName2, MODE_READ);
    read2 = Read(buffer2, 50, fileid2);
    while (buffer2[len2] != '\0') ++len2;
    PrintString("Read ");
    PrintNum(len2);
    PrintString(" characters: ");
    PrintString(buffer2);
    PrintString("\n");
    Close(fileid2);

    PrintString("Enter result concatenate file's name: ");
    ReadString(fileName3, MAX_LENGTH);
    if (CreateFile(fileName3) == 0) {
        PrintString(fileName3);
        PrintString(" created successfully!\n");
    } else 
    {
      PrintString("Failed to create ");
      PrintString(fileName3);
      PrintString("\n");
    } 
    

    
    
    
    len=len1+len2;
    buffer=strcat(buffer1,buffer2);
    fileid = Open(fileName3, 0);
    write = Write(buffer, len, fileid);
    PrintString("Write to ");
    PrintNum(write);
    PrintString(" characters to ");
    PrintString(fileName3);
    PrintString(" : ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);
    

    Halt();
}