#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <stdexcept> // for runtime_error

using namespace std;

// Define the stack node structure
template <typename T>
struct StackNode {
    T data;                // Data stored in the node
    StackNode* next;       // Pointer to the next node

    // Constructor
    StackNode(const T& value) : data(value), next(nullptr) {}
};

// Define the stack class
template <typename T>
class MyStack {
private:
    StackNode<T>* topNode; // Pointer to the top node of the stack

public:
    // Constructor
    MyStack() : topNode(nullptr) {}

    // Destructor
    ~MyStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return topNode == nullptr;
    }

    // Push operation
    void push(const T& value) {
        StackNode<T>* newNode = new StackNode<T>(value); // Create a new node
        newNode->next = topNode; // The new node points to the current top node
        topNode = newNode;       // Update the top node pointer
    }

    // Pop operation
    void pop() {
        if (isEmpty()) {
            throw runtime_error("Stack underflow: Cannot pop from an empty stack.");
        }
        StackNode<T>* temp = topNode; // Save the current top node
        topNode = topNode->next;      // Update the top node pointer
        delete temp;                  // Free the memory of the old top node
    }

    // Get the top element
    T top() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty: No top element.");
        }
        return topNode->data;
    }

    // Display the stack content (for debugging)
    void display() const {
        StackNode<T>* current = topNode;
        cout << "Stack: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

#endif // MYSTACK_H
