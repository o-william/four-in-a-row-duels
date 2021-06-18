// Client #1
#include <duels/four_in_a_row_duels/game.h>
#include <iostream>
#include <vector>

using namespace duels::four_in_a_row_duels;

//void initGrids(std::vector<std::vector<bool>> &my_grid, std::vector<std::vector<bool>> &opponent_grid, std::vector<std::vector<bool>> &total_grid);
int main(int argc, char** argv)
{
  
  Game game(argc, argv, "CLIENT 01", 1);    // to play as player 1 against level 1 AI
  //Game game(argc, argv, "your name", -2);    // to play as player 2 against level 2 AI

  Input input;
  Feedback feedback;
  const auto timeout = game.timeout_ms();

//  std::vector<std::vector<bool>> my_grid;
//  std::vector<std::vector<bool>> opponent_grid;
//  std::vector<std::vector<bool>> total_grid;
//  initGrids(my_grid, opponent_grid, total_grid);

  while(game.get(feedback))
  {
//      int played_cells = feedback.played_cells.size();
//      for(int i = 0; i<played_cells; i++){
//          std::cout<<"Last Cell: "<<feedback.played_cells[i].row<<", "<<feedback.played_cells[i].column;
//          std::cout<<std::endl;
//      }

//    // write input in less than timeout
//    // reconstruct total_grid
//      int total_plays = feedback.played_cells.size();
//      int current_row, current_column;

//      // update the total_grid
//      for (int i = 0; i < total_plays; i++){
//          current_row = feedback.played_cells[i].row;
//          current_column = feedback.played_cells[i].column;
//          if (!total_grid[current_row][current_column]){
//              total_grid[current_row][current_column] = true;
//          }

//          // choose columns to play in
//          for (int i = 0; i < 8; i++){
//              if(!total_grid[0][i]){
//                  input.played_column = i;
//                  game.send(input);
//              }
//          }
//      }
     input.played_column = 1;
     game.send(input);
  }
}

//void initGrids(std::vector<std::vector<bool>> &my_grid, std::vector<std::vector<bool>> &opponent_grid, std::vector<std::vector<bool>> &total_grid){
//    const int ROWS = 6;
//    const int COLUMNS = 8;
//    const bool EMPTY_TOKEN = false;

//    // initialize the grids to a 6x8 size. Note that we should find a way of passing this from the server, as opposed to manually inputting it.
//    my_grid.assign(ROWS, std::vector<bool> (COLUMNS, EMPTY_TOKEN));
//    opponent_grid.assign(ROWS, std::vector<bool> (COLUMNS, EMPTY_TOKEN));
//    total_grid.assign(ROWS, std::vector<bool> (COLUMNS, EMPTY_TOKEN));
//}
