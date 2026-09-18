#ifndef DS_H
#define DS_H

#include <cstdlib>
#include <ctime>

// Node in a circular doubly-linked list
class Node {
public:
    int key;      // 0 or 1 only
    Node* next;
    Node* prev;
    
    Node(int k = 0) : key(k), next(nullptr), prev(nullptr) {}
};

// Circular Doubly-Linked List
class CircularList {
private:
    Node* head;
    int actualLength;  // For testing purposes only - students shouldn't use this!
    
public:
    CircularList() : head(nullptr), actualLength(0) {}
    
    ~CircularList() {
        if (!head) return;
        
        Node* current = head;
        Node* next;
        do {
            next = current->next;
            delete current;
            current = next;
        } while (current != head);
    }
    
    // Get pointer to head (for student algorithms)
    Node* getHead() const {
        return head;
    }
    
    // Get actual length (for verification only - not available to students!)
    int getActualLength() const {
        return actualLength;
    }
    
    // Add node at the end
    void addNode(int key) {
        Node* newNode = new Node(key);
        
        if (!head) {
            // First node - point to itself
            head = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            // Insert before head (at the end of circular list)
            Node* tail = head->prev;
            
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
        
        actualLength++;
    }
    
    // Static method: Create random circular list
    // Size between 100 and 1000
    // Key is 1 with probability 0.5, otherwise 0
    static CircularList* createRandom() {
        static bool seeded = false;
        if (!seeded) {
            srand(time(0));
            seeded = true;
        }
        
        // Random size between 100 and 1000
        int size = 100 + (rand() % 901);
        
        CircularList* list = new CircularList();
        
        for (int i = 0; i < size; i++) {
            int key = (rand() % 2);  // 0 or 1 with equal probability
            list->addNode(key);
        }
        
        return list;
    }
    
    // Create list with specific size (for controlled testing)
    static CircularList* createRandomSize(int size) {
        CircularList* list = new CircularList();
        
        for (int i = 0; i < size; i++) {
            int key = (rand() % 2);
            list->addNode(key);
        }
        
        return list;
    }
    
    // Verify list integrity (for testing)
    bool verifyIntegrity() const {
        if (!head) return actualLength == 0;
        
        int count = 0;
        Node* current = head;
        
        do {
            // Check if key is 0 or 1
            if (current->key != 0 && current->key != 1) {
                return false;
            }
            
            // Check circular connections
            if (current->next->prev != current) {
                return false;
            }
            
            count++;
            current = current->next;
            
            // Safety check
            if (count > actualLength + 10) {
                return false;  // Loop detected
            }
            
        } while (current != head);
        
        return count == actualLength;
    }
};

#endif // DS_H