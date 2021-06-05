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

using namespace duels::four_in_a_row_duels;

void FourInARowDuelsAI::updateInput(){
    if (!ai_initialized){
        initializeAI();
    }
    // check the size of the feedback (which is a vector of played cells) i.e. condition where no one has played before
    if (feedback.played_cells.size() == 0){
        // no one has played yet
    }
    else{
        // use the feedback provided to update the grids
        reconstructGrids();
    }

    int played_column; // Input that will be sent from the AI back to the server;

    // check if the entire grid is filled. (This is not needed as it will be handled by the server, but for a complete code, we add it)
    if ((int)feedback.played_cells.size() == ROWS * COLUMNS){
        // grid is filled. no input to send
    }
    else{
        do{
            played_column = column_pool[rand() % column_pool.size()];
        }
        while(total_grid[0][played_column] == true);

        /* calculate the corresponding row in which the column will be filled
         * note: we are not using the computation from the mechanics, we are computing independently
         * to give a uniform played row, we might have to modify the feedback parameter
        */

        int played_row = -1; // initialized to -1 to prevent compiler warning, but ideally, there's no way this value will be used.
        for (int i = ROWS-1; i >= 0; i--){
            if (!total_grid[i][played_column]){
                played_row = i;
                break;
            }
        }

        // update the AI's 'my_filled_cells' variable, and the 'total_filled_cells' variable
        // note this is just to maybe compute ahead. The next call to this AI will initialize it again, as the AI is not an object.
        my_grid[played_row][played_column] = true;
        total_grid[played_row][played_column] = true;

        input.played_column = played_column; // note the played column must both be within bounds, and not be played in an already filled up column. Hence the checks above.
    }
}

void FourInARowDuelsAI::initializeAI(){
    initializeGrids();
    for (int i = 0; i < COLUMNS; i++)
    {
        column_pool.push_back(i);
    }
    ai_initialized = true;
}


void FourInARowDuelsAI::initializeGrids(){
    my_grid.assign(ROWS, std::vector<bool> (COLUMNS, EMPTY_TOKEN));
    opponent_grid.assign(ROWS, std::vector<bool> (COLUMNS, EMPTY_TOKEN));
    total_grid.assign(ROWS, std::vector<bool> (COLUMNS, EMPTY_TOKEN));
}


void FourInARowDuelsAI::reconstructGrids(){
    int played_cells = feedback.played_cells.size();
    for (int i = 0; i < played_cells; i++){
        if (feedback.played_cells[i].player == 0){
            // this was played by me
            my_grid[feedback.played_cells[i].row][feedback.played_cells[i].column] = true;
        }
        else{
            // feedback.played_cells[i].player == 1, hence this was played by my opponent
            opponent_grid[feedback.played_cells[i].row][feedback.played_cells[i].column] = true;
        }
        // update the total_grid
        total_grid[feedback.played_cells[i].row][feedback.played_cells[i].column] = true;
    }
}
