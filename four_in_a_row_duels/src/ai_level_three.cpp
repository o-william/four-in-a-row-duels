/* connectFour game using the duels package
 *
 * ECN Project (2020/2021 - Semester II)
 * Oluwapelumi WILLIAMS (IMARO II)
 * Adedamola SODE (IMARO I)
 *
 * Supervisor : Professor Olivier Kermogant
 *
 *
 * AI level 3.
 * The members and functions from the AI class (defined in four_in_a_row_duels_ai.h and implemented in
 * four_in_a_row_duels_ai.cpp are continued here for the AI level 4.
 * This is to properly separate code and not have too much code in one file (for readability and separation of thought.

 * File Name: ai_level_three.cpp
 * Definition File: four_in_a_row_duels_ai.h
 * Part Implementation in: four_in_a_row_duels.cpp
*/

// Note: this code can be improved by defining some of the variables in the header file, hence making them members of the entire ai object
// This would be so as to prevent the ai from instantiating these members every time the function is called.

#include <duels/four_in_a_row_duels/four_in_a_row_duels_ai.h>
using namespace duels::four_in_a_row_duels;

#include <iostream>

void FourInARowDuelsAI::aiLevelThree(int &played_column){
    if (feedback.played_cells.size() < 1){
        aiLevelTwo(played_column);
    }

    else{
        if (play_next != -1){
            if (getTopmostRow(play_next) < ROWS - 1){
                if (total_grid[getTopmostRow(play_next)+1][play_next]){
                    played_column = play_next;
                    play_next = -1;
                    std::cout<<"opponent's column to block: "<<played_column<<std::endl;
                }
                else{
                    aiLevelTwo(played_column);
                }
            }
            else{
                played_column = play_next;
                play_next = -1;
                std::cout<<"opponent's column to block: "<<played_column<<std::endl;
            }
        }

        else{
            int opponent_score;
            int total_checks = 0;
            for(int i = ROWS-1; i >= 0; i--){
                for(int j = 0; j < COLUMNS; j++){
                    opp_root_cell[0] = i;
                    opp_root_cell[1] = j;

                    if(opponent_grid[opp_root_cell[0]][opp_root_cell[1]]){
                        total_checks++;
                        for (int k = 0; k < int(orientations.size()); k++){
                            orientation_it_opp = k;
                            opponent_score = probeOpponent(opp_root_cell[0], opp_root_cell[1], orientations[orientation_it_opp]);
                            if (opponent_score == IN_A_ROW - 1){
                                break;
                            }
                            // you will have to change this code to allow for all directions to be chekced and then put into the stack that determines priority
                        }

                        if (opponent_score == IN_A_ROW - 1){
                            //very close for the opponent to win
                            for (int k = 1; k < IN_A_ROW; k++){
                                if (!opponent_grid[opp_root_cell[0]+k*orientations[orientation_it_opp].getRowOffset()][opp_root_cell[1]+k*orientations[orientation_it_opp].getColumnOffset()]){
                                    play_next = opp_root_cell[1]+k*orientations[orientation_it_opp].getColumnOffset();

                                    if (getTopmostRow(play_next) < ROWS - 1){
                                        if (my_grid[getTopmostRow(play_next)+1][play_next]){
                                            // this means I have already blocked this position
                                            play_next = -1;
                                        }
                                        break;
                                    }
                                    else{
                                        if (my_grid[ROWS - 1][play_next]){
                                            // this means I have already blocked this position
                                            play_next = -1;
                                        }
                                        break;
                                    }
                                    // this will only be valid for 1. to have multiple blockages, use a queue and add them to the queue;
                                }
                            }
                        }
                    }

                    if (play_next!=-1 || total_checks == int(feedback.played_cells.size())){
                        break;
                    }
                }
                if (play_next!=-1 || total_checks == int(feedback.played_cells.size())){
                    break;
                }
            }


            if (opponent_score == IN_A_ROW - 1){
                if (getTopmostRow(play_next) < ROWS - 1){
                    if (total_grid[getTopmostRow(play_next)+1][play_next]){
                        played_column = play_next;
                        play_next = -1;
                        std::cout<<"opponent's column to block: "<<played_column<<std::endl;
                    }
                    else{
                        aiLevelTwo(played_column);
                    }
                }
                else{
                    played_column = play_next;
                    play_next = -1;
                    std::cout<<"opponent's column to block: "<<played_column<<std::endl;
                }

            }

            else{
                aiLevelTwo(played_column);
            }
        }
    }
}
