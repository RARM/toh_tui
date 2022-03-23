# Journal
This folder contains records in a journal-like style of the process of creating the TOH-TUI game. The structure of this journal is:
- Start (this file).
- Research.
- Design.
- Work.

This structure resembles, in some way, a design cycle on purpose. Start reading below.

## Start
This project started as a challenge proposed by [Dr. Maria Petrie](https://www.fau.edu/engineering/directory/faculty/petrie/) in her class Data Structures and Algorithm Analysis. The objective is to create a playable Towers of Hanoi terminal game. Briefly, she has these requirements and suggestions:
- Students can use the Standard Library Template's functions and data types for implementing the stacks.
- A number and a string of "x"s represent each disk. Disks use fields of 7 characters (e.g., the smallest disk uses one "x" with three blanks on each side).
- There are three stacks (representing the pegs): A, B, and C.
- Ask the player to enter the letter representing the source and destination stacks.
- If the user breaks the rule of "A larger disk can't be on top of a smaller disk," then display "Can't cheat!"
- When the user wins, display "Won in # moves!"
- If the player won in the minimal number of moves (2<sup>n</sup> - 1, where "n" is the number of disks), display "Can't do better than that!"

The example output given is:
```txt
1   x
3  xxx
5 xxxxx
    A            B            C

What is your move? (give first the source stack (A, B, or C) and the Destination Stack, separated by 1 Space): A C


3  xxx
5 xxxxx                  1   x
    A            B           C

OR, you can print the following


3  xxx                   1   x
5 xxxxx
    A            B           C
```

---

Next: [Reseach](research.md)