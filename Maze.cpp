#include "Maze.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>
#include <random>
#include <set>

Maze::Maze(int width, int height, int numExits) : width(width), height(height), numExits(numExits), grid(height, std::vector<Cell>(width)) {}

void Maze::generate() {
    std::stack<std::pair<int, int>> stack;
    std::random_device rd;
    std::mt19937 rng(rd());

    int startX = 0;  // Start at the top left
    int startY = 1;  // Move one step down to avoid corners

    stack.push({startX, startY});
    grid[startY][startX].visited = true;

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        auto neighbors = getUnvisitedNeighbors(x, y);

        if (!neighbors.empty()) {
            std::uniform_int_distribution<int> dist(0, static_cast<int>(neighbors.size()) - 1); // Explicit cast
            auto [nx, ny] = neighbors[dist(rng)];

            if (nx > x) { grid[y][x].rightWall = false; grid[ny][nx].leftWall = false; }
            else if (nx < x) { grid[y][x].leftWall = false; grid[ny][nx].rightWall = false; }
            else if (ny > y) { grid[y][x].bottomWall = false; grid[ny][nx].topWall = false; }
            else if (ny < y) { grid[y][x].topWall = false; grid[ny][nx].bottomWall = false; }

            stack.push({nx, ny});
            grid[ny][nx].visited = true;
        } else {
            stack.pop();
        }
    }

    // Create an exit at the bottom right
    grid[height - 1][width - 2].rightWall = false;
    grid[height - 1][width - 1].leftWall = false;

    // Add additional exits
    addExits();

    storeMazeData();  // Store the maze data after generation
}

void Maze::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&width), sizeof(width));
    file.write(reinterpret_cast<const char*>(&height), sizeof(height));
    file.write(reinterpret_cast<const char*>(&numExits), sizeof(numExits));
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            file.write(reinterpret_cast<const char*>(&cell), sizeof(cell));
        }
    }
}

void Maze::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    file.read(reinterpret_cast<char*>(&width), sizeof(width));
    file.read(reinterpret_cast<char*>(&height), sizeof(height));
    file.read(reinterpret_cast<char*>(&numExits), sizeof(numExits));
    grid.resize(height, std::vector<Cell>(width));
    for (auto& row : grid) {
        for (auto& cell : row) {
            file.read(reinterpret_cast<char*>(&cell), sizeof(cell));
        }
    }

    storeMazeData();  // Store the maze data after loading
}

void Maze::print() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << (cell.topWall ? "+---" : "+   ");
        }
        std::cout << "+\n";
        for (const auto& cell : row) {
            std::cout << (cell.leftWall ? "|   " : "    ");
        }
        std::cout << "|\n";
    }
    for (const auto& cell : grid[0]) {
        std::cout << "+---";
    }
    std::cout << "+\n";
}

void Maze::storeMazeData() {
    mazeData.resize(height * 2 + 1, std::vector<int>(width * 2 + 1, 1));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int gridX = x * 2 + 1;
            int gridY = y * 2 + 1;
            mazeData[gridY][gridX] = 0;
            if (!grid[y][x].topWall) mazeData[gridY - 1][gridX] = 0;
            if (!grid[y][x].bottomWall) mazeData[gridY + 1][gridX] = 0;
            if (!grid[y][x].leftWall) mazeData[gridY][gridX - 1] = 0;
            if (!grid[y][x].rightWall) mazeData[gridY][gridX + 1] = 0;
        }
    }
}

void Maze::printMazeData() const {
    for (const auto& row : mazeData) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<int>> Maze::getMazeData() const {
    return mazeData;
}

bool Maze::isInBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

std::vector<std::pair<int, int>> Maze::getUnvisitedNeighbors(int x, int y) const {
    std::vector<std::pair<int, int>> neighbors;
    if (isInBounds(x, y - 1) && !grid[y - 1][x].visited) neighbors.push_back({x, y - 1});
    if (isInBounds(x, y + 1) && !grid[y + 1][x].visited) neighbors.push_back({x, y + 1});
    if (isInBounds(x - 1, y) && !grid[y][x - 1].visited) neighbors.push_back({x - 1, y});
    if (isInBounds(x + 1, y) && !grid[y][x + 1].visited) neighbors.push_back({x + 1, y});
    return neighbors;
}

void Maze::addExits() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> sideDist(0, 3);
    std::uniform_int_distribution<int> lengthDist;

    std::set<std::pair<int, int>> exits;

    while (exits.size() < numExits) {
        int side = sideDist(rng);

        switch (side) {
        case 0: // Top side
            lengthDist = std::uniform_int_distribution<int>(0, width - 1);
            {
                int x = lengthDist(rng);
                grid[0][x].topWall = false;
                exits.insert({0, x});
            }
            break;
        case 1: // Bottom side
            lengthDist = std::uniform_int_distribution<int>(0, width - 1);
            {
                int x = lengthDist(rng);
                grid[height - 1][x].bottomWall = false;
                exits.insert({height - 1, x});
            }
            break;
        case 2: // Left side
            lengthDist = std::uniform_int_distribution<int>(0, height - 1);
            {
                int y = lengthDist(rng);
                grid[y][0].leftWall = false;
                exits.insert({y, 0});
            }
            break;
        case 3: // Right side
            lengthDist = std::uniform_int_distribution<int>(0, height - 1);
            {
                int y = lengthDist(rng);
                grid[y][width - 1].rightWall = false;
                exits.insert({y, width - 1});
            }
            break;
        }
    }
}
