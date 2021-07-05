/* connectFour game using the duels package
 *
 * ECN Project (2020/2021 - Semester II)
 * Oluwapelumi WILLIAMS (IMARO II)
 * Adedamola SODE (IMARO I)
 *
 * Supervisor : Professor Olivier Kermogant
 *
 *
 * Implementation File of the "FourInARowDuelsAI" class
 * File Name: four_in_a_row_duels_ai.cpp
 * Definition File: four_in_a_row_duels_ai.h
*/

#include <duels/four_in_a_row_duels/four_in_a_row_duels_ai.h>
// #include <iostream>

using namespace duels::four_in_a_row_duels;


void FourInARowDuelsAI::updateInput(){
    // the AI does this once it receives feedback i.e (when game_io.sync(current) is called)
    // note: the feedback received is the vector of opponent played cells
    // std::cout<<"AI Initialized: "<<ai_initialized<<std::endl;
    if (!ai_initialized){
        initializeAI();
    }

    // check the size of the feedback (which is a vector of played cells) for a case where no one has played before
    if (feedback.played_cells.size() == 0){
        // no one has played yet
    }
    else{
        // use the feedback provided to update the grids
        updateGrids();
    }

    int played_column; // Input that will be sent from the AI back to the server;

    // check if the entire grid is filled. (This is not needed as it will be handled by the server, but for a complete code, we add it)
    if ((int)feedback.played_cells.size() + 1 > (int)ROWS * COLUMNS / 2){
        // this will not account for the case where we have a dimension (row or column) as an odd number
        // it'll result in the last cell not being playable
        // grid is filled. no input to send
    }

    else{
        // update the column pool
        int column_pool_size = column_pool.size();
        for (int i=0; i<column_pool_size; i++){
            if (total_grid[0][column_pool[i]] == true){
                column_pool.erase(column_pool.begin()+i);
                break;
            }
        }
        // call the appropriate AI using switch-case. For each one, return the played column
        switch(difficulty){
        case 1:
            aiLevelOne(played_column);
            break;
        case 2:
            aiLevelTwo(played_column);
            break;
        case 3:
            aiLevelThree(played_column);
            break;
        default:
            aiLevelOne(played_column);
        }

        /* calculate the corresponding row in which the column will be filled
         * note: we are not using the computation from the mechanics, we are computing independently
         * to give a uniform played row, we might have to modify the feedback parameter
        */

        int played_row = getTopmostRow(played_column);

        // update the AI's "my_filled_cells" variable, and the "total_filled_cells" variable.
        my_grid[played_row][played_column] = true;
        total_grid[played_row][played_column] = true;

        input.played_column = played_column; // note the played column must both be within bounds, and not be played in an already filled up column. Hence the checks above.
    }
}


void FourInARowDuelsAI::resetOrientationCount(){
    orientation_it = 0;
}

//void FourInARowDuelsAI::initPlayQueue(){
//    play_queue.resize(0);
//}

void FourInARowDuelsAI::initializeAI(){
    initializeGrids();
    for (int i = 0; i < COLUMNS; i++)
    {
        column_pool.push_back(i);
    }

    orientations.resize(7);
    orientations[0].setAsHorizontal(1);
    orientations[1].setAsHorizontal(-1);
    orientations[2].setAsVertical(-1);
    orientations[3].setAsDiagonal(1);
    orientations[4].setAsDiagonal(-1);
    orientations[5].setAsADiagonal(1);
    orientations[6].setAsADiagonal(-1);

    resetOrientationCount();

    orientation_it_opp = 0;
    //initPlayQueue();

    feasible_column_pool.resize(column_pool.size());
    std::copy(column_pool.begin(), column_pool.end(), feasible_column_pool.begin());

    ai_initialized = true;
}


void FourInARowDuelsAI::initializeGrids(){
    my_grid.assign(ROWS, std::vector<bool> (COLUMNS, EMPTY_TOKEN));
    opponent_grid.assign(ROWS, std::vector<bool> (COLUMNS, EMPTY_TOKEN));
    total_grid.assign(ROWS, std::vector<bool> (COLUMNS, EMPTY_TOKEN));
}


