# TerminalSnake
  A snake clone implemented entirely using standard output and ANSI escape codes
for color. Written in C++.

# Requirements
  - Your terminal/command prompt must support ANSI escape codes.
  - To build, GNU Make must be installed (https://www.gnu.org/software/make/)
  - By default, the included Makefile uses GPP to compile, but if you'd like to use clang simply change the macro "CC" from 'g++' to 'clang++'

# About
  This minigame is my first project written in C++. Some of the code may be unrefined, but I will come back and update this project as I learn.

  To make this game work without any third party libraries, I implemented a KeyListener for the terminal, and run the 'GUI' I developed on a seperate thread. I avoided using a GUI library because I liked the challenge of developing something fully interactive from scratch. I am happy with the result and as I learn I will try to repair some of the visual glitches.

  Thanks for playing!