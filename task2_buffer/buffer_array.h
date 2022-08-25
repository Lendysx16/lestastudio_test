#pragma once

#include <iostream>
#include "my_exception.h"


template<typename T>
class buffer_array {
    T *container = nullptr;
    int capacity = 0;
    int elements_in_array = 0;
    T *head = nullptr, *tail = nullptr;
    T *end_of_array = nullptr;
public:
    buffer_array(int);

    ~buffer_array();

    buffer_array(buffer_array<T> &);

    buffer_array(buffer_array<T> &&) noexcept;

    buffer_array &operator=(const buffer_array<T> &);

    buffer_array &operator=(buffer_array<T> &&) noexcept;

    int size() {
        if (tail) {
            if(tail >= head)
                return tail - head + 1;
            return (end_of_array - head) + (head - container) + 1;
        }
        return 0;
    }

    void push(T);

    T pop();
};


template<typename T>
buffer_array<T>::buffer_array(int capacity_) {
    if(capacity_ < 1){
        throw zero_capacity();
    }
    capacity = capacity_;
    container = new T[capacity];
    head = container;
    end_of_array = container + capacity - 1;
}

template<typename T>
buffer_array<T>::~buffer_array() {
    delete container;
    head = nullptr;
    tail = nullptr;
    end_of_array = nullptr;
    delete head;
    delete tail;
    delete end_of_array;
}

template<typename T>
buffer_array<T>::buffer_array(buffer_array<T> &&copyel) noexcept {
    head = copyel.head;
    container = copyel.container;
    tail = copyel.tail;
    end_of_array = copyel.end_of_array;
    capacity = copyel.capacity;
    copyel.container = nullptr;

}

template<typename T>
buffer_array<T>::buffer_array(buffer_array<T> &copyel) {
    capacity = copyel.capacity;
    container = new T[capacity];
    head = container;
    end_of_array = container + capacity - 1;
    if (copyel.tail) {
        tail = head + (copyel.tail - copyel.head);
        T *current = head, copycurrent = copyel.head;
        while (current != tail) {
            *current = *copycurrent;
            if (head == end_of_array) {
                head = container;
                copycurrent = copyel.container;
            } else {
                ++head;
                ++copycurrent;
            }
        }
        *current = *copycurrent;
        current = nullptr;
        copycurrent = nullptr;
        delete current;
        delete copycurrent;
    }
}

template<typename T>
buffer_array<T> &buffer_array<T>::operator=(const buffer_array<T> &copyel) {
    if (this != copyel) {
        capacity = copyel.capacity;
        container = new T[capacity];
        head = container;
        end_of_array = container + capacity - 1;
        if (copyel.tail) {
            tail = head + (copyel.tail - copyel.head);
            T *current = head, copycurrent = copyel.head;
            while (current != tail) {
                *current = *copycurrent;
                if (head == end_of_array) {
                    head = container;
                    copycurrent = copyel.container;
                } else {
                    ++head;
                    ++copycurrent;
                }
            }
            *current = *copycurrent;
            current = nullptr;
            copycurrent = nullptr;
            delete current;
            delete copycurrent;
        }
    }
    return *this;
}


template<typename T>
buffer_array<T> &buffer_array<T>::operator=(buffer_array<T> &&copyel) noexcept {
    if (this != *copyel) {
        head = copyel.head;
        container = copyel.container;
        tail = copyel.tail;
        end_of_array = copyel.end_of_array;
        capacity = copyel.capacity;
        copyel.container = nullptr;
    }
    return *this;
}

template<typename T>
void buffer_array<T>::push(T element) {
    if (tail) {
        if (tail == end_of_array) tail = container;
        else ++tail;
        *tail = element;
        if (tail == head) {
            if (head == end_of_array)
                head = container;
            else
                ++head;
        }
        return;
    }

    *head = element;
    tail = head;
}

template<typename T>
T buffer_array<T>::pop(){
    if(!tail) throw nothing_to_pop_exepction();
    auto element = *head;
    if(head == tail){
        head = container;
        tail = nullptr;
    }
    else if(head == end_of_array)
        head = container;
    else
        ++head;
    return element;
}