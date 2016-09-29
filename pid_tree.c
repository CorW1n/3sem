#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define N 4


int main()
{
	int i = 0, status;
	for (i; i < N; i++)
	{
		pid_t pid = fork();
		if (pid > 0)
		{
			printf("%d %d %d\n", i, getpid(), getppid());
			exit(1);
		}
		wait(&status);
	}
	return 0;	
}
