// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------
void move_program_counter()
{
	/* set previous programm counter (debugging only)
	 * similar to: registers[PrevPCReg] = registers[PCReg];*/
	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	/* set programm counter to next instruction
	 * similar to: registers[PCReg] = registers[NextPCReg]*/
	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(NextPCReg));

	/* set next programm counter for brach execution
	 * similar to: registers[NextPCReg] = pcAfter;*/
	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(NextPCReg) + 4);
}

void ExceptionHandler(ExceptionType which)
{
    int type = kernel->machine->ReadRegister(2);
    DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

    switch (which)
    {
    case NoException: // return control to kernel
		kernel->interrupt->setStatus(SystemMode);
		DEBUG(dbgSys, "Switch to system mode\n");
		break;
	case PageFaultException:
	case ReadOnlyException:
	case BusErrorException:
	case AddressErrorException:
	case OverflowException:
	case IllegalInstrException:
	case NumExceptionTypes:
		cerr << "Error " << which << " occurs\n";
		SysHalt();
		ASSERTNOTREACHED();

    case SyscallException:
        switch (type)
        {
        case SC_Halt:
        {
            DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

            SysHalt();

            ASSERTNOTREACHED();
            break;
        }
        case SC_Add:
        {
            DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

            /* Process SysAdd Systemcall*/
            int result;
            result = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
                            /* int op2 */ (int)kernel->machine->ReadRegister(5));

            DEBUG(dbgSys, "Add returning with " << result << "\n");
            /* Prepare Result */
            kernel->machine->WriteRegister(2, (int)result);

            return move_program_counter();

            return;
            ASSERTNOTREACHED();
            break;
        }
        case SC_ReadNum:
			DEBUG(dbgSys, "Read number\n");

			int res;
			res = SysReadNum();

			DEBUG(dbgSys, "SysReadNum returning with " << res << "\n");
			/* Prepare Result */
			kernel->machine->WriteRegister(2, (int)res);

			return move_program_counter();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_PrintNum:
			DEBUG(dbgSys, "PrintNum " << kernel->machine->ReadRegister(4) << "\n");
			SysPrintNum((int)kernel->machine->ReadRegister(4));

			return move_program_counter();

			return;
			ASSERTNOTREACHED();
			break;

		case SC_ReadChar:
		{
			DEBUG(dbgSys, "Read character \n");

			char result;
			result = SysReadChar();

			DEBUG(dbgSys, "ReadChar returning with " << result << "\n");
			kernel->machine->WriteRegister(2, (int)result);

			return move_program_counter();

			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_PrintChar:
		{
			DEBUG(dbgSys, "PrintChar returning with " << kernel->machine->ReadRegister(4) << "\n");
			SysPrintChar(kernel->machine->ReadRegister(4));

			return move_program_counter();

			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_RandomNum:
		{
			DEBUG(dbgSys, "Random number \n");

			int result;
			result = SysRandomNum();

            DEBUG(dbgSys, "RandomNumber returning with " << result << "\n");
            /* Prepare Result */
            kernel->machine->WriteRegister(2, (int)result);

            return move_program_counter();

            return;
            ASSERTNOTREACHED();
            break;
        }

        case SC_ReadString:
        {
            DEBUG(dbgSys, "Read string\n");
            SysReadString((char *)kernel->machine->ReadRegister(4), (int)kernel->machine->ReadRegister(5));

            /* Modify return point */
            {
                /* set previous programm counter (debugging only)*/
                kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

                /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
                kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

                /* set next programm counter for brach execution */
                kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
            }

            return;
            ASSERTNOTREACHED();
            break;
        }

        case SC_PrintString:
        {
            DEBUG(dbgSys, "PrintString " << kernel->machine->ReadRegister(4) << "\n");
            SysPrintString((int)kernel->machine->ReadRegister(4));

            /* Modify return point */
            {
                /* set previous programm counter (debugging only)*/
                kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

                /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
                kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

                /* set next programm counter for brach execution */
                kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
            }

            return;

            ASSERTNOTREACHED();

            break;
        }
        case SC_CreateFile:
        {
            DEBUG(dbgSys, "Create file\n");
            int result = SysCreateFile((int)kernel->machine->ReadRegister(4));

            DEBUG(dbgSys, "SysCreateFile returning with " << result << "\n");
            kernel->machine->WriteRegister(2, (int)result);

            return move_program_counter();

            return;
            ASSERTNOTREACHED();
            break;
        }
        case SC_Open:
        {
            int virtAddr = kernel->machine->ReadRegister(4);
            int type = kernel->machine->ReadRegister(5);

            kernel->machine->WriteRegister(2, SysOpen(virtAddr, type));

            return move_program_counter();

		}
		case SC_RemoveFile:
		{
			int virtAddr = kernel->machine->ReadRegister(4);
			int result=SysRemoveFile(virtAddr);
			DEBUG(dbgSys, "SysRemoveFile returning with " << result << "\n");
            kernel->machine->WriteRegister(2, (int)result);

            return move_program_counter();
			return;
            ASSERTNOTREACHED();
            break;
		}

        case SC_Close:
        {
            int id = kernel->machine->ReadRegister(4);
            kernel->machine->WriteRegister(2, SysClose(id));

           return move_program_counter();

            return;
            ASSERTNOTREACHED();
            break;
        }

        case SC_Read:
        {
            DEBUG(dbgSys, "Read file\n");
            int result;
            result = SysRead(kernel->machine->ReadRegister(4), (int)kernel->machine->ReadRegister(5), (int)kernel->machine->ReadRegister(6));

            DEBUG(dbgSys, "Read file returning with " << result << "\n");
            /* Prepare Result */
            kernel->machine->WriteRegister(2, (int)result);

            /* Modify return point */
            {
                /* set previous programm counter (debugging only)*/
                kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

                /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
                kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

                /* set next programm counter for brach execution */
                kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
            }

            return;
            ASSERTNOTREACHED();
            break;
        }

        case SC_Write:
        {
            DEBUG(dbgSys, "Write file\n");
            int result;
            result = SysWrite(kernel->machine->ReadRegister(4), (int)kernel->machine->ReadRegister(5), (int)kernel->machine->ReadRegister(6));

            DEBUG(dbgSys, "Write file returning with " << result << "\n");
            /* Prepare Result */
            kernel->machine->WriteRegister(2, (int)result);

            /* Modify return point */
            {
                /* set previous programm counter (debugging only)*/
                kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

                /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
                kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

                /* set next programm counter for brach execution */
                kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
            }

            return;
            ASSERTNOTREACHED();
            break;
        }
        case SC_Seek:
        {
            DEBUG(dbgSys, "Seek file\n");
            int result;
            result = SysSeek((int)kernel->machine->ReadRegister(4), (int)kernel->machine->ReadRegister(5));

            DEBUG(dbgSys, "Seek file returning with " << result << "\n");
            /* Prepare Result */
            kernel->machine->WriteRegister(2, (int)result);

            /* Modify return point */
            {
                /* set previous programm counter (debugging only)*/
                kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

                /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
                kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

                /* set next programm counter for brach execution */
                kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
            }

            return;
            ASSERTNOTREACHED();
            break;
        }
        default:
            cerr << "Unexpected system call " << type << "\n";
            break;
        }
        break;

    default:
        cerr << "Unexpected user mode exception" << (int)which << "\n";
        break;
    }
    ASSERTNOTREACHED();
}
