#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};


class UnorderedSet {
private:
    Node* head;
    
public:
    UnorderedSet() : head(nullptr) {}

    // Destructor
    ~UnorderedSet() {
        // Implement destructor to deallocate memory
        clear();
    }

    //insert an element into the set
    void insert(int value) {
        // Implement insertion algorithms(simplest that you know)
        
        Node* walk = head;
        
        while(walk != nullptr){
        	if(walk->data == value)
        		break;
        	
        	walk = walk->next;
		}
		
		
		Node* newnode = new Node(value);
		newnode->next = head;
		head = newnode;
        
    }

    //remove an element from the set
    void remove(int value) {
        //Implement removal logic
        
        Node* walk = head;
        Node* prev = nullptr;
        
        while(walk != nullptr){
        	if(walk->data == value)
        		break;
        	prev = walk;
        	walk = walk->next;
		}
		
		
		prev->next = walk->next;
		
		delete walk;
		
  
    }

    //check if an element exists in the set
    bool contains(int value) const {
        //your implementation
         
        Node* walk = head;
        
        
        while(walk != nullptr){
        	if(walk->data == value)
        		return true;

        	walk = walk->next;
		}
		
		if(walk == nullptr){
			return false;
		}
        
        
        return false;
    }

    //get the size of the set
    int size() const {
        // your implementation to return the size of the set
        
        Node* walk = head;
        int counter = 0;
        
        
        while(walk != nullptr){
        	
			counter++;
        	walk = walk->next;
		}
		
		if(walk == nullptr){
			return 0;
		}
        
        
        return 0;
    }

    //check if the set is empty
    bool isEmpty() const {
    	
    	if(head == nullptr)
    		return true;
    	
        
        return false;
    }

    //clear the set
    void clear() {
        if(head==nullptr)
        	return;
        	
        Node* prev = nullptr;
        
        while(head != nullptr){
        	prev = head;
        	head = head->next;
        	delete prev;
		}
        
    }

    void printSet() const {
        // display the set elements
        
        Node* walk = head;
        int counter = 0;
        
        while(walk != nullptr){
        	
        	cout << "\nNode: " << counter << "\n    " << "Stores: " << walk->data << endl;
        	counter++;
        	walk = walk->next;
		}
		
    }

    //compute the intersection of two sets
    UnorderedSet intersection(const UnorderedSet& other) const {
    	
    	UnorderedSet result;
    	
    	Node* walkthis = this->head;
    	Node* walkother = other.head;
    	
    	while(walkthis != nullptr){
    		
    		while(walkother != nullptr){
    			
    			if(walkthis->data == walkother->data){
    				
    				result.insert(walkthis->data);
    				
				}
    			walkother = walkother->next;
			}
    		walkthis = walkthis->next;
		}
		
        return result;
    }

    //compute the union of two sets
    UnorderedSet setUnion(const UnorderedSet& other) const {
        UnorderedSet result;
        // your implementation to compute union
        return result;
    }

    //compute the set difference of two sets
    UnorderedSet setDifference(const UnorderedSet& other) const {
        UnorderedSet result;
        // your implementation to compute set difference
        return result;
    }
};

int main() {
    UnorderedSet mySet1, mySet2;
    mySet1.insert(5);
    mySet1.insert(10);
    mySet1.insert(15);
    mySet1.insert(18);
    mySet2.insert(10);
    mySet2.insert(2);
    mySet2.insert(5);
    UnorderedSet intersectionSet = mySet1.intersection(mySet2);
    UnorderedSet unionSet = mySet1.setUnion(mySet2);
    UnorderedSet differenceSet = mySet1.setDifference(mySet2);
    std::cout << "Intersection Set: ";
    intersectionSet.printSet();
    std::cout << "Union Set: ";
    unionSet. printSet ();
    std::cout << "Difference Set (mySet1 - mySet2): ";
    differenceSet.printSet();
    
    mySet1.printSet();
    return 0;
}
