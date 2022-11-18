#include "syscall.h"
#define MAX_LENGTH 32

int main()
{
	char buffer[100];
	int openFileId;
	int fileSize;
	char c; // Ky tu de in ra
	char fileName[MAX_LENGTH];
	int i; // Index for loop

	PrintString("Nhap vao ten file can doc: ");

	// Goi ham ReadString de doc vao ten file
	ReadString(fileName, MAX_LENGTH);
	openFileId = Open(fileName, 1); // Goi ham Open de mo file

	if (openFileId != -1) // Kiem tra Open co loi khong
	{
		int read = Read(buffer, 50, openFileId);
		int len = 0;
		while (buffer[len] != '\0')
			++len;
		PrintString("Read ");
		PrintNum(len);
		PrintString(" characters: ");
		PrintString(buffer);
		PrintString("\n");
		Close(openFileId);
	}
	else
	{
		PrintString(" -> Mo file khong thanh cong!!\n\n");
	}

	Halt();
}