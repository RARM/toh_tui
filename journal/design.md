# Design
It would be dumb if the final product wouldn't have the exact requirements given by the professor. I will use conditional compilation techniques to have two versions of the game (the "Academic" and the "Full"). I will start by working on the "Academic" version (which won't use the ncurses library).

The architecture of the software will consist of four main modules.
- Game engine: It contains the data structures and API to control the state of the game
- The driver: It initializes the game, creating a game object and calling the respective output handler ("Academic" or "Full"). For the "Academic" only version, the program will start directly in the "Academic" environment (it will not ask the user which one to use).
- "Academic" handler: This controls the game outputting in the same format exemplified in the start document.
- "Full" handler: This uses the ncurses library, and it runs the program more interactively.

I will start by creating all the files in the `src` folder and completing the header files. This step may overlap the work stage a little bit.

---

Previous: [Research](research.md)<br />
Next: Work