#include "game_engine.h"

/*
* Rod_Stack Constructor
* Precondition: None.
* Postcondition: A new Rod_Stack object was created.
*/
Rod_Stack::Rod_Stack()
    : top{ nullptr } {}

/*
* Rod_Stack Destructor
* Precondition: None.
* Postcondition: Deallocates memory for all the disks in the stack.
*/
Rod_Stack::~Rod_Stack() {
    this->del();
}

/*
* Rod_Stack Copy Constructor
* Precondition: Pass another Rod_Stack as an argument.
* Postcondition: A new Rod_Stack object is created with the same elements as the argument.
*/
Rod_Stack::Rod_Stack(const Rod_Stack& other)
    : top{ nullptr } {
    struct Disk* current{ nullptr }, * o_current{ other.top };

    if (o_current != nullptr) { // copy only if not empty
        current = new struct Disk;
        current->id = o_current->id;
        this->top = current;

        o_current = o_current->next;

        while (o_current->next != nullptr) {
            o_current = o_current->next;
            current->next = new struct Disk;
            current = current->next;
            current->id = o_current->id;
        }
    }
}

/*
* Rod_Stack Copy Assignment
* Precondition: Another Rod_Stack object is given as an argument.
* Postcondition: The current stack is cleared and a new stack is created with the same values as the argument object.
*/
Rod_Stack& Rod_Stack::operator=(const Rod_Stack& other) {
    struct Disk* current{ nullptr }, * o_current{ other.top };

    this->clear();

    if (o_current != nullptr) { // copy only if not empty
        current = new struct Disk;
        current->id = o_current->id;
        this->top = current;

        o_current = o_current->next;

        while (o_current->next != nullptr) {
            o_current = o_current->next;
            current->next = new struct Disk;
            current = current->next;
            current->id = o_current->id;
        }
    }

    return *this;
}

/*
* Rod_Stack: Get the current size of the stack.
* Precondition: None.
* Postcondition: The amount of disks in the current rod is given as an integer.
*/
size_t Rod_Stack::size() {
    size_t total{ 0 };
    struct Disk* current{ this->top };

    while (current != nullptr) {
        total++;
        current = current->next;
    }

    return total;
}

/*
* Rod_Stack: Clear the current stacks.
* Precondition: None.
* Postcondition: All the disks in the current stack are deallocated and the top is set to nullptr.
*/
void Rod_Stack::clear() {
    this->del();
    this->top = nullptr;
    return;
}

/*
* Rod_Stack: Add a new disk to the top.
* Precondition: A integer representing the new disk is given as the argument.
* Postcondition: Memory is allocated for the new disk and added to the top of the rod. If the value is 0, it does nothing.
*/
void Rod_Stack::push(unsigned disk) {
    struct Disk* temp{ this->top };
    
    if (disk != 0) {
        this->top = new struct Disk;
        this->top->id = disk;
        this->top->next = temp;
    }

    return;
}

/*
* Rod_Stack: Removes the disk at the top.
* Precondition: None.
* Postcondition: The disk at the top is removed. Nothing is returned. Use "peek" to get the value before calling pop. It does nothing if the stack is empty.
*/
void Rod_Stack::pop() {
    struct Disk* temp{ nullptr };

    if (this->top != nullptr) {
        temp = this->top->next;
        delete this->top;
        this->top = temp;
    }

    return;
}

/*
* Rod_Stack: Helper function to deallocate all the memory of the disks of the current stack.
* Precondition: None.
* Postcondition: All the disks in the current stack are deallocated, but the top is not set to null.
*/
void Rod_Stack::del() {
    struct Disk* current{ this->top }, * next{ nullptr };

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }

    return;
}