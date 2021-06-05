# four-in-a-row-duels
This is a C++ and PyGame Implementation of the classic "ConnectFour" game.

It is part of a series of projects which use the duels package developed by Professor Olivier Kermogant
https://github.com/oKermorgant/duels

The duels package uses C++ and Python (PyGame) to create a turn-based game which can be played by multiple "clients". These clients are simply C++ programs which are written to "behave" as players playing the game, with an emphasis on AI techniques.

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

The current AI contains some bugs. We will work on it.
In like manner, we acknowledge that there also might be bugs in other parts of this program. We will work on it.
Additionally, we perceive that there might be some unhandled exceptions in the program. We will work on it.
Last but not least, we recognize that we might not be using right data structures or the most optimal algorithms for this trivial problem. Again, we will work on this. Thank you.
