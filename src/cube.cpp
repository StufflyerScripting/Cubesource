#include "cube.hpp"
#include <iostream>

Cube::Cube() {
    const char colors[6] = {'W', 'Y', 'G', 'B', 'O', 'R'};
    for (int f = 0; f < 6; ++f)
        for (int i = 0; i < 9; ++i)
            state[f * 9 + i] = colors[f];
}

void Cube::print() const {
    for (int f = 0; f < 6; ++f) {
        std::cout << "Face " << f << ": ";
        for (int i = 0; i < 9; ++i)
            std::cout << state[f * 9 + i];
        std::cout << "\n";
    }
}

bool Cube::is_solved() const {
    for (int f = 0; f < 6; ++f) {
        char color = state[f * 9];
        for (int i = 1; i < 9; ++i)
            if (state[f * 9 + i] != color)
                return false;
    }
    return true;
}

void Cube::move(const std::string& m) {
    if (m.back() == '\'') {
        std::string base = m.substr(0, m.size() - 1);
        for (int i = 0; i < 3; ++i)
            apply(base);
    } else if (m.back() == '2') {
        std::string base = m.substr(0, m.size() - 1);
        for (int i = 0; i < 2; ++i)
            apply(base);
    } else {
        apply(m);
    }
}

void Cube::move_sequence(const std::vector<std::string>& moves) {
    for (const auto& m : moves)
        move(m);
}

void Cube::apply(const std::string& m) {
    if (m == "U") turnU();
    else if (m == "D") turnD();
    else if (m == "F") turnF();
    else if (m == "B") turnB();
    else if (m == "L") turnL();
    else if (m == "R") turnR();
}

void Cube::rotate_face(int face) {
    int f = face * 9;
    std::array<char, 9> temp = {
        state[f + 6], state[f + 3], state[f + 0],
        state[f + 7], state[f + 4], state[f + 1],
        state[f + 8], state[f + 5], state[f + 2]
    };
    for (int i = 0; i < 9; ++i)
        state[f + i] = temp[i];
}

void Cube::rotate_ring(const std::array<int, 12>& indices) {
    std::array<char, 12> temp;
    for (int i = 0; i < 12; ++i)
        temp[i] = state[indices[i]];
    for (int i = 0; i < 12; ++i)
        state[indices[i]] = temp[(i + 9) % 12];
}

// Face turns simplified — you can improve later
void Cube::turnU() {}
void Cube::turnD() {}
void Cube::turnF() {}
void Cube::turnB() {}
void Cube::turnL() {}
void Cube::turnR() {}