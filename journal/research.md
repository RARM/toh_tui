# Research
Although the sample output given by the professor clarifies that there is no need for any graphics, my first thought was [Bastet](https://snapcraft.io/install/bastet/ubuntu) (a terminal game that uses ncurses graphics). Surely is not needed, but I will implement my solution using ncurses. However, my final solution should have the option to run a simple output screen that works without ncurses (matching the professor's sample output).

I recall that using ncurses is a bit complicated for Windows, so I will start by testing a simple ncurses program and making it work on Windows. If the program doesn't work for Windows, I will have to change the strategy. The most important thing is that the professor can open my program in her Windows machine (target user).

## Testing ncurses
The first step is to install [MinGW-W64](https://www.mingw-w64.org/). This setup will allow me to include and use ncurses in Windows. It will be the same setup I am going to use for development.

I installed MinGW-W64, specifically the MingW-W64-builds, from the [downloads page](https://www.mingw-w64.org/downloads/) and selected the 64-bits (86_64) version during installation. If the download fails during installation (servers down), you can get the pre-built package from the [SourceForge page](https://sourceforge.net/projects/mingw-w64/files/). I downloaded `x86_64-posix-seh`, which is the latest version to this date (March 23, 2022).

After completing the installation, I wrote a simple ncurses program to test my setup.

```c++
#include <ncurses.h>

int main(void) {
    // Show a blank (or better black) screen.
    initscr();
    refresh();

    // Wait for user to press a key and close.
    getch();
    endwin();

    return 0;
}
```

To learn about the ncurses API, look for a tutorial elsewhere.

```txt
g++ -o output_filename input_source_code.cpp -I path/to/headers -I other/path/if/necessary -L path/to/libs -l<libname> -static
```

```txt
g++ -o main main.cpp -I C:\Program` Files\mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\opt\include\ncursesw -I C:\Program` Files\mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\opt\include -L C:\Program` Files\mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\opt\lib -lncurses -static
```

---

Previous: [Start](readme.md)