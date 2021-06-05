cmake_minimum_required(VERSION 2.8.3)
project(four_in_a_row_duels_server CXX)

set(DUELS_ROOT "/opt/duels" CACHE STRING "Path to duels dev folder")
set(CMAKE_INSTALL_PREFIX ${DUELS_ROOT})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-pthread)
find_package (Threads)

# find ZeroMQ
find_path ( ZMQ_INCLUDE_DIR zmq.h )
find_library ( ZMQ_LIBRARY NAMES zmq )

include_directories(include ${DUELS_ROOT}/include ${ZMQ_INCLUDE_DIR})
add_definitions(-DDUELS_BIN_PATH="${DUELS_ROOT}/bin")
add_definitions(-DGAME_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DDUELS_SERVER)

#add_executable(test_game_grid
#    tests/test_game_grid.cpp
#    src/game_grid.cpp)

add_executable(four_in_a_row_duels_server
    server.cpp
    src/four_in_a_row_duels_ai.cpp
    src/mechanics.cpp
    src/game_grid.cpp)
target_link_libraries(four_in_a_row_duels_server ${CMAKE_THREAD_LIBS_INIT} ${ZMQ_LIBRARY})

# add whatever is needed to build display executable


# install server
install(TARGETS four_in_a_row_duels_server DESTINATION bin/four_in_a_row_duels)

# install gui and its deps
install(FILES four_in_a_row_duels_gui.py DESTINATION bin/four_in_a_row_duels
        PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
        
# client headers and templates
install(FILES include/duels/four_in_a_row_duels/game.h include/duels/four_in_a_row_duels/msg.h include/duels/four_in_a_row_duels/msg_detail.h DESTINATION include/duels/four_in_a_row_duels)
install(FILES client_template/CMakeLists.txt DESTINATION games/four_in_a_row_duels)
install(FILES client_template/four_in_a_row_duels.cpp DESTINATION games/four_in_a_row_duels )
