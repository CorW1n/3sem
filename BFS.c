#include <stdio.h>

#define MAX_QUEUE_SIZE 100

int a[5][5] = { 	
					{0, 1, 1, 1, 0},
					{0, 0, 0, 0, 1},
					{0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0} };
int n = 5;
struct Queue
{
    int head;
    int tail;
    int data[MAX_QUEUE_SIZE];
}my_queue;

void Push(struct Queue* queue, int element) 
{
	queue->tail++;
	queue->data[queue->tail] = element;
	return;
}
void Pop(struct Queue* queue) 
{
	queue->data[queue->head] = 0;
	queue->head++;
	return;
}
int Front(struct Queue* queue) // возвращает элемент из головы очереди
{
	return(queue->data[queue->head + 1]);
}
int Back(struct Queue* queue) // -//- хвоста очереди
{
	return(queue->data[queue->tail]);
}
int IsEmpty(struct Queue* queue)
{
	if(queue->tail == queue->head)
		return 1;
	else
		return 0;
}

int main(int argc, char **argv)
{
	int dir, i;
	Push(&my_queue, 0);
	while(!IsEmpty(&my_queue))
	{
		dir = Front(&my_queue);
		Pop(&my_queue);
		printf("%d\n", dir+1);
		for(i = n; i >= 0 ; i--)
			if(a[dir][i] == 1)
				Push(&my_queue, i);
	}
	return 0;
}

