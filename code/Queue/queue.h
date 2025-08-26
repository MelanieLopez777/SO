#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "../Structure/structures.h"

constexpr int MAX_QUEUE_SIZE = 16;
using dataType = Proceso;

class StaticQueue {
private:
    int front;
    int rear;
    dataType data[MAX_QUEUE_SIZE];

public:
    StaticQueue();

    void initialize();
    bool isEmpty() const;
    bool isFull() const;

    void enqueue(dataType element);
    void dequeue();
    dataType getFront() const;

    std::string toString() const;
};

#endif // QUEUE_H
