#ifndef CONNECTFOUR_GAMEGRID_H
#define CONNECTFOUR_GAMEGRID_H

#include <vector>
#include <iostream>

namespace duels {
namespace four_in_a_row_duels{

class GameGrid {
    private:
      const int ROWS;
      const int COLUMNS;
      char empty_token;
      std::vector<std::vector<char>> grid;

      std::vector<std::vector<char>> getGrid();

      void resetGrid();
      void resetGrid(int rowIn, int columnIn);

    public:

      GameGrid(int rowIn=6, int columnIn=8);

      // void setRows(int rowIn);
      // void setColumns(int columnIn);

      int getRows() const;
      int getColumns() const;

      void setCell(int row_in, int column_in, char token_in);
      char getCell(int row_in, int column_in) const;

      void printGrid();
};
}}

#endif
