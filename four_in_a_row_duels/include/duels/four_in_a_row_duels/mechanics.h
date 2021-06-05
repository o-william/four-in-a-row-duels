#ifndef FOUR_IN_A_ROW_DUELS_MECHANICS_H
#define FOUR_IN_A_ROW_DUELS_MECHANICS_H

#include <duels/four_in_a_row_duels/msg.h>
#include <duels/four_in_a_row_duels/game_grid.h>
#include <iostream>
#include <vector>

using namespace duels::four_in_a_row_duels;

// base mechanics class, should be heavily adapted to reflect the game rules
class FourInARowDuelsMechanics
{
public:
    FourInARowDuelsMechanics();
    InitDisplay initGame() {return {};}
    inline const Display& display() const {return display_msg;}
    
    void buildPlayerFeedback(Feedback &feedback, [[maybe_unused]] bool player_1_turn);
    void play(int column_in, bool player_1_turn);
    bool checkWinner();
    bool checkDraw();

private:
  Display display_msg;
  GameGrid game_grid;
  int ROWS; // edit: instead of generating the default 6 x 8, we need to find a way to specify the row and column values in server.cpp, and use that here
  int COLUMNS;
  int IN_A_ROW;
  const char PLAYER_1_TOKEN = 'A';
  const char PLAYER_2_TOKEN = 'B';
  const char EMPTY_TOKEN = ' ';

  int total_moves;
  bool game_won;

  bool withinBounds(int column_in) const;
  bool columnFilled(int column_in) const;
  bool cellFilled(int row_in, int column_in) const;
  int getTopmostRow(int column_in) const;

  bool horizontalSequence();
  bool verticalSequence();
  bool diagonalSequence();
  bool antiDiagonalSequence();
};

#endif 
