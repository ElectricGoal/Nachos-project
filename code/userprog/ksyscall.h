/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include "kernel.h"
#include "synchconsole.h"
#include "filesys.h"

/*  Input:  - User space address (int)
            - Limit of buffer (int)
    Output: - Buffer (char*)
    Purpose: Copy buffer from User memory space to System memory space */
char *User2System(int virtAddr, int limit)
{
  int i; // index
  int oneChar;
  char *kernelBuf = new char[limit + 1]; // need for terminal string

  if (kernelBuf == NULL)
    return kernelBuf;

  memset(kernelBuf, 0, limit + 1);

  for (i = 0; i < limit; i++)
  {
    kernel->machine->ReadMem(virtAddr + i, 1, &oneChar);
    kernelBuf[i] = (char)oneChar;
    if (oneChar == 0)
      break;
  }

  return kernelBuf;
}

/*  Input:  - User space address (int)
            - Limit of buffer (int)
            - Buffer (char[])
    Output: - Number of bytes copied (int)
    Purpose: Copy buffer from System memory space to User memory space */
int System2User(int virtAddr, int len, char *buffer)
{
  if (len < 0)
    return -1;

  if (len == 0)
    return len;

  int i = 0;
  int oneChar = 0;

  do
  {
    oneChar = (int)buffer[i];
    kernel->machine->WriteMem(virtAddr + i, 1, oneChar);
    i++;
  } while (i < len && oneChar != 0);

  return i;
}

void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

/*	Input: int value
  Output: None
  Purpose: Print an int number to console */
void SysPrintNum(int number)
{
  // in case the input is 0
  if (number == 0)
  {
    // print '0' to the console and return
    kernel->synchConsoleOut->PutChar('0');
    return;
  }

  // in case the input is a negative number, print minus sign to console
  if (number < 0)
  {
    kernel->synchConsoleOut->PutChar('-');
  }

  int digitCount = 0; // stores number of digits
  int digits[10];     // array stores each digit
                      // (int type has up to 10 digits: -2,147,483,648 -> 2,147,483,647)

  // store each digit from right to left to the digits array and count the number of digits
  // if number is a negative number, each digit will have a minus sign
  int numberCopy = number;
  while (numberCopy != 0)
  {
    digits[digitCount] = numberCopy % 10;
    numberCopy /= 10;
    digitCount++;
  }

  // print digits array to console in reverse order
  if (number > 0)
  {
    for (int i = 0; i < digitCount; i++)
    {
      // (0 -> 9) + '0' = ('0' -> '9')
      kernel->synchConsoleOut->PutChar(digits[digitCount - 1 - i] + '0');
    }
  }
  else
  {
    for (int i = 0; i < digitCount; i++)
    {
      // -(0 -> -9) + '0' = ('0' -> '9')
      kernel->synchConsoleOut->PutChar(-digits[digitCount - 1 - i] + '0');
    }
  }
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
