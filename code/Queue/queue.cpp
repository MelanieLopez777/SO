#include "queue.h"

StaticQueue::StaticQueue() {
    initialize();
}

void StaticQueue::initialize() {
    front = 0;
    rear = MAX_QUEUE_SIZE - 1;
    count = 0;   
}

bool StaticQueue::isEmpty() const {
    return count == 0;
}

bool StaticQueue::isFull() const {
    return count == MAX_QUEUE_SIZE;
}

void StaticQueue::enqueue(dataType* element) {
    if (isFull()) {
        std::cerr << "[!] Error: Queue is full\n";
        return;
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = element;
    count++;  
} 

void StaticQueue::dequeue() {
    if (isEmpty()) {
        std::cerr << "[!] Error: Queue is empty\n";
        return;
    }
    front = (front + 1) % MAX_QUEUE_SIZE;
    count--;   
}

int StaticQueue::size() const {
    return count;
}

dataType* StaticQueue::getFront() const {
    if (isEmpty()) {
        throw std::runtime_error("[!] Error: Queue is empty, cannot take any element");
    }
    return data[front];
}

std::string StaticQueue::toString(estadoProceso etapa) const {
    std::ostringstream oss;

    if (isEmpty()) {
        return "";
    }

    int current_index = front;
    for (int i = 0; i < count; i++) {
        oss << data[current_index]->toString(etapa);
        current_index = (current_index + 1) % MAX_QUEUE_SIZE;
    }

    return oss.str();
}