void FourInARowDuelsAI::updateGrids(){
    int played_cells = feedback.played_cells.size();
    // update opponent grid with the last vector in the feedback
    opponent_grid[feedback.played_cells[played_cells-1].row][feedback.played_cells[played_cells-1].column] = true;
    total_grid[feedback.played_cells[played_cells-1].row][feedback.played_cells[played_cells-1].column] = true;
}


int FourInARowDuelsAI::getTopmostRow(int column){
    // returns -1 if column is filled to prevent compiler warning, but ideally, there's no way this value will be used due to the checking that has been done in the column selection.
    int played_row;
    for (int i = ROWS-1; i >= 0; i--){
        if (!total_grid[i][column]){
            played_row = i;
            return played_row;
            // break;
        }
    }
    return -1;
}


/* AI Levels.
 * They all return an integer value: between 0 and the number of columns in the game.
*/


void FourInARowDuelsAI::aiLevelOne(int &played_column){
    /* Uses the rand() function from stdlib.h and srand() in addition. The seed is a time object, created on every call to this function.
     * This is random (albeit predictable)
    */
    srand(clock());
    played_column = column_pool[rand() % column_pool.size()];

}


bool FourInARowDuelsAI::findCandidate(){
    if (orientation_it == int(orientations.size()) - 1 || (root_cell[0] == -1 || root_cell[1] == -1)){
        if (orientation_it == int(orientations.size()) - 1){
//            std::vector<int>::iterator it = std::find(feasible_column_pool.begin(), feasible_column_pool.end(), root_cell[1]);
//            feasible_column_pool.erase(it);
            resetOrientationCount();
        }
        int column_r, row_r;
        srand(clock());
        column_r = feasible_column_pool[rand() % feasible_column_pool.size()];
        row_r = getTopmostRow(column_r);

        if (probe(row_r, column_r, orientations[orientation_it])==true){
            root_cell[0] = row_r;
            root_cell[1] = column_r;
            candidate_found = true;

            direction = orientations[orientation_it].getDirection();

            std::cout<<"candiate found. row: "<<root_cell[0]<<", column: "<<root_cell[1]<<", orientation: "<<orientations[orientation_it].getName()<<", direction: "<<orientations[orientation_it].getDirection()<<std::endl;
            return true;
        }
        else{
            return false;
        }
    }

    else{
        if (probe(root_cell[0], root_cell[1], orientations[orientation_it])==true){
            candidate_found = true;
            direction = orientations[orientation_it].getDirection();
            std::cout<<"candiate found. row: "<<root_cell[0]<<", column: "<<root_cell[1]<<", orientation: "<<orientations[orientation_it].getName()<<", direction: "<<orientations[orientation_it].getDirection()<<std::endl;
            return true;
        }
        else{
            return false;
        }
    }
}












bool FourInARowDuelsAI::horizontalProbe(int row, int column, int direction){
    if (direction == 1){
        // check in the +ve direction; to the right
        if (column > COLUMNS - IN_A_ROW){
            // non-probable; not possible to result in a winning pattern
            return false;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (total_grid[row][column+i]){
                    if (opponent_grid[row][column+i]){
                        return false;
                    }
                }
            }
            return true;
        }
    }

    if (direction == -1){
        // check in the -ve direction; to the left
        if (column < IN_A_ROW - 1){
            // non-probable; not possible to result in a winning pattern
            return false;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (total_grid[row][column-i]){
                    if (opponent_grid[row][column-i]){
                        return false;
                    }
                }
            }
            return true;
        }
    }
    // invalid direction
    return false;
}


bool FourInARowDuelsAI::verticalProbe(int row, int column, int direction){
    if (direction == 1){
        // check in the +ve direction; downwards
        if (row > ROWS - IN_A_ROW){
            // non-probable; not possible to result in a winning pattern
            return false;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (total_grid[row+i][column]){
                    if (opponent_grid[row+i][column]){
                        return false;
                    }
                }
            }
            return true;
        }
    }

    if (direction == -1){
        // check in the -ve direction; upwards
        if (row < IN_A_ROW - 1){
            // non-probable; not possible to result in a winning pattern
            return false;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (total_grid[row-i][column]){
                    if (opponent_grid[row-i][column]){
                        return false;
                    }
                }
            }
            return true;
        }
    }
    // invalid direction
    return false;
}


