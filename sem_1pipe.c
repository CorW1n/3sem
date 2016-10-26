#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void SemFunc(int n, int semnum, int semid)
{
	struct sembuf mybuf;
	mybuf.sem_op = n;
	mybuf.sem_flg = 0;
	mybuf.sem_num = semnum;
	semop(semid , &mybuf , 1);
}

int main()
{
	int semid;
	int i = 0, status, a = 1, b = 2, answer;
	int fd[2];
	pipe(fd);
	const char pathname[] = "sem_key.c";
	key_t key;
	struct sembuf mybuf;
	key = ftok(pathname, 0);
	semid = semget(key, 2, 0666 | IPC_CREAT);
	SemFunc(1, 1, semid);
	pid_t pid = fork();
	if (pid > 0)
	{
		while(1)		
		{
						
			write(fd[1], &a, sizeof(int));
			write(fd[1], &b, sizeof(int));
			SemFunc(-1, 0, semid);
			read(fd[0], &answer, sizeof(int));
			SemFunc(1, 1, semid);
			printf("%d\n", answer);
		}	
	}
	if (pid == 0)
	{
		while(1)
		{	
			SemFunc(-1, 1, semid);
			read(fd[0], &a, sizeof(int));
			read(fd[0], &b, sizeof(int));
			answer = a + b;
			write(fd[1], &answer, sizeof(int));
			SemFunc(1, 0, semid);
		}
	}


	semctl(semid, IPC_RMID, NULL);
	return 0;
}
