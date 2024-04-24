// Conway's Game of Life
/*
1. Any live cell with fewer than two live neighbors dies, as if by underpopulation.
2. Any live cell with two or three live neighbors lives on to the next generation.
3. Any live cell with more than three live neighbors dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/
#include <iostream> // Do I want to do this in C or C++?
#include <stdlib.h> 
#include <time.h>

#define G_DIM 50

void printBoard(int grid[G_DIM][G_DIM], int tick) {
    std::cout << "Tick: " << tick << std::endl;
    for (int i = 0; i < G_DIM; i++){
        for (int j = 0; j < G_DIM; j++) {
            if (grid[i][j]) std::cout << "+";
            else std::cout << "-";         
        }
        std::cout << std::endl;
    }
}

// Get number of live neighbours for a cell
int countNeighbours(int grid[G_DIM][G_DIM], int x, int y) {
    int alive = 0;
    int offsets[8][2] =  {{-1,-1}, {-1, 0}, {-1, 1}, {0,-1}, {0,1}, {1, -1}, {1,0}, {1, 1}};

    for (int i = 0; i < 8; i++){
        int x_o = x + offsets[i][0]; 
        int y_o = y + offsets[i][1];

        if (x_o < 0 || x_o >= G_DIM || y_o < 0 || y_o >= G_DIM) continue;
        alive += grid[x_o][y_o];
    }
    return alive;
}

// Function to copy the contents of one grid into another, feels inefficient
void copyGrid(int source[][G_DIM], int destination[][G_DIM]) {
    for (int i = 0; i < G_DIM; ++i) {
        for (int j = 0; j < G_DIM; ++j) {
            destination[i][j] = source[i][j];
        }
    }
}

void initRandom(int grid[][G_DIM]) {
    srand(time(NULL));
    for (int i = 0; i < G_DIM; i++) {
        for (int j = 0; j < G_DIM; j++) {
            // Generate a random number between 0 and 1
            grid[i][j] = rand() % 2;
        }
    }
}

int updateGrid(int grid[][G_DIM]) {
    // Update Rules
    int next[G_DIM][G_DIM] = {0};
    int g_size = 0;
    for (int i = 0; i < G_DIM; i++){
        for (int j = 0; j < G_DIM; j++) {
            int live_n = countNeighbours(grid, i, j);
            if ((grid[i][j] && (live_n == 2 || live_n == 3)) || (!grid[i][j] && (live_n == 3))) { // Is alive
                next[i][j] = 1;
                g_size++;
            }
        }
    }
    copyGrid(next, grid);
    return g_size;
}

int main () {
    int step = 0;
    int g_size = 1;
    int grid[G_DIM][G_DIM] = {0};
    initRandom(grid);

    // Main Loop
    while (true && g_size > 0) { // Run until converges (if it will)
        printBoard(grid, step); // Replace with visual
        updateGrid(grid);
        step++;
    }
    printBoard(grid, step);
    return 0;
}