#include <stdio.h>

int a[5][5] = { 	
					{0, 1, 1, 1, 0},
					{0, 0, 0, 0, 1},
					{0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0} };
int n = 5;


void DFS(int k)
{
	int i;
	printf("%d\n", k);
	for(i = 0; i < n; i++)
		if(a[k-1][i] == 1)
			DFS(i+1);
	return;
}

int main(int argc, char **argv)
{
	DFS(1);
	return 0;
}

