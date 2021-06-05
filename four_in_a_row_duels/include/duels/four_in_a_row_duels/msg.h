// generated from four_in_a_row_duels.yaml -- editing this file by hand is not recommended
#ifndef FOUR_IN_A_ROW_DUELS_MSG_H
#define FOUR_IN_A_ROW_DUELS_MSG_H
#include <sstream>
#include <duels/game_state.h>
#include <duels/stream_overloads.h>
namespace duels {
namespace four_in_a_row_duels {

// utility structures
struct Cell
{
  int row;int column;int player;
  inline bool operator==(const Cell &other) const
  {
    return row == other.row && column == other.column && player == other.player;
  }
};
}}

//detail on how to stream these structures
#include <duels/four_in_a_row_duels/msg_detail.h>

// core game messages
namespace duels {
namespace four_in_a_row_duels {

struct InitDisplay
{
  int rows; int columns;
  std::string toYAMLString(std::string name1, std::string name2) const 
  {
    std::stringstream ss;
    ss << "name1: " << name1;
    ss << "\nname2: " << name2;
    ss << "\nrows: " << rows;
    ss << "\ncolumns: " << columns;
    return ss.str();
  }
};

struct Input
{
  int played_column;
  std::string toString() const 
  {
    std::stringstream ss;
    ss << "played_column: " << played_column;
    return ss.str();
  }
};

struct Feedback
{
  std::vector<Cell> played_cells;
  std::string toString() const 
  {
    std::stringstream ss;
    ss << "played_cells: " << played_cells;
    return ss.str();
  }
  State __state;
};

struct Display
{
  Cell last_played_cell;
  std::string toYAMLString(Result result) const 
  {
    std::stringstream ss;
    ss << "result: " << result;
    ss << "\nlast_played_cell: " << last_played_cell;
    return ss.str();
  }
};

}}
#endif