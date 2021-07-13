# four-in-a-row-duels
This is a C++ and PyGame Implementation of the classic "ConnectFour" game.

It is part of a series of projects which use the duels package developed by Professor Olivier Kermogant:
https://github.com/oKermorgant/duels

The duels package uses C++ and Python to create/implement games. These games can be turn-based or not, and are played by (usually) 2 "clients". These clients are simply C++ programs which are written to implement algorthims that the user/student has coded, with an emphasis on AI techniques.

To run, just run the CMakeLists.txt file and run "four_in_a_row_duels_server" executable

or using a compiler, e.g. g++, gcc

gcc <<executable_name>> -o server.cpp src/four_in_a_row_duels_ai.cpp src/mechanics.cpp src/game_grid.cpp

In the CMakeLists.txt, it is given as:
add_executable(four_in_a_row_duels_server
    server.cpp
    src/four_in_a_row_duels_ai.cpp
    src/mechanics.cpp
    src/game_grid.cpp)
    
    
Note that the CMakeLists.txt already handles the include folder paths.

The branch "edit-03" contains the most recent version of the game. This branch equally prints to the console the results and some information I use in debugging/tracing errors.

The branch "edit-03-pub" has the most recent version, but without any information being printed to the screen.

Kindly note any errors you come across while using this program. Thank you.
