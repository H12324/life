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
#include "SDL.h"

#define G_DIM 80

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;//600;
const int CELL_SIZE = 10;
const int GRID_WIDTH = SCREEN_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;
const int ALIVE_COLOR = 0x000000;
const int DEAD_COLOR = 0xFFFFFF;

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

// Function to draw the grid
void drawGrid(SDL_Renderer* renderer, int grid[GRID_WIDTH][GRID_HEIGHT]) {
    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            SDL_Rect rect = { i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE };
            if (grid[i][j] == 1) {
                SDL_SetRenderDrawColor(renderer, (ALIVE_COLOR >> 16) & 0xFF, (ALIVE_COLOR >> 8) & 0xFF, ALIVE_COLOR & 0xFF, SDL_ALPHA_OPAQUE);
            }
            else {
                SDL_SetRenderDrawColor(renderer, (DEAD_COLOR >> 16) & 0xFF, (DEAD_COLOR >> 8) & 0xFF, DEAD_COLOR & 0xFF, SDL_ALPHA_OPAQUE);
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

int main (int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //
    int step = 0;
    int g_size = 1;
    int grid[G_DIM][G_DIM] = {0};
    initRandom(grid);

    // Main Loop
    bool running = true;
    SDL_Event e;
    while (running && g_size > 0) { // Run until converges (if it will)
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) running = false;
        }
        
        //printBoard(grid, step); // Replace with visual
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Draw grid
        drawGrid(renderer, grid);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(100); // Adjust this value to control the speed

        // Game Iteration
        updateGrid(grid);
        //step++;
    }
    //printBoard(grid, step);
    return 0;
}