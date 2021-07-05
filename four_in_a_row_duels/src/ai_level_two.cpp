/* connectFour game using the duels package
 *
 * ECN Project (2020/2021 - Semester II)
 * Oluwapelumi WILLIAMS (IMARO II)
 * Adedamola SODE (IMARO I)
 *
 * Supervisor : Professor Olivier Kermogant
 *
 *
 * AI level 2.
 * The members and functions from the AI class (defined in four_in_a_row_duels_ai.h and implemented in
 * four_in_a_row_duels_ai.cpp are continued here for the AI level 4.
 * This is to properly separate code and not have too much code in one file (for readability and separation of thought.

 * File Name: ai_level_two.cpp
 * Definition File: four_in_a_row_duels_ai.h
 * Part Implementation in: four_in_a_row_duels.cpp
*/

// Note: this code can be improved by defining some of the variables in the header file, hence making them members of the entire ai object
// This would be so as to prevent the ai from instantiating these members every time the function is called.

#include <duels/four_in_a_row_duels/four_in_a_row_duels_ai.h>
using namespace duels::four_in_a_row_duels;

#include <iostream>

//void FourInARowDuelsAI::aiLevelTwo(int &played_column){
//    std::cout<<"candidate_found: ";
//    if (candidate_found){
//        std::cout<<"true"<<std::endl;
//    }
//    else{
//        std::cout<<"false"<<std::endl;
//    }

//    if (candidate_found){
//        fill(played_column, orientations[orientation_it]);
//    }
//    else{
//        do{
//            if (findCandidate()==true){
//                // do nothing extra. the needed action would have been done in the findCandidate() function
//                played_column = root_cell[1];
//                fill(played_column, orientations[orientation_it]);
//            }
//            else{
//                orientation_it++;

//                if (feasible_column_pool.size() == 0){
//                    played_column = column_pool[rand() % column_pool.size()];
//                    feasible_column_pool.resize(column_pool.size());
//                    std::copy(column_pool.begin(), column_pool.end(), feasible_column_pool.begin());
//                    resetOrientationCount();
//                    break;
//                }
//            }
//        }
//        while(!candidate_found);
//    }
//}


void FourInARowDuelsAI::aiLevelTwo(int &played_column){
    std::cout<<"candidate_found: ";
    if (candidate_found){
        std::cout<<"true"<<std::endl;
    }
    else{
        std::cout<<"false"<<std::endl;
    }
    do{
        if (candidate_found){
            fill(played_column, orientations[orientation_it]);
        }
        else{
            if (findCandidate()==true){
                // do nothing extra. the needed action would have been done in the findCandidate() function
                // played_column = root_cell[1];
                fill(played_column, orientations[orientation_it]);
            }
            else{
                orientation_it++;

                if (feasible_column_pool.size() == 0){
                    played_column = column_pool[rand() % column_pool.size()];
                    feasible_column_pool.resize(column_pool.size());
                    std::copy(column_pool.begin(), column_pool.end(), feasible_column_pool.begin());
                    resetOrientationCount();
                    break;
                }
            }
        }
    }
    while(!candidate_found);
}
