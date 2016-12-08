#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#define Length 100
#define GiveBitS SIGINT
#define GetBit0 SIGUSR1
#define GetBit1 SIGUSR2
#define Byte 8

int bitCount = 0, lenght;
char message[] = "May the Force be with you";
char text[Length];
pid_t ppid;

void GiveBit()
{
	char bit;
	int symbolCount = bitCount / Byte;
	int pointer = bitCount % Byte;

	bit = message[symbolCount] & (1 << pointer);
	bitCount++;
	if(bit)
	{
		kill(ppid, GetBit1);
	}
	else
	{
		kill(ppid, GetBit0);
	}
	if (symbolCount == lenght)
	exit(0);
}

void GetBit(int signal)
{
	int symbolCount = bitCount / Byte;
	int pointer = bitCount % Byte;

	if (signal == GetBit1)
		text[symbolCount] = text[symbolCount] | (1 << pointer);

	bitCount++;
	kill(ppid, GiveBitS);

	if ((bitCount % Byte) == 0)
	{
		printf("%c\n", text[symbolCount]);
		sleep(1);
	}

}


int main()
{
	lenght = strlen(message);

	signal(GetBit0, GetBit);
	signal(GetBit1, GetBit);
	signal(GiveBitS, GiveBit);

	ppid = getpid();
	pid_t pid = fork();

	if (pid != 0)
	{
		ppid = pid;
		GiveBit();
	}

	while(1)
	{
	}

return 0;
}
