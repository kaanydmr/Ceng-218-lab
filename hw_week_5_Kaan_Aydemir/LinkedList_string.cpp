#pragma once
#include "LinkedList_string.h"

LinkedList::LinkedList() : head(nullptr) { }

Node* LinkedList::findMiddleNode()const{

    if(head == nullptr)
        return nullptr;

    Node* walk = head;
    int counter = 0;

    while(walk != nullptr) {
        if (size() / 2 == counter)
            return walk;

        walk = walk->next;
        counter++;
    }
}

Node* LinkedList::getSmallestNode()const {
    if (head == nullptr) {
        return nullptr;
    }

    Node* smallestNode = head;
    Node* currentNode = head->next;

    while (currentNode != nullptr) {
        if (currentNode->data < smallestNode->data) {
            smallestNode = currentNode;
        }
        currentNode = currentNode->next;
    }

    return smallestNode;
}

void LinkedList::moveSmallestToFront() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* walk = head;
    Node* smallestNode = head;
    Node* prevNode = nullptr;
    Node* prevSmallestNode = nullptr;

    while (walk != nullptr) {
        if (walk->data < smallestNode->data) {
            smallestNode = walk;
            prevSmallestNode = prevNode;
        }
        prevNode = walk;
        walk = walk->next;
    }

    prevSmallestNode->next = smallestNode->next;
    smallestNode->next= head;
    head = smallestNode;

}

void LinkedList::printList()const {

    int counter = 0;

    Node* temp = head;

    if(head == nullptr)
        cout << "List is empty" << endl;

    while(temp != nullptr){

        cout << "Node " << counter << endl;
        cout << "   " << temp->data << endl;

        temp = temp->next;
        counter++;
    }
}

LinkedList::LinkedList(string li[], int sz) {
    if (sz > 0) {
        head = new Node(li[0]);
        int i = 1;
        Node* lastNode = head;
        while (i < sz) {
            lastNode->next = new Node(li[i]);
            lastNode = lastNode->next;
            i++;
        }
    }
}

LinkedList::LinkedList(const LinkedList &other) {

    if (other.head == nullptr) {
        this->head = nullptr;
        return;
    }
    head = new Node(other.head->data);
    Node* w = other.head->next;
    Node* last = head;
    while (w != nullptr) {
        last->next = new Node(w->data);
        last = last->next;
        w = w->next;
    }

}

LinkedList::~LinkedList() {
    clear();
}

string &LinkedList::at(int index) {

    int counter = 0;
    Node *temp = head;
    while (temp!= nullptr){
        if(counter == index)
            return temp->data;
        temp = temp->next;
        counter++;
    }

}

string &LinkedList::front() {
    if (head == nullptr) {
        cout << "Error: List is empty" << endl;
    }
    else
        return head->data;
}

string &LinkedList::back() {
    if (head == nullptr) {
        cout << "Error: List is empty" << endl;
    }
    else {
        Node *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }
}

void LinkedList::push_back(const string &value) {
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::pop_back() {
    if (head == nullptr) {
        cout << "Error: List is empty" << endl;
        return;
    }

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        Node *secondLastNode = head;
        while (secondLastNode->next->next != nullptr) {
            secondLastNode = secondLastNode->next;
        }
        delete secondLastNode->next;
        secondLastNode->next = nullptr;
    }
}

void LinkedList::push_front(const string &value) {
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

void LinkedList::pop_front() {
    if (head == nullptr) {
        cout << "Error: List is empty" << endl;
        return;
    }

    Node *temp = head;
    head = head->next;
    delete temp;
}

void LinkedList::insert_at(int index, const string &value) {
    if (index < 0) {
        cout << "Error: index out of range" << endl;
        return;
    }

    if (index == 0) {
        push_front(value);
        return;
    }

    Node *prevNode = head;
    for (int i = 0; i < index - 1; ++i) {
        if (prevNode->next == nullptr) {
            cout << "Error: index out of range" << endl;
            return;
        }
        prevNode = prevNode->next;
    }

    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

void LinkedList::insert_after(int index, const string &val) {
    insert_at(index + 1, val);
}

void LinkedList::erase_at(int index) {
    if (index < 0 || head == nullptr) {
        cout << "Error: index out of range" << endl;
        return;
    }

    if (index == 0) {
        pop_front();
        return;
    }

    Node *prevNode = head;
    for (int i = 0; i < index - 1; ++i) {
        if (prevNode->next == nullptr) {
            cout << "Error: index out of range" << endl;
            return;
        }
        prevNode = prevNode->next;
    }

    if (prevNode->next == nullptr) {
        cout << "Error: index out of range" << endl;
        return;
    }

    Node *temp = prevNode->next;
    prevNode->next = temp->next;
    delete temp;
}

void LinkedList::erase(const string &e) {
    if (head == nullptr) {
        cout << "Error: List is empty" << endl;
        return;
    }

    while (head != nullptr && head->data == e) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    Node *prevNode = head;
    while (prevNode != nullptr && prevNode->next != nullptr) {
        if (prevNode->next->data == e) {
            Node *temp = prevNode->next;
            prevNode->next = temp->next;
            delete temp;
        } else {
            prevNode = prevNode->next;
        }
    }
}

void LinkedList::clear() {
    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

int LinkedList::size() const {
    int size = 0;
    for (Node *temp = head; temp != nullptr; temp = temp->next) {
        ++size;
    }
    return size;
}

bool LinkedList::empty() const {
    return head == nullptr;
}

LinkedList &LinkedList::operator=(const LinkedList &lhs) {
    if (this != &lhs) {
        clear();
        Node *ptr = lhs.head;
        while (ptr != nullptr) {
            push_back(ptr->data);
            ptr = ptr->next;
        }
    }
    return *this;
}

bool LinkedList::operator==(const LinkedList &lhs) const {
    Node *ptr1 = head;
    Node *ptr2 = lhs.head;
    while (ptr1 != nullptr && ptr2 != nullptr) {
        if (ptr1->data != ptr2->data) {
            return false;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return ptr1 == nullptr && ptr2 == nullptr;
}

ostream &operator<<(ostream &out, const LinkedList &list) {
    for (Node *temp = list.head; temp != nullptr; temp = temp->next) {
        out << temp->data << " ";
    }
    return out;
}

LinkedList LinkedList::operator+(const LinkedList& other)const {
    LinkedList res;
    Node* res_walk = nullptr;
    if (this->head == nullptr && other.head == nullptr) return res;
    if (head != nullptr) {
        res.head = new Node(head->data);
    }
    else if (other.head != nullptr) {
        res.head = new Node(other.head->data);
    }
    res_walk = res.head;
    Node* w = nullptr;
    if (head != nullptr) {
        w = head->next;
        while (w != nullptr) {
            res_walk->next = new Node(w->data);
            res_walk = res_walk->next;
            w = (*w).next;
        }
    }
    if (head == nullptr && other.head != nullptr)
        w = other.head->next;
    else
        w = other.head;

    while (w != nullptr) {
        res_walk->next = new Node(w->data);
        res_walk = res_walk->next;
        w = (*w).next;
    }

    return res;
}

LinkedList& LinkedList::operator+(const string& data) {
    Node* w = this->head;
    while (w != nullptr) {
        if (w->next == nullptr) {
            w->next = new Node(data);
            break;
        }
        w = w->next;
    }
    return *this;
}