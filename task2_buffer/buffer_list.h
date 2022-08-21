#pragma once

#include <iostream>

template<typename T>
class buffer_list {
    struct Node {
        T data;
        Node *next;
    };
    Node *head = nullptr;
    Node *last_element_added = nullptr;
    int capacity = 0;
    int elements_in_list = 0;
public:
    buffer_list(int capacity_);

    buffer_list(buffer_list<T> &&copyel) noexcept;

    buffer_list(buffer_list<T> &copyel);

    buffer_list<T> &operator=(buffer_list<T> &&copyel) noexcept;

    buffer_list<T> &operator=(const buffer_list<T> &copyel);

    T pop();

    ~buffer_list();

    void push(T);

    //iterator class
    class iterator {
        Node *now;
    public:

        iterator(Node *p = nullptr) : now(p) {};

        const T &operator*() const { return  now->data;};

        bool operator==(const iterator &p) const { return now == p.now; }

        bool operator!=(const iterator &p) const { return now != p.now; }

        iterator &operator++() {
            if (now) now = now->next;
            return *this;
        }

        iterator operator++(int) {
            Node *tmp = now;
            if (now) {
                now = now->next;
            }
            return iterator(tmp);
        }
        friend class buffer_list;
    };

    iterator begin(){
        return iterator(head);
    }
    iterator end(){
        return iterator(nullptr);
    }
};


//realisation of buffer_list
template<typename T>
buffer_list<T>::buffer_list(int capacity_) {
    capacity = capacity_;
}


template<typename T>
buffer_list<T>::~buffer_list() {
    Node *current = head;
    while (current != last_element_added) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    delete current;
}

template<typename T>
void buffer_list<T>::push(T date) {
    if (elements_in_list == 0) {
        head = new Node;
        head->data = date;
        last_element_added = head;
        ++elements_in_list;
        return;
    } else if (elements_in_list < capacity) {
        last_element_added->next = new Node;
        last_element_added = last_element_added->next;
        last_element_added->data = date;
        last_element_added->next = nullptr;
        ++elements_in_list;
        return;
    } else {
        last_element_added->next = head;
        last_element_added = head;
        head = head->next;
        last_element_added->next = nullptr;
        last_element_added->data = date;
        return;
    }

}


template<typename T>
buffer_list<T>::buffer_list(buffer_list<T> &copyel) {
    head = new Node;
    capacity = copyel.capacity;
    head->next = new Node;
    last_element_added = head->next;
    for (auto i = 0; i < copyel.capacity - 2; i++) {
        last_element_added->next = new Node;
        last_element_added = last_element_added->next;
    }
    last_element_added->next = nullptr;
    Node *current_node = head, *node_to_copy = copyel.head;
    while (current_node != last_element_added) {
        current_node->data = node_to_copy->data;
        current_node = current_node->next;
        node_to_copy = node_to_copy->next;
    }
    current_node->data = node_to_copy->next;
    current_node = nullptr;
    node_to_copy = nullptr;
    delete current_node;
    delete node_to_copy;
}

template<typename T>
buffer_list<T>::buffer_list(buffer_list<T> &&copyel) noexcept {
    head = copyel.head;
    last_element_added = copyel.last_element_added;
    capacity = copyel.capacity;
    elements_in_list = copyel.elements_in_list;
    copyel.head = nullptr;
    copyel.last_element_added = nullptr;
}

template<typename T>
buffer_list<T> &buffer_list<T>::operator=(buffer_list<T> &&copyel) noexcept {
    if (this != &copyel) {
        head = copyel.head;
        last_element_added = copyel.last_element_added;
        capacity = copyel.capacity;
        elements_in_list = copyel.elements_in_list;
        copyel.head = nullptr;
        copyel.last_element_added = nullptr;
    }
    return *this;
}

template<typename T>
buffer_list<T> &buffer_list<T>::operator=(const buffer_list<T> &copyel) {
    if (this != &copyel) {
        capacity = copyel.capacity;
        head = new Node;
        head->next = new Node;
        last_element_added = head->next;
        for (auto i = 0; i < capacity - 2; ++i) {
            last_element_added->next = new Node;
            last_element_added = last_element_added->next;
        }
        last_element_added->next = nullptr;
        Node *current_node = head, *node_to_copy = copyel.head;

        while (current_node != last_element_added) {
            current_node->data = node_to_copy->data;
            current_node = current_node->next;
            node_to_copy = node_to_copy->next;
        }
        current_node->data = node_to_copy->data;
        current_node = nullptr;
        node_to_copy = nullptr;
        delete current_node;
        delete node_to_copy;
    }
}

template <typename T>
T buffer_list<T>::pop(){
    --elements_in_list;
    auto tmp = head->data;
    Node* deleted = head;
    if(elements_in_list != 0)
        head = head->next;
    else {head = nullptr;
    last_element_added = nullptr;}
    delete deleted;
    return tmp;
}
