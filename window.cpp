#include <SFML/Graphics.hpp>
#include "conway_game.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> args;

    // Convert command-line arguments to std::string
    for (int i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }

    // Check if the "-d" flag is present
    bool debug_mode = false;
    for (const auto& arg : args) {
        if (arg == "-d") {
            debug_mode = true;
            break;
        }
    }
    if (debug_mode) {
        std::cout << "Debug mode enabled" << std::endl;
    }

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    std::srand(std::time(nullptr)); // use current time as seed for random generator

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("./fonts/Ubuntu-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Conway's Game of Life");

    Board gameBoard = Board();
    
    float cellWidth = static_cast<float>(WINDOW_WIDTH) / WIDTH;
    float cellHeight = static_cast<float>(WINDOW_HEIGHT) / HEIGHT;

    //Clock for delay
    sf::Clock clock; // Create a clock object
    int updateDelay = 500; // Delay between updates in milliseconds

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::N:
                    gameBoard.update_board();
                    std::cout << "Board Updated!" << std::endl;
                    std::cout.flush();
                    break;
                default:
                    break;
                }
            }
        }

        // Check if enough time has passed to update the board
        if (clock.getElapsedTime().asMilliseconds() >= updateDelay) {
            gameBoard.update_board();
            clock.restart(); // Reset the clock
        }

        window.clear();

        // Draw the grid
        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
                cell.setPosition(x * cellWidth, y * cellHeight);
                gameBoard.get_cell_status(x, y) ? cell.setFillColor(sf::Color::White) : cell.setFillColor(sf::Color::Black); 
                cell.setOutlineColor(sf::Color::Red);
                cell.setOutlineThickness(cellWidth >= 2.0f && cellHeight >= 2.0f ? 1.0f : 0.0f);                
                window.draw(cell);

                // Cell text
                if (debug_mode)
                {
                    sf::Text cellText;
                    cellText.setFont(font);
                    cellText.setString(std::to_string(gameBoard.count_alive_neighbours_of_cell(x, y)));
                    cellText.setCharacterSize(12);
                    cellText.setFillColor(sf::Color::Red);
                    cellText.setPosition(x * cellWidth + cellWidth / 2 - cellText.getGlobalBounds().width / 2,
                                        y * cellHeight + cellHeight / 2 - cellText.getGlobalBounds().height / 2);

                    window.draw(cellText);
                }
                
            }
        }

        window.display(); // Display the updated frame
    }

    return 0;
}