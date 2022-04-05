# Make file for ToH_TUI

# Edit the variables below.
# Path to header file.
win_headers = -I "C:\Program Files\mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\opt\include\ncursesw" -I "C:\Program Files\mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\opt\include"
win_libs = -L "C:\Program Files\mingw-w64\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\opt\lib" -lncurses

# ToH_TUI game compilation for Windows.
win_toh_tui: full_handler.o academic_handler.o game_engine.o
	g++ -o dist/bin/win_toh_tui src/main.cpp dist/obj/academic_handler.o dist/obj/full_handler.o dist/obj/game_engine.o -std=c++14 $(win_headers) $(win_libs) -static -Wall

# Full handler compilation for Windows only.
full_handler.o: src/full_handler.cpp src/full_handler.h
	g++ -o dist/obj/full_handler.o -c src/full_handler.cpp -std=c++14 -Wall

# Academic handler compilation.
academic_handler.o: src/academic_handler.cpp src/academic_handler.h
	g++ -o dist/obj/academic_handler.o -c src/academic_handler.cpp -std=c++14 -Wall

# Game engine compilation.
game_engine.o: src/game_engine.cpp src/game_engine.h
	g++ -o dist/obj/game_engine.o -c src/game_engine.cpp -std=c++14 -Wall