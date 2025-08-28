#include "queue.h"

StaticQueue::StaticQueue() {
    initialize();
}

void StaticQueue::initialize() {
    front = 0;
    rear = MAX_QUEUE_SIZE - 1;
}

bool StaticQueue::isEmpty() const {
    return (front == rear + 1) || (front == 0 && rear == MAX_QUEUE_SIZE - 1);
}

bool StaticQueue::isFull() const {
    return (front == rear + 2) ||
           (front == 0 && rear == MAX_QUEUE_SIZE - 2) ||
           (front == 1 && rear == MAX_QUEUE_SIZE - 1);
}

void StaticQueue::enqueue(dataType* element) {
    if (isFull()) {
        std::cerr << "";
        return;
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = element;
}


void StaticQueue::dequeue() {
    if (isEmpty()) {
        std::cerr << "";
        return;
    }
    front = (front + 1) % MAX_QUEUE_SIZE;
}

dataType* StaticQueue::getFront() const {
    if (isEmpty()) {
        throw std::runtime_error("[!] Error: Queue is empty, cannot take any element");
    }
    return data[front];
}


std::string StaticQueue::toString(int etapa) const {
    std::ostringstream oss;

    if (isEmpty()) {
        oss << "";
        return oss.str();
    }


    int current_index = front;
    bool first = true;

    while (true) {
        if (!first) {
            oss << "\n ";
        }
        oss << data[current_index]->toString(etapa);
        first = false;

        if (current_index == rear) {
            break;
        }

        current_index = (current_index + 1) % MAX_QUEUE_SIZE;
    }
    return oss.str();
}
