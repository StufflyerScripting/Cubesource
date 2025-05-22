#pragma once
#include <array>
#include <string>
#include <vector>

enum Face { U, D, F, B, L, R };

class Cube {
public:
    Cube();

    void print() const;
    void move(const std::string& move);
    void scramble(const std::vector<std::string>& moves);

    // U moves
    void turnU();
    void turnU_prime();
    void turnU2();

    // D moves
    void turnD();
    void turnD_prime();
    void turnD2();

    // F moves
    void turnF();
    void turnF_prime();
    void turnF2();

    // B moves
    void turnB();
    void turnB_prime();
    void turnB2();

    // L moves
    void turnL();
    void turnL_prime();
    void turnL2();

    // R moves
    void turnR();
    void turnR_prime();
    void turnR2();

    // Access to faces
    const std::array<std::array<std::array<char, 3>, 3>, 6>& getFaces() const;

    // Apply move and return new cube (for IDA*)
    Cube apply(const std::string& move) const;

    // Sticker access
    char getSticker(Face face, int row, int col) const;

    // For corner and edge orientation tracking
    std::array<char, 3> getCorner(int index) const;
    std::array<char, 2> getEdge(int index) const;

    // Whether an edge is in the E-slice
    bool isInEslice(int edgeIndex) const;

private:
    std::array<std::array<std::array<char, 3>, 3>, 6> faces;

    void rotate_face_clockwise(Face f);
    void rotate_face_counterclockwise(Face f);
    void rotate_face_180(Face f);
};

// Orientation and E-slice indexing (used in Phase 1)
int get_orientation_index(const Cube& cube);
int get_e_slice_index(const Cube& cube);
