/* connectFour game using the duels package
 *
 * ECN Project (2020/2021 - Semester II)
 * Oluwapelumi WILLIAMS (IMARO II)
 * Adedamola SODE (IMARO I)
 *
 * Supervisor : Professor Olivier Kermogant
 *
 *
 * Implementation File of the "FourInARowDuelsMechanics" class
 * File Name: mechanics.cpp
 * Definition File: mechanics.h
*/

#include <duels/four_in_a_row_duels/mechanics.h>

FourInARowDuelsMechanics::FourInARowDuelsMechanics() {
    ROWS = game_grid.getRows();
    COLUMNS = game_grid.getColumns();
    IN_A_ROW = 4;
    total_moves = 0;
    game_won = false;
}


void FourInARowDuelsMechanics::buildPlayerFeedback(Feedback &feedback, [[maybe_unused]] bool player_1_turn)
{
    // Feedback is a vector of type "Cell" called played_cells.
    // This does not take into account the situation where a player object skips its turn
    if (total_moves == 0){
        // no one has played yet
    }
    else{
        // append the current player's feedback with the last played cell of the opponent using display_msg.last_played_cell
        // this sends the opponent's played cells to the current player as feedback
        feedback.played_cells.push_back(display_msg.last_played_cell);
    }
    //std::cout<<"Total cells in feedback: "<<feedback.played_cells.size()<<std::endl;
}


void FourInARowDuelsMechanics::play(int column_in, bool player_1_turn){
    if (withinBounds(column_in)){
        if (!columnFilled(column_in)){
            int row = getTopmostRow(column_in);
            if (player_1_turn){
                game_grid.setCell(row, column_in, PLAYER_1_TOKEN);
            }
            else{
                game_grid.setCell(row, column_in, PLAYER_2_TOKEN);
            }

            total_moves += 1;

            // edit display_msg by adding the new cell
            Cell new_cell;
            new_cell.row = row;
            new_cell.column = column_in;
            display_msg.last_played_cell = new_cell;
            if (player_1_turn){
                display_msg.last_played_cell.player = 1;
                // cell was played by player 1
            }
            else{
                display_msg.last_played_cell.player = 2;
                // cell was played by player 2
            }
        }
        else{
            // display an appropriate error: COLUMN IS FILLED, PLAY AGAIN
        }
    }
    else{
        // display an appropriate error: INPUT IS OUT OF BOUNDS
    }
    std::cout<<"Total Moves: "<<total_moves<<std::endl;
    game_grid.printGrid();
    std::cout<<std::endl;
}


// Function to check if the entered column is within the bounds
bool FourInARowDuelsMechanics::withinBounds(int column_in) const{
    if (column_in >= 0 && column_in < COLUMNS){
        return true;
    }
    else{
        return false;
    }
}


// Function to check if a column is filled
bool FourInARowDuelsMechanics::columnFilled(int column_in) const{
    if (cellFilled(0, column_in)){
        return true;
    }
    else{
        return false;
    }
}


// Function to check if a cell is filled (This can be implemented in the game_grid class, instead of here)
bool FourInARowDuelsMechanics::cellFilled(int row_in, int column_in) const{
    if (game_grid.getCell(row_in, column_in) != EMPTY_TOKEN){
        return true;
    }
    else{
        return false;
    }
}


// Function to get the topmost unfilled row for a specified column
// Does not return anything (for now) if the entire column is filled
int FourInARowDuelsMechanics::getTopmostRow(int column_in) const{
    for (int i = ROWS-1; i >= 0; i--){
        if (!cellFilled(i, column_in)){
            return i;
        }
    }
    return -1;
}


bool FourInARowDuelsMechanics::horizontalSequence(){
    // Check horizontal direction if we have a four in a row
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < (COLUMNS-IN_A_ROW + 1); j++){
            if (cellFilled(i,j)){
                char current_cell = game_grid.getCell(i,j);

                for (int k = 1; k < IN_A_ROW; k++){
                    if (game_grid.getCell(i, j+k) == current_cell){
                        if (k == 3){
                            return true;
                        }
                        continue;
                        /* Potential way to improve this form of four-in-a-row check (also applies to other directions i.e. checking functions below this one)
                        * Find a way to store the position of the column (or row or diagonal, in the below cases,) that triggered the "break" in the current loop, and start from there in the next iteration, instead of starting from the next integer once the "break" is triggered.
                        * Also, this algorithm is not the best (all four checking directions). This is because the game is not played by entering both row and column, but by column only, hence, you don't need to check from the top (where the filling of tokens is certain not to start from).
                        * A better algorithm will start the check from the bottom and stop when an empty cell is encountered.
                        */
                    }
                    break;
                }
            }
        }
    }
    return false;
}


bool FourInARowDuelsMechanics::verticalSequence(){
    // Check vertical direction if we have a four in a row
    for (int i = 0; i < COLUMNS; i++){
        for (int j = 0; j < (ROWS-IN_A_ROW + 1); j++){
            if (cellFilled(j,i)){
                char current_cell = game_grid.getCell(j,i);

                for (int k = 1; k < IN_A_ROW; k++){
                    if (game_grid.getCell(j+k, i) == current_cell){
                        if (k == 3){
                            return true;
                        }
                        continue;
                    }
                    break;
                }
            }
        }
    }
    return false;
}


bool FourInARowDuelsMechanics::diagonalSequence(){
    // Check diagonal direction if we have a four in a row
    for (int i = 0; i < (ROWS-IN_A_ROW + 1); i++){
        for (int j = 0; j < (COLUMNS-IN_A_ROW + 1); j++){
            if (cellFilled(i,j) == true){
                char current_cell = game_grid.getCell(i,j);

                for (int k = 1; k < IN_A_ROW; k++){
                    if (game_grid.getCell(i+k, j+k) == current_cell){
                        if (k == 3){
                            return true;
                            // The comment made in the "fourHorizontal" function will be more challenging for this function. Think about it before you attempt to implement a more elegant and efficient version
                        }
                        continue;
                    }
                    break;
                }
            }
        }
    }
    return false;
}


bool FourInARowDuelsMechanics::antiDiagonalSequence(){
    // Check diagonal direction if we have a four in a row
    // This algorithm starts checking from the bottom-up
    for (int i = ROWS - 1; i >= IN_A_ROW - 1; i--){
        for (int j = 0; j < COLUMNS - IN_A_ROW + 1; j++){
            if (cellFilled(i,j) == true){
                char current_cell = game_grid.getCell(i,j);

                for (int k = 1; k < IN_A_ROW; k++){
                    if (game_grid.getCell(i-k, j+k) == current_cell){
                        if (k == 3){
                            return true;
                            // The comment in the "fourDiagonal" function also applies here.
                        }
                        continue;
                    }
                    break;
                }
            }
        }
    }
    return false;
}


bool FourInARowDuelsMechanics::checkWinner(){
    if ((total_moves > 4) && (horizontalSequence() || verticalSequence() || diagonalSequence() || antiDiagonalSequence())){
        // WINNER FOUND
        game_won = true;
    }
    return game_won;
}

bool FourInARowDuelsMechanics::checkDraw(){
    if ((!game_won) && (total_moves == ROWS * COLUMNS)){
        return true;
    }
    return false;
}

