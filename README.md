# Maze Snake Game

This project implements a snake game where the snake explores multiple mazes generated dynamically using a C++ maze generation algorithm and the A* pathfinding algorithm to find food within the maze. The maze generation and snake game logic are integrated using Python bindings.

## Project Structure

- **Maze.h**: Header file defining the Maze class.
- **Maze.cpp**: Implementation of the Maze class.
- **bindings.cpp**: Pybind11 bindings to expose the Maze class to Python.
- **AStar.py**: Implementation of the A* pathfinding algorithm.
- **Settings.py**: Configuration settings including colors, grid size, and other constants.
- **SnakeGame.py**: Implementation of the snake game logic.
- **main.py**: Entry point for the snake game.
- **run_maze.ps1**: PowerShell script to compile the C++ extensions and run the Python game.
- **CMakeLists.txt**: Configuration file for building the C++ extension.
- **maze.dat**: Example file to load or save maze data.

## Prerequisites

Ensure you have the following installed:

- Python 3.x
- C++ compiler
- Pybind11 library
- CMake

## Setup and Usage

### Step 1: Compile the C++ Extensions

Build the C++ component and run the `run_maze.ps1` PowerShell script to compile the C++ code and build the Python bindings.

```powershell
cmake -S . -B build
cd build
cmake --build .
cd .. 
.\run_maze.ps1
```

This commands will:
1. Build the maze module
2. Navigate to the script directory.
3. Set the `PYTHONPATH` to include the build directory.
4. Run the `main.py` script.

### Step 2: Run the Snake Game

After the compilation is successful, the `main.py` script will execute automatically. This script initializes the snake game, generates the mazes, and starts the game loop.

### main.py

This script initializes and runs the snake game. It generates a grid of six mazes, places the snake in an open cell, and uses the A* algorithm to navigate the snake to the food.

## Components

### Maze Class

The Maze class is implemented in C++ and exposed to Python using Pybind11. It includes the following methods:

- **Constructor**: `Maze(int width, int height, int numExits)`
- **generate()**: Generates the maze using a randomized depth-first search algorithm.
- **saveToFile(const std::string& filename)**: Saves the maze to a file.
- **loadFromFile(const std::string& filename)**: Loads the maze from a file.
- **print()**: Prints the maze to the console.
- **storeMazeData()**: Stores the maze data in a 2D vector.
- **printMazeData()**: Prints the stored maze data to the console.
- **getMazeData() const**: Returns the stored maze data as a 2D vector.

#### Example Usage in Python

```python
import maze

# Create a Maze object
m = maze.Maze(20, 20, 1)

# Generate the maze
m.generate()

# Print the maze to the console
m.print()

# Get the maze data
maze_data = m.getMazeData()
```

### A* Algorithm

The A* pathfinding algorithm is implemented in `AStar.py`. It includes the following methods:

- **heuristic(a, b)**: Calculates the heuristic distance between two points.
- **neighbors(node)**: Returns the valid neighboring nodes for a given node.
- **find_path(start, goal)**: Finds the path from the start node to the goal node.

### Snake Game

The snake game logic is implemented in `SnakeGame.py`. It includes the following components:

- **Initialization**: Sets up the game, initializes the snake and food positions, and configures the pathfinding.
- **Movement**: Updates the snake's position based on the calculated path.
- **Rendering**: Draws the maze, snake, and food on the screen.

### Settings

The `Settings.py` file contains various configuration settings for the game, including colors, grid size, and other constants.

### Game Controls

- The game runs automatically, and the snake navigates to the food using the A* algorithm.
- The game continues until the window is closed.

### Customization

You can customize the maze size, number of mazes, and other parameters by modifying the configuration in `Settings.py` and the logic in `main.py`.

## Troubleshooting

If you encounter issues running the game, ensure that:

- The C++ code compiles successfully.
- The Python bindings are correctly set up.
- All required libraries are installed.
