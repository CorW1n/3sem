#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxTokensCount 100
#define MaxStringLength 100

void Split(char* s, char* del, char*** tokens, int* count);
void MyScanf(char **s);

int main() {
	int count = 0, i = 0;	
	char *s = malloc(sizeof(char) * MaxStringLength);
	MyScanf(&s);
	char del[] = " \t,.!?";
	char** tokens = malloc(sizeof(char*) * MaxTokensCount);
	for (i = 0; i < MaxStringLength; i++) 
	{
		tokens[i] = malloc(MaxStringLength * sizeof(char));
	}
	Split(s, del, &tokens, &count);
	for (i = 0; i < count; i++)
	{
		printf("%s\n", tokens[i]);
	}
	for (i = 0; i < MaxTokensCount; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
	free(s);
	return 0;
}
void Split(char* s, char* del, char*** tokens, int* count) {
	char* token = strtok(s, del);
	while (token != NULL)
	{		
		strcpy( (*tokens)[*count], token);
		(*count)++;
		token = strtok(NULL, del);
	}
}

void MyScanf(char **s)
{
	int j = 0, c;
	while ((c = getchar()) != '\n')
	{
		(*s)[j] = c;
		j++;
	}
	s[j + 1] = '\0';
}
