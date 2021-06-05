// Test file for game_grid class

#include <iostream>
#include <vector>
#include <duels/four_in_a_row_duels/game_grid.h>

using namespace std;
using namespace duels::four_in_a_row_duels;

int main(){
    // Create a new gamegrid object. Note the initialization
    GameGrid game_grid;

    // Print the data members
    int grid_rows = game_grid.getRows();
    int grid_columns = game_grid.getColumns();

    cout<<"Rows: "<<grid_rows<<endl;
    cout<<"Columns: "<<grid_columns<<endl;

    cout<<endl;
    cout<<"Print the Grid"<<endl;
    game_grid.printGrid();

    cout<<endl;
    vector<vector<char>> game_grid_grid = game_grid.getGrid();

    cout<<endl;
    cout<<"Get the characters in each cell of the grid"<<endl;
    for (int i=0; i<grid_rows; i++){
        for (int j = 0; j<grid_columns; j++){
            cout<<"Row "<<i+1<<", Column "<<j+1<<": '"<<game_grid_grid[i][j]<<"'"<<endl;
        }
    }

    return 0;
}
