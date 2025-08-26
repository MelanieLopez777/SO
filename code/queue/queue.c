#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

void initialize(StaticQueue *queue)
{
	queue->front = 0;
	queue->rear = MAX_QUEUE_SIZE - 1;
}

bool isEmpty(StaticQueue *queue)
{
	if(queue->front == queue->rear + 1 || (queue->front == 0 && queue->rear == MAX_QUEUE_SIZE - 1))
	{
		return true;
	}

	return false;
}

bool isFull(StaticQueue *queue)
{
	if(queue->front == queue->rear + 2 || 
	   (queue->front == 0 && queue->rear == MAX_QUEUE_SIZE - 2) ||
	   (queue->front == 1 && queue->rear == MAX_QUEUE_SIZE - 1))
	{
		return true;
	}

	return false;
}

void enqueue(StaticQueue *queue, dataType element)
{
	if(isFull(queue))
	{
		printf("[!] Error: Queue is full, can not add value '%d'\n", element);
		return;
	}

	queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
	queue->data[queue->rear] = element;

}

void dequeue(StaticQueue *queue)
{
	if(isEmpty(queue))
	{
		printf("[!] Error: Queue is empty\n");
		return;
	}

	queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
}

dataType front(StaticQueue *queue)
{
	if(isEmpty(queue))
	{
		printf("[!] Error: Queue is empty, cannot take any element\n");
	}

	return queue->data[queue->front];
}

char* queueStr(StaticQueue *queue)
{
    static char buffer[2000];
    char temp[15];
    int current_index;
    int len = 0;

    buffer[0] = '\0';

    if (isEmpty(queue)) {
        strcat(buffer, "Queue: [ Empty ]\n");
        return buffer;
    }

    strcat(buffer, "Queue: [");
    len = strlen(buffer);
    current_index = queue->front;
    while (true) {
        sprintf(temp, "%d", queue->data[current_index]);

        if (len + strlen(temp) + 3 >= sizeof(buffer)) {
            strcat(buffer, "...");
            break;
        }

        strcat(buffer, temp);
        len += strlen(temp);

        if (current_index == queue->rear) {
            break;
        } else {
            strcat(buffer, ", ");
            len += 2;
        }

        current_index = (current_index + 1) % MAX_QUEUE_SIZE;
    }
    strcat(buffer, "]\n");

    return buffer;
}