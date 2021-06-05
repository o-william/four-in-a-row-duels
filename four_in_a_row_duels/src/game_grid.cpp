/* connectFour game using the duels package
 *
 * ECN Project (2020/2021 - Semester II)
 * Oluwapelumi WILLIAMS (IMARO II)
 * Adedamola SODE (IMARO I)
 *
 * Supervisor : Professor Olivier Kermogant
 *
 *
 * Implementation File of the "GameGrid" class
 * File Name: game_grid.cpp
 * Definition File: game_grid.h
*/

#include <duels/four_in_a_row_duels/game_grid.h>
using namespace duels::four_in_a_row_duels;

GameGrid::GameGrid(int rowIn, int columnIn): ROWS{rowIn}, COLUMNS {columnIn}{
    if (rowIn < 6 || columnIn < 8){
        std::cout<<"Error: Entered dimensions are less than standard."<<std::endl;
    }
    else{
        empty_token = ' ';
        resetGrid(ROWS, COLUMNS);
    }
    // The above error checking should not be here. It should be at the "fiar_lite.cpp" constructor
}

// void GameGrid::setRows(int rowIn){
//     ROWS = rowIn;
// }

// void GameGrid::setColumns(int columnIn){
//     COLUMNS = columnIn;
// }

int GameGrid::getRows() const{
    return ROWS;
}

int GameGrid::getColumns() const{
    return COLUMNS;
}

void GameGrid::setCell(int row_in, int column_in, char token_in){
    grid[row_in][column_in] = token_in;
}

char GameGrid::getCell(int row_in, int column_in) const{
    return grid[row_in][column_in];
}

void GameGrid::resetGrid(){
    grid.assign(ROWS, std::vector<char> (COLUMNS, empty_token));
}

void GameGrid::resetGrid(int rowIn, int columnIn){
    grid.assign(rowIn, std::vector<char> (columnIn, empty_token));
}


void GameGrid::printGrid(){
    std::vector<std::vector<char>>::iterator it_row;

    for(it_row = grid.begin(); it_row != grid.end(); ++it_row){
        std::vector<char>::iterator it_column;

        for(it_column = (*it_row).begin(); it_column != (*it_row).end(); ++it_column){
            std::cout<<"| "<<*it_column<<" ";
        }
        std::cout<<"|"<<std::endl;
    }

    for (int i=0; i<COLUMNS; i++){
        std::cout<<"____";
    }
    std::cout<<"_"<<std::endl;

    for (int i=0; i<COLUMNS; i++){
        std::cout<<" ";
        if (i < 10){
            std::cout<<" ";
        }
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
}

std::vector<std::vector<char>> GameGrid::getGrid(){
    return grid;
}