bool FourInARowDuelsAI::diagonalProbe(int row, int column, int direction){
    if (direction == 1){
        // check in the +ve diagonal direction; downwards and to the right
        if (row > ROWS - IN_A_ROW || column > COLUMNS - IN_A_ROW){
            // non-probable; not possible to result in a winning pattern
            return false;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (total_grid[row+i][column+i]){
                    if (opponent_grid[row+i][column+i]){
                        return false;
                    }
                }
            }
            return true;
        }
    }

    if (direction == -1){
        // check in the -ve direction; upwards and to the left
        if (row < IN_A_ROW - 1 || column < IN_A_ROW - 1){
            // non-probable; not possible to result in a winning pattern
            return false;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (total_grid[row-i][column-i]){
                    if (opponent_grid[row-i][column-i]){
                        return false;
                    }
                }
            }
            return true;
        }
    }
    // invalid direction
    return false;
}


bool FourInARowDuelsAI::antiDiagonalProbe(int row, int column, int direction){
    if (direction == 1){
        // check in the +ve diagonal direction; upwards and to the right
        if (row < IN_A_ROW - 1 || column > COLUMNS - IN_A_ROW){
            // non-probable; not possible to result in a winning pattern
            return false;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (total_grid[row-i][column+i]){
                    if (opponent_grid[row-i][column+i]){
                        return false;
                    }
                }
            }
            return true;
        }
    }

    if (direction == -1){
        // check in the -ve direction; downwards and to the left
        if (row > ROWS - IN_A_ROW || column < IN_A_ROW - 1){
            // non-probable; not possible to result in a winning pattern
            return false;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (total_grid[row+i][column-i]){
                    if (opponent_grid[row+i][column-i]){
                        return false;
                    }
                }
            }
            return true;
        }
    }
    // invalid direction
    return false;
}


bool FourInARowDuelsAI::probe(int &row, int &column, Orientation &orientation){
    switch (orientation.getName()){
    case 'H':
        return horizontalProbe(row, column, orientation.getDirection());
        break;
    case 'V':
        return verticalProbe(row, column, orientation.getDirection());
        break;
    case 'D':
        return diagonalProbe(row, column, orientation.getDirection());
        break;
    case 'A':
        return antiDiagonalProbe(row, column, orientation.getDirection());
        break;
    default:
        return false;
    }
}


void FourInARowDuelsAI::horizontalFill(int &played_column){
    if (horizontalProbe(root_cell[0], root_cell[1], direction)){
        std::cout<<"root_cell[0]: "<<root_cell[0]<<", root_cell[1]: "<<root_cell[1]<<", direction: "<<direction<<std::endl;
        if (direction == 1){
            for (int i=0; i < IN_A_ROW; i++){
                if (!total_grid[root_cell[0]][root_cell[1]+i]){
                    played_column = root_cell[1]+i;
                    break;
                }
            }
        }
        else {
            // direction will be -1, if it is not 1
            for (int i=0; i < IN_A_ROW; i++){
                if (!total_grid[root_cell[0]][root_cell[1]-i]){
                    played_column = root_cell[1]-i;
                    break;
                }
            }
        }
    }
    else{
        candidate_found = false;
        aiLevelTwo(played_column);
//        findCandidate();
    }
    std::cout<<"played_column: "<<played_column<<std::endl;
}


void FourInARowDuelsAI::verticalFill(int &played_column){
    if (verticalProbe(root_cell[0], root_cell[1], direction)){
        std::cout<<"root_cell[0]: "<<root_cell[0]<<", root_cell[1]: "<<root_cell[1]<<", direction: "<<direction<<std::endl;
        if (direction == 1){
            // you cannot fill downwards
        }
        else {
            // direction will be -1, if it is not 1
            for (int i=0; i < IN_A_ROW; i++){
                if (!total_grid[root_cell[0]-i][root_cell[1]]){
                    played_column = root_cell[1];
                    break;
                }
            }
        }
    }
    else{
        candidate_found = false;
        aiLevelTwo(played_column);
//        findCandidate();
    }
    std::cout<<"played_column: "<<played_column<<std::endl;
}


