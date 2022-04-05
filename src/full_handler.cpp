#include "full_handler.h"

/*
* Main Menu
* Precondition: None.
* Postcondition: Returns a Full_Handler::MM_ constant represnting the option choosen.
*
* This subroutine will take care of displaying the main menu and asking for input.
* The input is processed by another subroutine.
*/
int main_menu() {
    initscr();
    printw("Hello World!");
	refresh();
	getch();
	endwin();

    return 0;
}

/*
* Full Handler Main Entry Point
* The run_full subroutine is the starting point for the full version.
* It starts by whosing a menu calling other functions based on the input.
*/
void run_full() {
    main_menu();
    // Show menu.
}