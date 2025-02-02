#ifndef _LIST_HPP
#define _LIST_HPP

#include <stdint.h> 
/*
* @file list.h
* @brief implementation of singly linked list structure in C++
*/
 
template <typename T>
class List {

    public:
    List():head(nullptr), tail(nullptr), listSize(0) {}
    ~List() {
        Node* current = head;
        Node* next = nullptr;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
    }    
    List(const List&) = delete;
    List& operator=(const List&) = delete;
    List(List&&) = delete;
    List& operator=(List&&) = delete;
    void pushBack(T data) {
        Node *newNode = new Node{data, nullptr};
        if(nullptr == head) 
        {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        listSize++;
    }

    void pushFront(T data) {
        Node *newNode = new Node{data, nullptr};
        if(nullptr == head) 
        {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        listSize++;
    }

    T popBack() {
        if(nullptr != head) {
            Node* current = head;
            Node* prev = nullptr;
            while(current->next != nullptr) {
                prev = current;
                current = current->next;
            }
            if(nullptr != prev) {
                prev->next = nullptr;
                tail = prev;
            } else {
                head = nullptr;
                tail = nullptr;
            }
            T data = current->data;
            delete current;
            listSize--;
            return data;
        }
        throw std::out_of_range("List is empty");
    }

    T popFront() {
        if(nullptr != head) {
            Node* current = head;
            head = head->next;
            T data = current->data;
            delete current;
            listSize--;
            return data;
        }
        throw std::out_of_range("List is empty");
    }

    size_t size() {
        return listSize;
    }
    private:
        struct Node {
            T data;
            Node* next;
        };
        Node* head;
        Node* tail;
        size_t listSize;
};

#endif	// _LIST_HPP