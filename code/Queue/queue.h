#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "../Structure/structures.h"

template <typename T>
class StaticQueue {
private:
    std::vector<T*> data;  // usar punteros
    size_t maxSize;

public:
    StaticQueue(size_t size = 100) : maxSize(size) {}

    void enqueue(T* item) {
        if (data.size() >= maxSize)
            throw std::overflow_error("Queue full");
        data.push_back(item);
    }

    void dequeue() {
        if (data.empty())
            throw std::underflow_error("Queue empty");
        data.erase(data.begin());
    }

    T* getFront() {
        if (data.empty())
            throw std::underflow_error("Queue empty");
        return data.front();
    }

    bool isEmpty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

    std::string toString() const {
        std::ostringstream oss;
        for (const auto* item : data) {
            oss << item->toString(item->dameEstado()) << "\n";
        }
        return oss.str();
    }

    std::vector<std::string> toVectorString(estadoProceso estado) const {
        std::vector<std::string> v;
        for (const auto& item : data) {     // item ahora es un puntero T*
            if (item->dameEstado() == estado) {
                v.push_back(item->toString(estado));
            }
        }
        return v;
    }

};


#endif