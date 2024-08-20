#include "conway_game.h"

Board::Board() {
    // resize vectror to appropriate size
    alive.resize(WIDTH, std::vector<bool>(HEIGHT, false));

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            // Random Value projected between 0 and 1
            alive[i][j] = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) < ALIVE_PROB;            
        }
    }

    alive[0][0] = false; // protagonist
    alive[0][1] = true;
    alive[0][2] = false;

    alive[1][0] = false;
    alive[1][1] = false; 
    alive[1][2] = true;

    alive[2][0] = true;
    alive[2][1] = true;
    alive[2][2] = true;

}

int Board::count_alive_neighbours_of_cell(int width, int height) {
    int count = 0;
    // Top left neighbour
    if (width-1 >= 0 && height-1 >= 0) {
        if (alive[width-1][height-1]) count++;
    }
    // Top neighbour
    if (height-1 >= 0) {
        if (alive[width][height-1]) count++; 
    }
    //Top right neighbour
    if (width+1 < WIDTH && height-1 >= 0 ) {
        if (alive[width+1][height-1]) count++;
    }
    // Left neighbour
    if (width - 1 >= 0){
        if (alive[width-1][height]) count++; 
    }
    // Right neighbour
    if (width + 1 < WIDTH){
        if (alive[width+1][height]) count++; 
    }
    // Bottom left neighbour
    if (width-1 >= 0 && height+1 < HEIGHT ) {
        if (alive[width-1][height+1]) count++;
    }
    // Bottom neighbour
    if (height + 1 < HEIGHT){
        if (alive[width][height+1]) count++; 
    }
    // Bottom right neighbour
    if (width+1 < WIDTH && height+1 < HEIGHT) {
        if (alive[width+1][height+1]) count++;
    }
    return count;
}

void Board::update_board() {
    std::vector<std::vector<bool>> new_board = alive;
    
    // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    // Any live cell with two or three live neighbours lives on to the next generation.
    // Any live cell with more than three live neighbours dies, as if by overpopulation.
    // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            int num_neighbours = count_alive_neighbours_of_cell(i, j);

            if (alive[i][j])
            {
                if (num_neighbours < 2 || num_neighbours > 3) new_board[i][j] = false;
            } else {
                if (num_neighbours == 3) new_board[i][j] = true;
            }
        }
    }

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++){
            alive[i][j] = new_board[i][j];
        }
    }
    
}

void Board::print_board() {
    // std::cout << "Board_Updated: " << std::time(nullptr) << std::endl;
    std::cout << count_alive_neighbours_of_cell(1, 0) << std::endl;

    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            if (alive[i][j]) {
                std::cout << "█";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool Board::get_cell_status(int x, int y)
{
    return alive[x][y];
}