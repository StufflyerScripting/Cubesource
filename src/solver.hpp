#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "cube.hpp"
#include <vector>
#include <string>

std::vector<std::string> generate_scramble(int length = 20);
bool solve(Cube& cube, int max_depth, std::vector<std::string>& solution);

#endif