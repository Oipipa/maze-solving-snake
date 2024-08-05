#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Maze.h"

namespace py = pybind11;

PYBIND11_MODULE(maze, m) {
    py::class_<Maze>(m, "Maze")
        .def(py::init<int, int, int>())
        .def("generate", &Maze::generate)
        .def("saveToFile", &Maze::saveToFile)
        .def("loadFromFile", &Maze::loadFromFile)
        .def("print", &Maze::print)
        .def("storeMazeData", &Maze::storeMazeData)
        .def("printMazeData", &Maze::printMazeData)
        .def("getMazeData", &Maze::getMazeData);
}
