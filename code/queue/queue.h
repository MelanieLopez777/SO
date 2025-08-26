#include <stdio.h>
#include <stdbool.h>
#include "../structures.h"

#define MAX_QUEUE_SIZE 16

typedef proceso dataType;

typedef struct 
{
    dataType data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} StaticQueue;

void initialize(StaticQueue *queue);
bool isEmpty(StaticQueue *queue);
bool isFull(StaticQueue *queue);
void enqueue(StaticQueue *queue, dataType element);
void dequeue(StaticQueue *queue);
dataType front(StaticQueue *queue);
char* queueStr(StaticQueue *queue);