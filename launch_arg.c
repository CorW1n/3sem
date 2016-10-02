#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 * Совсем неверный подход к решению.
 * Никто не гарантирует, что у вас число аргументов при запуске будет не больше двух.
 * Мы специально писали ф-ю Split, которая строку разбила бы на отдельные токены, количество которых может быть произвольным.
 */
int main()
{
	FILE *file = fopen("input.txt", "r"); 
	int countLines = 0, seconds = 0, status; 
/*
 * магических чисел вроде 10 быть не должно. объявляйте константы.
 */
	char s1[10], s2[10], s3[10], s4[10]; 

	fscanf(file, "%s", s1); 
	fscanf(file, "%s ", s2); 
	fscanf(file, "%s ", s3); 
	fscanf(file, "%s", s4);
	countLines = atoi(s1);
	seconds = atoi(s4);
	pid_t pid1 = fork(); 
/*
 * Непонятна цель этого wait
 */
	wait(&status); 
	if (pid1 == 0) 
	{ 
		sleep(seconds); 
		execlp(s2, s2, s3, NULL); 
	}

  /*
   * ваш код написан для одно конкретного файла запуска. в общем случае работать не будет.
   */
	fscanf(file, "%s ", s1); 
	fscanf(file, "%s", s2);
	seconds = atoi(s2);
	pid_t pid2 = fork(); 
	wait(&status); 
	if (pid2 == 0) 
	{ 
		sleep(seconds); 
		execlp(s1, s1, NULL); 
	}
	fscanf(file, "%s ", s1);
	fscanf(file, "%s ", s2);
	fscanf(file, "%s ", s3);
	fscanf(file, "%s", s4);
	seconds = atoi(s4);
	strcat(s2, s3);
	pid_t pid3 = fork();
	wait(&status);
	if (pid3 == 0)
	{
		sleep(seconds);
		execlp(s1, s1, s2, NULL);
	}
	
	fclose(file);
	 
	return 0;	
}
