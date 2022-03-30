// Unit testing environment.
#include <iostream>
#include "game_engine.h"

void some_test_function(Rod_Stack a_stack) {
    a_stack.push(50);
    return;
}

int main(void) {
    Rod_Stack rod_A;
    rod_A.push(1);
    rod_A.push(2);

    std::cout << "The size of the first \"Rod_Stack\" object should be 2. It is "
              << rod_A.size() << ".\n";

    std::cout << "\nExpected top value: 2.\n"
              << "Actual value: " << rod_A.peek() << ".\n\n";

    std::cout << "--------------------------------------------------------\n";

    std::cout << "Removing and adding some values.\n\n";

    rod_A.pop();
    rod_A.push(5);

    std::cout << "Size should still be 2, but top should be 5.\n"
              << "Actual size: " << rod_A.size() << ".\n"
              << "Actual top: " << rod_A.peek() << ".\n\n";

    Rod_Stack rod_B{ rod_A };
    rod_A.clear();

    std::cout << "Size of \"rod_A\" after clearing it: " << rod_A.size() << ".\n\n";

    rod_B.push(10);
    rod_B.push(20);

    std::cout << "Size of \"rod_B\" before calling function: " << rod_B.size() << ".\n";
    some_test_function(rod_B);
    std::cout << "Size after: " << rod_B.size() << ".\n";

    std::cout << "State of the \"rod_B\": [";
    for (unsigned num : rod_B.get_state()) std::cout << " " << num;
    std::cout << " ]\n";

    return 0;
}