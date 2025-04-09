#include "solver.hpp"
#include <random>

std::vector<std::string> generate_scramble(int length) {
    static const std::vector<std::string> moves = {
        "U", "U'", "U2", "D", "D'", "D2",
        "F", "F'", "F2", "B", "B'", "B2",
        "L", "L'", "L2", "R", "R'", "R2"
    };

    std::vector<std::string> scramble;
    std::string last_face = "";

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, moves.size() - 1);

    while (scramble.size() < length) {
        std::string move = moves[dist(rng)];
        std::string face = move.substr(0, 1);

        if (face != last_face) {
            scramble.push_back(move);
            last_face = face;
        }
    }
    return scramble;
}

bool solve(Cube& cube, int max_depth, std::vector<std::string>& solution,
           std::vector<std::string> path, int depth) {
    if (cube.is_solved()) {
        solution = path;
        return true;
    }

    if (depth >= max_depth) return false;

    static const std::vector<std::string> moves = {
        "U", "U'", "U2", "D", "D'", "D2",
        "F", "F'", "F2", "B", "B'", "B2",
        "L", "L'", "L2", "R", "R'", "R2"
    };

    for (const auto& move : moves) {
        Cube copy = cube;
        copy.move(move);
        path.push_back(move);

        if (solve(copy, max_depth, solution, path, depth + 1))
            return true;

        path.pop_back();
    }

    return false;
}

// Wrapper
bool solve(Cube& cube, int max_depth, std::vector<std::string>& solution) {
    return solve(cube, max_depth, solution, {}, 0);
}