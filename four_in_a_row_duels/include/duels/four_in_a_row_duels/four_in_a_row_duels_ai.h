#ifndef FOUR_IN_A_ROW_DUELS_AI_H
#define FOUR_IN_A_ROW_DUELS_AI_H

#include <duels/player.h>
#include <duels/four_in_a_row_duels/msg.h>
#include <stdlib.h> // random number generation
#include <time.h>
#include <algorithm>

#include <iostream>

namespace duels {
namespace four_in_a_row_duels {


// orientation class
class Orientation{
private:
    char name;
    int direction_or;
    int row_offset;
    int column_offset;

    void correctDirection(int &direction_in);

public:
    Orientation();
    void setAsHorizontal(int direction_in);
    void setAsVertical(int direction_in);
    void setAsDiagonal(int direction_in);
    void setAsADiagonal(int direction_in);

    char getName();
    int getDirection();
    int getRowOffset();
    int getColumnOffset();
};





// built-in AI class, should be heavily adapted to your needs
class FourInARowDuelsAI : public duels::Player<Input, Feedback>
{
public:
  FourInARowDuelsAI(int difficulty = 1) : difficulty(difficulty) {}

  void updateInput();

private:
  int difficulty = 1;

  int ROWS = 6; // edit: we have to find a way to pass the row values from the grid generated in the mechanics file
  int COLUMNS = 8; // edit: we have to find a way to pass the column values from the grid generated in the mechanics file

  std::vector<int> column_pool; // vector containing the columns that we can play in
  std::vector<int> feasible_column_pool; // vector containing the columns that can result in a winning result

  const bool EMPTY_TOKEN = false;
  bool ai_initialized = false;
  std::vector<std::vector<bool>> my_grid;
  std::vector<std::vector<bool>> opponent_grid;
  std::vector<std::vector<bool>> total_grid;


  // Data members for the advanced AI levels
  int IN_A_ROW = 4; // how many tokens to be in a row to win
  bool candidate_found = false; // boolean for a candidate for the root_cell (if a candidate has been found)
  int direction;
  std::vector<int> root_cell = {-1, -1}; // vector containing 2 elements (row and column), for use as the current root_cell
  std::vector<int> opp_root_cell = {-1, -1};

  std::vector<Orientation> orientations; // orientation instances
  // std::vector<int> play_queue; // a queue for AI level 3 and beyond - to put the columns that should be played in order of priority.
  // change to name to play_stack
  int play_next = -1;
  int orientation_it; // iterator for orientation vector - for AI level 2
  int orientation_it_opp; // opponent's iterator for the orientation vector - for AI level 3

  void initializeAI();
  void initializeGrids();
  void resetOrientationCount();
  void updateGrids();
  int getTopmostRow(int column);

  //void initPlayQueue();

  void aiLevelOne(int &played_column);
  void aiLevelTwo(int &played_column);
  void aiLevelThree(int &played_column);

  // functions for the advanced AI levels
  bool findCandidate();
  bool horizontalProbe(int row, int column, int direction);
  bool verticalProbe(int row, int column, int direction);
  bool diagonalProbe(int row, int column, int direction);
  bool antiDiagonalProbe(int row, int column, int direction);
  bool probe(int &row, int &column, Orientation &orientation);

  void horizontalFill(int &played_column);
  void verticalFill(int &played_column);
  void diagonalFill(int &played_column);
  void antiDiagonalFill(int &played_column);
  void fill(int &played_column, Orientation &orientation);

  int horizontalProbeOpponent(int row, int column, int direction);
  int verticalProbeOpponent(int row, int column, int direction);
  int diagonalProbeOpponent(int row, int column, int direction);
  int antiDiagonalProbeOpponent(int row, int column, int direction);
  int probeOpponent(int &row, int &column, Orientation &orientation);



};
}
}
#endif
