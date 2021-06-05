#ifndef FOUR_IN_A_ROW_DUELS_GAME_H
#define FOUR_IN_A_ROW_DUELS_GAME_H
#include <duels/client.h>
#include <duels/four_in_a_row_duels/msg.h>
#include <sstream>
namespace duels {
namespace four_in_a_row_duels {
class Game: public duels::Client<Input, Feedback>
{
public:
  Game(int argc, char** argv, std::string name, int difficulty = 1)
    : Game(argc, argv, name, difficulty, "localhost") {}
  Game(int argc, char** argv, std::string name, std::string ip, int difficulty = 1)
      : Game(argc, argv, name, difficulty, ip) {}
private:
  Game(int argc, char** argv, std::string name, int difficulty, std::string ip)
      : duels::Client<Input, Feedback>(
      argc, argv, 100, 20000, name, difficulty, ip, "four_in_a_row_duels") {}
};
}
}
#endif