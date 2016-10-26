#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int semid;

void SemFunc(int n, int semnum, int semid)
{
	struct sembuf mybuf;
	mybuf.sem_op = n;
	mybuf.sem_flg = 0;
	mybuf.sem_num = semnum;
	if (n < 0)
	{
		printf("try to lock sem%d\n", semnum + 1);
		semop(semid, &mybuf, 1);
		printf("sem%d is locked\n", semnum + 1);
	}
	else
	{
		semop(semid, &mybuf, 1);
	}
}


void *mythread1(void *dummy)
{
	while(1)
	{
		SemFunc(-1, 1, semid);
		SemFunc(-1, 0, semid);
		SemFunc(1, 1, semid);
		SemFunc(1, 0, semid);
	}
	return NULL;
}

void *mythread2()
{
	while(1)
	{
		SemFunc(-1, 1, semid);
		SemFunc(-1, 0, semid);
		SemFunc(1, 1, semid);
		SemFunc(1, 0, semid);
	}
	return NULL;
}

int main()
{
	pthread_t thid, mythid; 
	int result, status;
	const char pathname[] = "sem_key.c";
	key_t key;
	struct sembuf mybuf;
	key = ftok(pathname, 0);
	semid = semget(key, 2, 0666 | IPC_CREAT);
	SemFunc(1, 1, semid);
	SemFunc(1, 0, semid);

	result = pthread_create( &thid, (pthread_attr_t *)NULL, mythread1, NULL);

	mythread2();

	pthread_join(thid, (void **)NULL);
	semctl(semid, IPC_RMID, NULL);
	return 0;
}
