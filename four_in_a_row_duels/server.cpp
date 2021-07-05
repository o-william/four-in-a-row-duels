/* connectFour game using the duels package
 *
 * ECN Project (2020/2021 - Semester II)
 * Oluwapelumi WILLIAMS (IMARO II)
 * Adedamola SODE (IMARO I)
 *
 * Supervisor : Professor Olivier Kermogant
 *
 *
 * Implementation File of the game Server (contains "main")
 * File Name: server.cpp
 * Definition File: server.h (non-writeable)
*/


#include <duels/server.h>
#include <duels/four_in_a_row_duels/msg.h>
#include <duels/four_in_a_row_duels/four_in_a_row_duels_ai.h>
#include <duels/four_in_a_row_duels/mechanics.h>


using namespace duels::four_in_a_row_duels;
using duels::Result;
using duels::Timeout;
using duels::Refresh;
using GameIO = duels::Server<InitDisplay, Input, Feedback, Display>;

int main(int argc, char** argv)
{
  const int ROWS = 6;
  const int COLUMNS = 8;

  GameIO game_io("four_in_a_row_duels", Refresh(300), Timeout(100));
  
  // simulation time
  [[maybe_unused]] const double dt(game_io.samplingTime());

  // TODO prepare game state / init message (for display)
  FourInARowDuelsMechanics mechanics;
  InitDisplay init = mechanics.initGame();

  init.rows = ROWS;
  init.columns = COLUMNS;

  // inform displays and get players (no multithread by default for simultaneous games)
  const auto [player1, player2] = game_io.initPlayers<FourInARowDuelsAI>(argc, argv, init, 2, 3, false); {}


  bool player1_turn(true);
  while(game_io.running())
  {
    // adapt to who is playing
    auto [current, opponent] = game_io.newTurn(player1_turn);

    // extract feedback for the current player
    mechanics.buildPlayerFeedback(current->feedback, player1_turn);

    // get their action / exit if they have crashed or timeout
    if(!game_io.sync(current))
      break;

    // TODO update game mechanics (display, winning conditions) from current->input
    // up to you!
    mechanics.play(current->input.played_column, player1_turn);

    game_io.sendDisplay(mechanics.display());

    if (mechanics.checkWinner()){
        game_io.registerVictory(current);
        if (player1_turn){
            game_io.endsWith(Result::P1_WINS);
        }
        else{
            game_io.endsWith(Result::P2_WINS);
        }
    }
    if (mechanics.checkDraw()){
        game_io.registerDraw();
    }

    // TODO check if any regular winner after this turn
    //if(...)
    {
      /* depending on the rules, you may use:
      game_io.registerVictory(current);
      game_io.registerVictory(opponent);
      game_io.registerDraw();
      game_io.endsWith(Result::P1_WINS);
      game_io.endsWith(Result::P2_WINS);
      */
    }

    // switch player
    player1_turn = !player1_turn;
  }

  // send final result to players and display
  game_io.sendResult(mechanics.display());
}
