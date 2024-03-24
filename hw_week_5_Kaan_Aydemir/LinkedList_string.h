#pragma once
#include"Node.h"
#include <string>
#include <iostream>
using namespace std;
class LinkedList {
public:
    // Constructors
    LinkedList();
    LinkedList(string li[], int sz);
    LinkedList(const LinkedList& other);
    ~LinkedList();

    // Element Access
    string& at(int index);
    string& front();
    string& back();

    Node* findMiddleNode()const;
    Node* getSmallestNode()const;
    void moveSmallestToFront();

    void printList()const;

    // Modifiers
    void push_back(const string& value);
    void pop_back();
    void push_front(const string& value);
    void pop_front();
    void insert_at(int index, const string& value);
    void insert_after(int index, const string& val);
    void erase_at(int index);
    void erase(const string& e);
    void clear();

    // Capacity
    int size() const;
    bool empty() const;

    LinkedList& operator=(const LinkedList& lhs);
    bool operator==(const LinkedList& lhs)const;
    LinkedList operator+(const LinkedList& other)const;
    LinkedList& operator+(const string& data);
    friend ostream& operator<<(ostream& out, const LinkedList &list);
private:
    Node* head;
};
