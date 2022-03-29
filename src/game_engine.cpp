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
        while (o_current != nullptr) {
            current->next = new struct Disk;
            current = current->next;
            current->id = o_current->id;
            o_current = o_current->next;
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
        while (o_current != nullptr) {
            current->next = new struct Disk;
            current = current->next;
            current->id = o_current->id;
            o_current = o_current->next;
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
* Get the curret state of the rod.
* Precondition: None.
* Postcondition: A vector with all the values from top to bottom is returned.
*/
std::vector<unsigned> Rod_Stack::get_state() {
    std::vector<unsigned> state;
    struct Disk* current{ this->top };

    while (current != nullptr) {
        state.push_back(current->id);
        current = current->next;
    }

    return state;
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

/*
* ToH_Game Constructor.
* Precondition: The number of disks must be given as an argument. Minimum is 1 (forced).
* Postcondition: The game will be started from zero. All the disks will be placed in rod A.
* 
* How does an unsigned number represent a disk?
* Each disk is represented by an id = 1, 2, 3, 4, etc...
* The size of the disk when being displayed is an odd number of "x"s.
* The width of the disk is calculated as follows: id + (id - 1) or 2 * id - 1
*/
ToH_Game::ToH_Game(size_t disks_num)
    : disks_amount{ (disks_num > 0) ? disks_num : 1 }, rods{} {
    for (size_t i = 1; i <= this->disks_amount; i++)
        this->rods[ToH_Game::rod_A].push(static_cast<unsigned>(i));
}

/*
* ToH_Game: Make a move.
* Precondition: Constants (ToH_Game::rod_A, ToH_Game::rod_B, ToH_Game::rod_C) are given as arguments to represent the source and destination rods.
* Postcondition: Returns true if the move is valid and done; it returns false otherwise (and no changes are made to the game).
*/
std::tuple<bool, int> ToH_Game::move(int src, int dst) {
    const bool valid_src{ src == ToH_Game::rod_A || src == ToH_Game::rod_B || src == ToH_Game::rod_C };
    const bool valid_dst{ (dst == ToH_Game::rod_A || dst == ToH_Game::rod_B || dst == ToH_Game::rod_C) && src != dst };
    int return_code{};

    // const bool valid_mov{ valid_src && valid_dst && this->rods[src].size() > 0 && (this->rods[dst].peek() == 0 || this->rods[src].peek() < this->rods[dst].peek()) };
    // Check issues first.
    if (!valid_src || !valid_dst) // src and dst within range
        return_code = ToH_Game::MC4;
    else if (this->rods[src].size() == 0) // no disk in src
        return_code = ToH_Game::MC3;
    else if (this->rods[dst].peek() != 0 && this->rods[src].peek() > this->rods[dst].peek()) // src is bigger than dst
        return_code = ToH_Game::MC2;
    else // everything should be good
        return_code = ToH_Game::MC1;

    if (return_code == ToH_Game::MC1) { // move if no errors
        struct Disk temp;
        temp.id = this->rods[src].peek();
        this->rods[src].pop();
        this->rods[dst].push(temp.id);
    }

    return std::make_tuple((return_code == ToH_Game::MC1) ? true : false, return_code);
}

/*
* ToH_Game: Get the state of the game.
* Precondition: None.
* Postcondition: Return a Rods structure representing the current state of the game.
*/
Rods ToH_Game::get_state() {
    Rods state;

    state.A = this->rods[ToH_Game::rod_A].get_state();
    state.B = this->rods[ToH_Game::rod_B].get_state();
    state.C = this->rods[ToH_Game::rod_C].get_state();

    return state;
}