#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define N 100

int main()
{
	char buff[Т];
	int bytesRead;
	char     *array;
	int     shmid;
	int     new = 1;
	const char pathname[] = "s06e01a.c";
	key_t   key;

	if((key = ftok(pathname , 0)) < 0)
	{
		printf("Can\'t generate key\n");
		exit(-1);
	}

	if((shmid = shmget(key, 10000, 0666 | IPC_CREAT | IPC_EXCL)) < 0)
	{    
		if(errno != EEXIST)
		{         
			printf("Can't create shared memory\n");
        		exit(-1);
		}
		else
		{

         	if((shmid = shmget(key, 10000, 0)) < 0)
		{
			printf("Can't find shared memory\n");
			exit(-1);
		}
		new = 0;
		}
	}

	if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1))
	{
		printf("Can't attach shared memory\n");
		exit(-1);
	}
	int f = open("input.txt", O_RDONLY, 1);
	while((bytesRead = read(f, buff, 10)) > 0)
		 strcat(array,buff);
	
	return 0;
}
