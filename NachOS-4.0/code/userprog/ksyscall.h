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

void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

/*  Input:   None
    Output:  int value
    Purpose: Read an int number from console */
int SysReadNum()
{
  char c;
  int res = 0;
  int sign = 1;
  bool isValid = true;

  // skip blank space and LF character
  c = kernel->synchConsoleIn->GetChar();
  while (c == ' ' || c == '\n')
    c = kernel->synchConsoleIn->GetChar();

  if (c == '-') // check negative
  {
    sign = -1;
    c = kernel->synchConsoleIn->GetChar();
  }

  while (c != ' ' && c != '\n')
  {
    if (isValid) // if number is valid
    {
      if (c >= '0' && c <= '9')
      {
        res *= 10;
        res += sign * (c - '0');
        if ((sign > 0 && res < 0) || (sign < 0 && res > 0)) // overflow
          isValid = false;
      }
      else
        isValid = false;
    }
    c = kernel->synchConsoleIn->GetChar();
  }

  if (isValid)
    return res;
  return 0;
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

/* Read a character from console */
char SysReadChar()
{
  return kernel->synchConsoleIn->GetChar();
}

/* Print a character to console */
void SysPrintChar(char character)
{
  kernel->synchConsoleOut->PutChar(character);
}

/* Random a number */
int SysRandomNum()
{
  RandomInit((int)time(NULL));
  return RandomNumber();
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
