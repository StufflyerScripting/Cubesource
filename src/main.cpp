#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "cube.hpp"
#include "dredux.hpp"  // <- Make sure you created this header and .cpp

// Function to generate a random scramble of a given length
std::vector<std::string> generateRandomScramble(int length) {
    std::vector<std::string> moves = {
        "U", "D", "L", "R", "F", "B",
        "U'", "D'", "L'", "R'", "F'", "B'",
        "U2", "D2", "L2", "R2", "F2", "B2"
    };
    std::vector<std::string> scramble;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, moves.size() - 1);

    for (int i = 0; i < length; ++i) {
        scramble.push_back(moves[dis(gen)]);
    }

    return scramble;
}

int main() {
    Cube cube;

    // Generate a random scramble of length 20
    int scrambleLength = 10;
    std::vector<std::string> scramble = generateRandomScramble(scrambleLength);

    // Print the scramble
    std::cout << "\nRandom Scramble: ";

    for (const auto& move : scramble) {
        std::cout << move << " ";
    }
    std::cout << "\n";

    // Apply scramble to the cube
    cube.scramble(scramble);

    // Print the cube after scramble
    std::cout << "\nScrambled Cube:\n";
    cube.print();

    std::cout << "Orientation Index: " << get_orientation_index(cube) << "\n";
    std::cout << "E-Slice Index: " << get_e_slice_index(cube) << "\n";

    // === Solve Phase 1 ===
    std::cout << "\nSolving Phase 1...\n";
    std::vector<std::string> phase1_solution = solve_phase1(cube);
    

    // Print Phase 1 solution
    std::cout << "\nPhase 1 Solution (" << phase1_solution.size() << " moves): ";
    for (const auto& move : phase1_solution) {
        std::cout << move << " ";
    }
    std::cout << "\n Cube after solution:";
    cube.print();

    return 0;
}
