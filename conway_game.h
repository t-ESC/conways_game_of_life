// myclass.h
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

const int WIDTH = 450;
const int HEIGHT = 300;
const float ALIVE_PROB = 0.15;

class Board {
private:
    // Top left corner (0, 0)
    std::vector<std::vector<bool>> alive;

public:
    Board();
    void update_board();
    void print_board();
    bool get_cell_status(int x, int y);
    int count_alive_neighbours_of_cell(int width, int height);
};

#endif // Board