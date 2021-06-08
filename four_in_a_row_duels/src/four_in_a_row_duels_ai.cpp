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
        // call the appropriate AI using switch-case
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

        // update the AI's 'my_filled_cells' variable, and the 'total_filled_cells' variable.
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


void FourInARowDuelsAI::updateGrids(){
    int played_cells = feedback.played_cells.size();
    // update opponent grid with the last vector in the feedback
    opponent_grid[feedback.played_cells[played_cells-1].row][feedback.played_cells[played_cells-1].column] = true;
    total_grid[feedback.played_cells[played_cells-1].row][feedback.played_cells[played_cells-1].column] = true;
}
