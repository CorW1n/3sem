#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define LengthName 32
#define UserMaxCount 15
#define LengthMes 1000

struct User
{
	int ip;
	int port;
	char* nick;
}; 

char message[LengthMes];
char *text;
struct User users[UserMaxCount];
int sockfd;
struct sockaddr_in servaddr, cliaddr;
int clilen;

void SendMessage(int currentUser, int i)
{
	strcat(message, users[currentUser].nick);
	strcat(message, ": ");
	strcat(message, text);
	printf("Post pigeon with the message: %s is flying to %s with an IP %d and a port %d, good luck\n", text, users[i].nick, users[i].ip, users[i].port);
	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = users[i].port;
	cliaddr.sin_addr.s_addr = users[i].ip;
	if (sendto(sockfd, message, strlen(message) + 1, 0, (struct sockaddr*)&cliaddr, clilen) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(1);
	}
	bzero(&message, strlen(message));
}

int main()
{
	char* directNick = malloc(LengthName * sizeof(char));
	text = malloc(LengthMes * sizeof(char));
	int n, i = 0, j = 0;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(51000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror(NULL);
		exit(1);
	}
	else
	{
		printf("Sock fd:%d\n", sockfd);
	}

	if (bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(1);
	}

	int userCount = 0;
	int currentUser;
	clilen = sizeof(cliaddr);
	while (1)
	{
		bzero(text, LengthMes);
		if ((n = recvfrom(sockfd, text, 999, 0, (struct sockaddr*)&cliaddr, &clilen)) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(1);
		}
		currentUser = -1;
		
		for(i = 0; i < userCount; i++)
		{
			if((cliaddr.sin_port == users[i].port) && (cliaddr.sin_addr.s_addr == users[i].ip))
				currentUser = i;
		}
		if(currentUser < 0)
		{
			users[userCount].nick = malloc(LengthName * sizeof(char));
			strcpy(users[userCount].nick, text);
			users[userCount].port = cliaddr.sin_port; 
			users[userCount].ip = cliaddr.sin_addr.s_addr;
			printf("Champion %s has come with an IP %d and a port %d, greetings!\n", users[userCount].nick, users[userCount].ip, users[userCount].port);
			userCount++;
		}
		else 
			if (text[0] == '$')
			{
				directNick = strtok(text, "$");
				text = strtok(NULL, "$");
				for (j = 0; j < userCount; j++)
				{
					if (!strcmp(directNick, users[j].nick))
					{
						SendMessage(currentUser, j);
					}
				}
			}
			else 
			{
				for(i = 0; i < userCount; i++)
				{
					if(i != currentUser)
					{
						SendMessage(currentUser, i);
					}
				}
			}
		}
	return 0;
}
