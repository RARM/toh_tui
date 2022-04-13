#include <ncurses.h>
#include <chrono>

int main(int argc, char const *argv[])
{
    int user_input;
    std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::system_clock::now();
    std::chrono::duration<std::chrono::system_clock::rep> duration; // = std::chrono::system_clock::now() - start_time;
    
    initscr();

    printw("Press \"q\" to exit.");
    refresh();

    timeout(1000/10); // 10 Hz
    while ((user_input = getch()) != 'q')
    {
        clear();
        printw("Press \"q\" to exit.\n");

        // Calculate and display seconds.
        duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start_time);
        printw("Time passed: %ld seconds.", duration.count());
        refresh();
    }
    

    endwin();
    return 0;
}
