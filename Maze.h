#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

class Maze {
public:
    Maze(int width, int height, int numExits);
    void generate();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void print() const;
    void storeMazeData();
    void printMazeData() const;
    std::vector<std::vector<int>> getMazeData() const;

private:
    struct Cell {
        bool visited;
        bool topWall;
        bool bottomWall;
        bool leftWall;
        bool rightWall;
        Cell() : visited(false), topWall(true), bottomWall(true), leftWall(true), rightWall(true) {}
    };

    int width;
    int height;
    int numExits;  // Number of exits
    std::vector<std::vector<Cell>> grid;
    std::vector<std::vector<int>> mazeData;
    void carvePath(int x, int y);
    bool isInBounds(int x, int y) const;
    std::vector<std::pair<int, int>> getUnvisitedNeighbors(int x, int y) const;
    void addExits();
};

#endif // MAZE_H