# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -lsfml-graphics -lsfml-window -lsfml-system

# Source and object files
SRC = conway_game.cpp window.cpp
OBJ = $(SRC:.cpp=.o)

# Target executable
TARGET = conway_game_of_life

# Default target
all: $(TARGET)

# Compile the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean