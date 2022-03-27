# Design
It would be dumb if the final product wouldn't have the exact requirements given by the professor. I will use conditional compilation techniques to have two versions of the game (the "Academic" and the "Full"). I will start by working on the "Academic" version (which won't use the ncurses library).

The architecture of the software will consist of four main modules.
- Game engine: It contains the data structures and API to control the state of the game
- The driver: It initializes the game, creating a game object and calling the respective output handler ("Academic" or "Full"). For the "Academic" only version, the program will start directly in the "Academic" environment (it will not ask the user which one to use).
- "Academic" handler: This controls the game outputting in the same format exemplified in the start document.
- "Full" handler: This uses the ncurses library, and it runs the program more interactively.

I will start by creating all the files in the `src` folder and completing the header files. This step may overlap the work stage a little bit.

I designed a simple wireframe for the "Full Version" on a sheet of paper. I also described how the program updates and changes as users interact with it (on a superficial level). On a usual project, I may additionally create mockups of the UI, a code reference, or a dependency tree of the different modules. It is good practice to spend more time designing than coding.

Since there is no code reference for this project, I will be thorough in the inline documentation. Header files (at this stage) are written based on the wireframe I made, with an idea of how the different objects would interact to perform the desired actions in the program.

---

Previous: [Research](research.md)<br />
Next: [Work](work.md)