void FourInARowDuelsAI::diagonalFill(int &played_column){
    if (diagonalProbe(root_cell[0], root_cell[1], direction)){
        std::cout<<"root_cell[0]: "<<root_cell[0]<<", root_cell[1]: "<<root_cell[1]<<", direction: "<<direction<<std::endl;
        if (direction == 1){
            for (int i=0; i < IN_A_ROW; i++){
                if (!total_grid[root_cell[0]+i][root_cell[1]+i]){
                    played_column = root_cell[1]+i;
                    break;
                }
            }
        }
        else {
            // direction will be -1, if it is not 1
            for (int i=0; i < IN_A_ROW; i++){
                if (!total_grid[root_cell[0]-i][root_cell[1]-i]){
                    played_column = root_cell[1]-i;
                    break;
                }
            }
        }
    }
    else{
        candidate_found = false;
        aiLevelTwo(played_column);
//        findCandidate();
    }
    std::cout<<"played_column: "<<played_column<<std::endl;
}


void FourInARowDuelsAI::antiDiagonalFill(int &played_column){
    if (antiDiagonalProbe(root_cell[0], root_cell[1], direction)){
        std::cout<<"root_cell[0]: "<<root_cell[0]<<", root_cell[1]: "<<root_cell[1]<<", direction: "<<direction<<std::endl;
        if (direction == 1){
            for (int i=0; i < IN_A_ROW; i++){
                if (!total_grid[root_cell[0]-i][root_cell[1]+i]){
                    played_column = root_cell[1]+i;
                    break;
                }
            }
        }
        else {
            // direction will be -1, if it is not 1
            for (int i=0; i < IN_A_ROW; i++){
                if (!total_grid[root_cell[0]+i][root_cell[1]-i]){
                    played_column = root_cell[1]-i;
                    break;
                }
            }
        }
    }
    else{
        candidate_found = false;
        aiLevelTwo(played_column);
//        findCandidate();
    }
    std::cout<<"played_column: "<<played_column<<std::endl;
}


void FourInARowDuelsAI::fill(int &played_column, Orientation &orientation){
    switch (orientation.getName()){
    case 'H':
        horizontalFill(played_column);
        break;
    case 'V':
        verticalFill(played_column);
        break;
    case 'D':
        diagonalFill(played_column);
        break;
    case 'A':
        antiDiagonalFill(played_column);
        break;
    default:
        break;
    }
}









int FourInARowDuelsAI::horizontalProbeOpponent(int row, int column, int direction){
    int score = 1;
    if (direction == 1){
        // check in the +ve direction; to the right
        if (column > COLUMNS - IN_A_ROW){
            // non-probable; not possible to result in a winning pattern
            return 0;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (opponent_grid[row][column+i]){
                    score++;
                }
                if (my_grid[row][column+i]){
                    score = 0;
                    break;
                }
            }
            return score;
        }
    }

    if (direction == -1){
        // check in the -ve direction; to the left
        if (column < IN_A_ROW - 1){
            // non-probable; not possible to result in a winning pattern
            return 0;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (opponent_grid[row][column-i]){
                    score++;
                }
                if (my_grid[row][column-i]){
                    score = 0;
                    break;
                }
            }
            return score;
        }
    }
    return 0;
}


int FourInARowDuelsAI::verticalProbeOpponent(int row, int column, int direction){
    int score = 1;
    if (direction == 1){
        // check in the +ve direction; downwards
        if (row > ROWS - IN_A_ROW){
            // non-probable; not possible to result in a winning pattern
            return 0;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (opponent_grid[row+i][column]){
                    score++;
                }
                if (my_grid[row+i][column]){
                    score = 0;
                    break;
                }
            }
            return score;
        }
    }

    if (direction == -1){
        // check in the -ve direction; upwards
        if (row < IN_A_ROW - 1){
            // non-probable; not possible to result in a winning pattern
            return 0;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (opponent_grid[row-i][column]){
                    score++;
                }
                if (my_grid[row-i][column]){
                    score = 0;
                    break;
                }
            }
            return score;
        }
    }
    // invalid direction
    return 0;
}


