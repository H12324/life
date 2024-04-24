// Conway's Game of Life
/*
1. Any live cell with fewer than two live neighbors dies, as if by underpopulation.
2. Any live cell with two or three live neighbors lives on to the next generation.
3. Any live cell with more than three live neighbors dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/
#include <iostream> // Do I want to do this in C or C++?

#define G_DIM 10

void printBoard(int grid[G_DIM][G_DIM]) {
    for (int i = 0; i < G_DIM; i++){
        for (int j = 0; j < G_DIM; j++) {
            if (grid[i][j]) std::cout << "+";
            else std::cout << "-";         
        }
        std::cout << std::endl;
    }
}

int countNeighbours(int grid[G_DIM][G_DIM], int x, int y) {
    // Get number of live neighbours for a cell
    
}

int main () {
    int grid[G_DIM][G_DIM] = {0};
    // Basic Tetromino Test
    grid[1][0] = 1; grid[0][1] = 1; grid[0][2]=1;
    // Main Loop
    int step = 0;
    while (true) {
    //
    printBoard(grid);
    // Update Rules
    for (int i = 0; i < G_DIM; i++){
        for (int j = 0; j < G_DIM; j++) {
            
        }
    }
    break;
    step++;
    }
    return 0;
}