#include <iostream>
#include "Node.h"
#include "LinkedList_string.h"

using namespace std;

int main() {

    int choice = 15, index;
    string data;
    LinkedList list;

    Node* nodeOperations = nullptr;

    while(choice != 0){

        choice = 15;

        cout << "\nWelcome to the Linked List Program!\n";
        cout << "Menu:\n";
        cout << "1. Add an element\n";
        cout << "2. Remove an element by value\n";
        cout << "3. Access an element at index\n";
        cout << "4. Insert an element at index\n";
        cout << "5. Insert an element after index\n";
        cout << "6. Remove an element at index\n";
        cout << "7. Print the linked list\n";
        cout << "8. Print the size of the linked list\n";
        cout << "9. Check if the linked list is empty\n";
        cout << "10. Clear the linked list\n";
        cout << "11. Find the middle node\n";
        cout << "12. Find the smallest node\n";
        cout << "13. Move smallest node to front\n";
        cout << "14. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice) {

            case 1:
                cout << "What string you want to store: " ;
                cin >> data;
                list.push_back(data);
                cout << "Node with data: " << data << " is added" << endl;
                break;

            case 2:

                cout << "What element do you want to remove: ";
                cin >> data;
                list.erase(data);
                cout << "Node containing " << data << " is erased" << endl;
                break;

            case 3:

                cout << "What index you want to access element: ";
                cin >> index;
                cout << "Element on index "<< index << ": " << list.at(index).data();
                break;

            case 4:

                cout << "What index you want to add an element: ";
                cin >> index;
                cout << "What string you want to store: " ;
                cin >> data;
                list.insert_at(index, data);
                cout << "Node containing " << data << " at index "<< index << " added" << endl;
                break;

            case 5:
                cout << "What index you want to add an element after: ";
                cin >> index;
                cout << "What string you want to store: " ;
                cin >> data;
                list.insert_after(index, data);
                cout << "Node containing " << data << " after index "<< index << " added" << endl;
                break;

            case 6:

                cout << "What index you want to remove an element: ";
                cin >> index;
                list.erase_at(index);
                cout << "Node at index: " << index << " is erased" << endl;
                break;

            case 7:

                list.printList();
                break;

            case 8:

                cout << "Linked lists size: " << list.size() << endl;
                break;

            case 9:

                list.empty() ? (cout << "List is empty") : (cout << "List is not empty");
                cout << endl;
                break;

            case 10:

                list.clear();
                cout << "List is now empty" << endl;
                break;

            case 11:

                nodeOperations = list.findMiddleNode();

                if (nodeOperations != nullptr) {
                    cout << "The middle node is: " << nodeOperations->data << endl;
                }
                else {
                    cout << "The list is empty." << endl;
                }
                break;

            case 12:

                nodeOperations = list.getSmallestNode();

                if (nodeOperations != nullptr) {
                    cout << "The smallest node is: " << nodeOperations->data << endl;
                }
                else {
                    cout << "The list is empty." << endl;
                }
                break;

            case 13:

                list.moveSmallestToFront();
                cout << "List updated." << endl;

                break;

            case 14:

                cout << "Exiting..." << endl;
                choice = 0;
                break;

            default:
                cout << "Enter Valid Choice" << endl;


                break;
        }

    }
    return 0;
}
