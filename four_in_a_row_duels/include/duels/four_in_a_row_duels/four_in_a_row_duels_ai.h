#ifndef FOUR_IN_A_ROW_DUELS_AI_H
#define FOUR_IN_A_ROW_DUELS_AI_H

#include <duels/player.h>
#include <duels/four_in_a_row_duels/msg.h>
#include <stdlib.h> // random number generation

namespace duels {
namespace four_in_a_row_duels {

// built-in AI class, should be heavily adapted to your needs
class FourInARowDuelsAI : public duels::Player<Input, Feedback>
{
public:
  FourInARowDuelsAI(int difficulty = 1) : difficulty(difficulty) {}

  void updateInput();

private:
  int difficulty = 1;

  const int SEED = 5;
  int ROWS = 6; // edit: we have to find a way to pass the row values from the grid generated in the mechanics file
  int COLUMNS = 8; // edit: we have to find a way to pass the column values from the grid generated in the mechanics file

  std::vector<int> column_pool; // vector containing the columns that we can play in

  bool EMPTY_TOKEN = false;
  bool ai_initialized = false;
  std::vector<std::vector<bool>> my_grid;
  std::vector<std::vector<bool>> opponent_grid;
  std::vector<std::vector<bool>> total_grid;

  void initializeAI();
  void initializeGrids();
  void reconstructGrids();

};
}
}
#endif