int FourInARowDuelsAI::diagonalProbeOpponent(int row, int column, int direction){
    int score = 1;
    if (direction == 1){
        // check in the +ve diagonal direction; downwards and to the right
        if (row > ROWS - IN_A_ROW || column > COLUMNS - IN_A_ROW){
            // non-probable; not possible to result in a winning pattern
            return 0;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (opponent_grid[row+i][column+i]){
                    score++;
                }
                if (my_grid[row+i][column+i]){
                    score = 0;
                    break;
                }
            }
            return score;
        }
    }

    if (direction == -1){
        // check in the -ve direction; upwards and to the left
        if (row < IN_A_ROW - 1 || column < IN_A_ROW - 1){
            // non-probable; not possible to result in a winning pattern
            return 0;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (opponent_grid[row-i][column-i]){
                    score++;
                }
                if (my_grid[row-i][column-i]){
                    score = 0;
                    break;
                }
            }
            return score;
        }
    }
    // invalid direction
    return 0;
}


int FourInARowDuelsAI::antiDiagonalProbeOpponent(int row, int column, int direction){
    int score = 1;
    if (direction == 1){
        // check in the +ve diagonal direction; upwards and to the right
        if (row < IN_A_ROW - 1 || column > COLUMNS - IN_A_ROW){
            // non-probable; not possible to result in a winning pattern
            return 0;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (opponent_grid[row-i][column+i]){
                    score++;
                }
                if (my_grid[row-i][column+i]){
                    score = 0;
                    break;
                }
            }
            return score;
        }
    }

    if (direction == -1){
        // check in the -ve direction; downwards and to the left
        if (row > ROWS - IN_A_ROW || column < IN_A_ROW - 1){
            // non-probable; not possible to result in a winning pattern
            return 0;
        }
        else{
            for (int i = 1; i < IN_A_ROW; i++){
                if (opponent_grid[row+i][column-i]){
                    score++;
                }
                if (my_grid[row+i][column-i]){
                    score = 0;
                    break;
                }
            }
            return score;
        }
    }
    // invalid direction
    return 0;
}


int FourInARowDuelsAI::probeOpponent(int &row, int &column, Orientation &orientation){
    switch (orientation.getName()){
    case 'H':
        return horizontalProbeOpponent(row, column, orientation.getDirection());
        break;
    case 'V':
        return verticalProbeOpponent(row, column, orientation.getDirection());
        break;
    case 'D':
        return diagonalProbeOpponent(row, column, orientation.getDirection());
        break;
    case 'A':
        return antiDiagonalProbeOpponent(row, column, orientation.getDirection());
        break;
    default:
        return 0;
    }
}









Orientation::Orientation(){
    name = ' ';
    direction_or = 0;
    row_offset = 0;
    column_offset = 0;
}

void Orientation::correctDirection(int &direction_in){
    if (direction_in != 1 && direction_in != -1){
        direction_in = 1;
    }
}

void Orientation::setAsHorizontal(int direction_in){
    name = 'H';
    direction_or = direction_in;
    row_offset = 0;
    column_offset = direction_or;
}

void Orientation::setAsVertical(int direction_in){
    correctDirection(direction_in);
    name = 'V';
    direction_or = direction_in;
    row_offset = direction_or;
    column_offset = 0;
}

void Orientation::setAsDiagonal(int direction_in){
    correctDirection(direction_in);
    name = 'D';
    direction_or = direction_in;
    row_offset = direction_or;
    column_offset = direction_or;
}

void Orientation::setAsADiagonal(int direction_in){
    correctDirection(direction_in);
    name = 'A';
    direction_or = direction_in;
    row_offset = -1*direction_or;
    column_offset = direction_or;
}

int Orientation::getDirection(){
    return direction_or;
}

char Orientation::getName(){
    return name;
}

int Orientation::getRowOffset(){
    return row_offset;
}

int Orientation::getColumnOffset(){
    return column_offset;
}
