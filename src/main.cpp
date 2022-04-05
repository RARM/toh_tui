// main.cpp -- Game driver.
// This file takes care of initilizing the game and running the respective handler.

// Compilation settings.
#define FULL_VERSION true // It will only compile the "Academic" version if false.

#include "academic_handler.h"
#if FULL_VERSION
#include "full_handler.h"
#endif

int main(void) {

#if FULL_VERSION
    char in;
    // Ask for the version to run.
    std::cout << "Select the version to run: ";
    std::cin >> in;

    if (in == '1') run_full();
    else run_academic();
#else
    run_academic();
#endif

    return 0;
}