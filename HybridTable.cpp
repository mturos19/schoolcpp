#include "HybridTable.h"


Node::Node(int index, int val) {
	// Constructor, index + val + null next pointer
    index_ = index;
    val_ = val;
    next_ = nullptr;



}

Node::Node(int index, int val, Node* next) {
	// Constructor, index + val + next pointer
    index_ = index;
    val_ = val;
    next_ = next;

}

 Node::~Node() {
    // Destructor
    // delete next_; 
    // seems to fix segmentation fault
   

 }

HybridTable::HybridTable() {
    // Constructor entry initialised to 0 and empty linked list
    array_ = new int[INITIAL_ARRAY_SIZE];
    for (int i = 0; i < INITIAL_ARRAY_SIZE; i++) {
        array_[i] = 0;
    }
    arraySize = INITIAL_ARRAY_SIZE;
    list_ = nullptr;
    listSize = 0;

}

HybridTable::HybridTable(const int *p, int n) {
    // Constructor with parameters
    array_ = new int[n];
    for (int i = 0; i < n; i++) {
        array_[i] = p[i];
    }
    arraySize = n;
    list_ = nullptr;
    listSize = 0;



}

HybridTable::~HybridTable() {
	// Destructor of hybridtable
    delete[] array_;
    while(list_ != nullptr){
        Node* temp = list_;
        list_ = list_->next_;
        delete temp;
    }

}

HybridTable::HybridTable(const HybridTable& other) {
    // Copy constructor
    // Array part
    arraySize = other.arraySize;
    array_ = new int[other.arraySize];
    for (int i = 0; i < arraySize; i++) {
        array_[i] = other.array_[i];
    }
    


    // Linkedlist part
    list_ = nullptr;
    listSize = 0;
    Node* current = other.list_;
    while (current != nullptr) {
        Node* newNode = new Node(current->index_, current->val_);
        newNode->next_ = list_;
        list_ = newNode;
        listSize++;
        current = current->next_;
    }

}

HybridTable& HybridTable::operator=(const HybridTable& other) {
    //copy assignment functions
    // Array part
    if(this != &other){
        delete[] array_;
        arraySize = other.arraySize;
        array_ = new int[arraySize];
        for (int i = 0; i < arraySize; i++) {
            array_[i] = other.array_[i];
        }
    }

    //Linked list
    if(this != &other){
        while(list_ != nullptr){
            Node* current = list_;
            list_ = list_->next_;
            delete current;
        }
        list_ = nullptr;
        listSize = 0;
        Node* current = other.list_;
        while (current != nullptr) {
            Node* newNode = new Node(current->index_, current->val_);
            newNode->next_ = list_;
            list_ = newNode;
            listSize++;
            current = current->next_;
        }
    }
    return *this;


}

int HybridTable::get(int i) const {
	// Return value at index, index bigger than array size return 0
    if (i >= arraySize) {
        return 0;
    }
    else {
        return array_[i];
    }



}

void HybridTable::set(int i, int val) {
    // Store value at index, if index in range or in list stores value, otherwise new node created. List should always be sorted
    array_[i] = val;
    if (i >= arraySize) {
        if (list_ == nullptr) {
            list_ = new Node(i, val);
            listSize++;
        }
        else {
            Node* current = list_;
            while (current->next_ != nullptr) {
                current = current->next_;
            }
            current->next_ = new Node(i, val);
            listSize++;
        }
    }
    else {
        Node* current = list_;
        while (current != nullptr) {
            if (current->index_ == i) {
                current->val_ = val;
            }
            current = current->next_;
        }
    }

    

}

 string HybridTable::toString() const {
     // Returns a string representation of contents of HybridTable.
     string result = "";
     for (int i = 0; i < arraySize; i++) {
         if (array_[i] != 0) {
             result += std::to_string(i) + " : " + std::to_string(array_[i]) + "\n";
         }
     }
     if (list_ != nullptr) {
         result += "---\n";
         Node* current = list_;
         while (current != nullptr) {
             result += std::to_string(current->index_) + " : " + std::to_string(current->val_);
             if (current->next_ != nullptr) {
                 result += " --> ";
             }
             current = current->next_;
         }
     }
     return result;

 }

int HybridTable::getArraySize() const {
    // returns the size of the array part
    return arraySize;

}

int HybridTable::getTotalSize() const {
    // returns the total size (number of entries) of the array part and the list part
    return arraySize + listSize;

}