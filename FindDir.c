#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int i = 0;
void Find(char* path, int depth, char* fileName)
{
	if(depth <= 0)
		return;
	struct stat buf;
	DIR* d = opendir(path);
	struct dirent *dir;
	while(1)
	{
		dir = readdir(d);
		if (dir != NULL)
		{
      /*
       * FIXIT:
       * Мы же обсуждали с вами в самом конце семирара, что передаёте в stat неверный первый аргумент.
       * Вы передаете только имя, а нужно путь до этого файла и директории тоже указывать.
       */
			stat(dir->d_name, &buf);
			if (dir->d_type == 4)
			{
					if((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0))
					{	
						/*
             * FIXIT:
             * Нужно завести отдельную константу для 1000.
             */
						char s[1000];
						strcpy(s, path);
						strcat(s, "/");
						strcat(s, dir->d_name);
						Find(s, depth - 1, fileName);
					}
			}
			else
			{
				if(!strcmp(dir->d_name, fileName))
				{
					printf("%s/%s\n", path, dir->d_name);
				}
			}	
		}
		else
		{
			break;
		}
	}
	closedir(d);
	return;
}

int main(int argc, char **argv)
{
	Find("..", 2, "wiper.txt");
	return 0;
}

