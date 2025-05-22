#pragma once

#include "cube.hpp"
#include <vector>
#include <string>

// Solve phase 1 of Kociemba's algorithm:
// It orients the cube and solves the E-slice.
// Returns a sequence of moves that transforms the cube to the phase-1 goal state.
std::vector<std::string> solve_phase1(const Cube& startCube);
