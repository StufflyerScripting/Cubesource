#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <string>
#include <vector>

enum Face { U, D, F, B, L, R };

class Cube {
public:
    std::array<char, 54> state;

    Cube();
    void print() const;
    void move(const std::string& m);
    void move_sequence(const std::vector<std::string>& moves);
    bool is_solved() const;

private:
    void apply(const std::string& m);
    void rotate_face(int face);
    void rotate_ring(const std::array<int, 12>& indices);

    void turnU();
    void turnD();
    void turnF();
    void turnB();
    void turnL();
    void turnR();
};

#endif