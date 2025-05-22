// KociembaPhase1_IDA.cpp
#include "Cube.hpp"
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <iostream>

const std::array<std::string, 18> PHASE1_MOVES = {
    "U", "U'", "U2",
    "D", "D'", "D2",
    "F", "F'", "F2",
    "B", "B'", "B2",
    "L", "L'", "L2",
    "R", "R'", "R2"
};

// --- Heuristic ---
int heuristic(const Cube& cube) {
    int ori = get_orientation_index(cube);
    int slice = get_e_slice_index(cube);
    // Rough heuristic: count flipped edges and misplaced E-slice edges
    int edgeOri = __builtin_popcount(ori);
    int sliceWrong = __builtin_popcount(slice ^ 0xF00);
    return std::max((edgeOri + 1) / 2, (sliceWrong + 1) / 2);  // each move can fix up to 2
}

// --- IDA* DFS ---
bool dfs(Cube& cube, int g, int threshold, std::vector<std::string>& path, int& nextThreshold) {
    int f = g + heuristic(cube);
    if (f > threshold) {
        nextThreshold = std::min(nextThreshold, f);
        return false;
    }

    if (get_orientation_index(cube) == 0 && get_e_slice_index(cube) == 0xF00) {
        return true; // Solved!
    }

    for (const std::string& move : PHASE1_MOVES) {
        Cube next = cube;
        next.move(move);
        path.push_back(move);

        if (dfs(next, g + 1, threshold, path, nextThreshold))
            return true;

        path.pop_back(); // backtrack
    }

    return false;
}

// --- Main IDA* Loop ---
std::vector<std::string> solve_phase1(const Cube& startCube) {
    int threshold = heuristic(startCube);

    while (threshold <= 20) { // reasonable move cap
        std::vector<std::string> path;
        int nextThreshold = 1e9;
        Cube copy = startCube;

        if (dfs(copy, 0, threshold, path, nextThreshold))
            return path;

        if (nextThreshold == 1e9)
            break; // No more paths to search

        threshold = nextThreshold;
    }

    return {}; // No solution found
}
