# four-in-a-row-duels
C++ and PyGame Implementation of the classic ConnectFour game.

This is part of a project and it uses the duels package developed by Olivier Kermogant
https://github.com/oKermorgant/duels

The current AI is very buggy. We will work on it.

To run, just run the CMakeLists.txt file and run "four_in_a_row_duels_server" executable

or

<<executable_name>> server.cpp src/four_in_a_row_duels_ai.cpp src/mechanics.cpp src/game_grid.cpp)

In the CMakeLists.txt, it is given as 
add_executable(four_in_a_row_duels_server
    server.cpp
    src/four_in_a_row_duels_ai.cpp
    src/mechanics.cpp
    src/game_grid.cpp)
    
    
Note that the CMakeLists.txt already handles the include folder paths.
