#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define N 4

/*
 * Вы не полностью разобрались в создании дочерних процессов, видимо, и том, как родительский процесс может дожидаться дочернего.
 * Запустите несколько раз свою программу, и вы убедитесь, что не каждый раз процессы образуют цепочку.
 * 
 * Программа работает неверно.
 */
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
