#include "Cube.hpp"
#include "Solver.hpp"
#include <iostream>

int main() {
    Cube cube;

    auto scramble = generate_scramble(5);
    std::cout << "Scramble: ";
    for (auto& m : scramble) std::cout << m << " ";
    std::cout << "\n";

    cube.move_sequence(scramble);
    cube.print();

    std::vector<std::string> solution;
    bool found = solve(cube, 5, solution);

    if (found) {
        std::cout << "Solved with: ";
        for (auto& m : solution) std::cout << m << " ";
        std::cout << "\n";
    } else {
        std::cout << "No solution found.\n";
    }
}