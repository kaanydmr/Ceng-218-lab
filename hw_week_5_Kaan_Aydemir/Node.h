#pragma once
#include <string>
#include <iostream>
#include<ostream>
using namespace std;
class Node
{
public:
    string data;
    Node* next;

    Node():next(nullptr){}
    Node(const string &na) :next(nullptr) {}

    void print()const {
        cout << data << "->";
    }
    friend ofstream& operator<<(ofstream & out, const Node & obj);
};

