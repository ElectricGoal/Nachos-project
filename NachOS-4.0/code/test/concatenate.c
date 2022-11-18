#include "syscall.h"
#define MAX_LENGTH 255

char *strcat(char *s1, const char *s2) {
  char *s = s1;

  while (*s1)
    s1++;

  while (*s1++ = *s2++)
    ;
  return s;
}

int main() {
    char fileName1[MAX_LENGTH];
    char fileName2[MAX_LENGTH];
    OpenFileID fileId1;
    OpenFileID fileId2;
    // int length;

    // PrintString("Enter file's name's length: ");
    // length = ReadNum();
    PrintString("Enter first file's name: ");
    ReadString(fileName1, MAX_LENGTH);

    PrintString("Enter second file's name: ");
    ReadString(fileName2, MAX_LENGTH);


    Halt();
}