#include "cube.hpp"
#include <iostream>
#include <algorithm>

Cube::Cube() {
    faces[U] = std::array<std::array<char, 3>, 3>{{
        {{'W', 'W', 'W'}},
        {{'W', 'W', 'W'}},
        {{'W', 'W', 'W'}}
    }};
    faces[D] = std::array<std::array<char, 3>, 3>{{
        {{'Y', 'Y', 'Y'}},
        {{'Y', 'Y', 'Y'}},
        {{'Y', 'Y', 'Y'}}
    }};
    faces[F] = std::array<std::array<char, 3>, 3>{{
        {{'G', 'G', 'G'}},
        {{'G', 'G', 'G'}},
        {{'G', 'G', 'G'}}
    }};
    faces[B] = std::array<std::array<char, 3>, 3>{{
        {{'B', 'B', 'B'}},
        {{'B', 'B', 'B'}},
        {{'B', 'B', 'B'}}
    }};
    faces[L] = std::array<std::array<char, 3>, 3>{{
        {{'O', 'O', 'O'}},
        {{'O', 'O', 'O'}},
        {{'O', 'O', 'O'}}
    }};
    faces[R] = std::array<std::array<char, 3>, 3>{{
        {{'R', 'R', 'R'}},
        {{'R', 'R', 'R'}},
        {{'R', 'R', 'R'}}
    }};
}

char Cube::getSticker(Face f, int row, int col) const {
    return faces[f][row][col];
}

std::array<char, 3> Cube::getCorner(int index) const {
    switch (index) {
        case 0: return {faces[U][0][2], faces[R][0][0], faces[F][0][2]}; // URF
        case 1: return {faces[U][0][0], faces[F][0][0], faces[L][0][2]}; // UFL
        case 2: return {faces[U][2][0], faces[L][0][0], faces[B][0][2]}; // ULB
        case 3: return {faces[U][2][2], faces[B][0][0], faces[R][0][2]}; // UBR
        case 4: return {faces[D][0][2], faces[F][2][2], faces[R][2][0]}; // DFR
        case 5: return {faces[D][0][0], faces[L][2][2], faces[F][2][0]}; // DLF
        case 6: return {faces[D][2][0], faces[B][2][2], faces[L][2][0]}; // DBL
        case 7: return {faces[D][2][2], faces[R][2][2], faces[B][2][0]}; // DRB
        default: return {'?', '?', '?'};
    }
}

std::array<char, 2> Cube::getEdge(int index) const {
    switch (index) {
        case 0: return {faces[U][0][1], faces[F][0][1]}; // UF
        case 1: return {faces[U][1][0], faces[L][0][1]}; // UL
        case 2: return {faces[U][2][1], faces[B][0][1]}; // UB
        case 3: return {faces[U][1][2], faces[R][0][1]}; // UR
        case 4: return {faces[D][0][1], faces[F][2][1]}; // DF
        case 5: return {faces[D][1][0], faces[L][2][1]}; // DL
        case 6: return {faces[D][2][1], faces[B][2][1]}; // DB
        case 7: return {faces[D][1][2], faces[R][2][1]}; // DR
        case 8: return {faces[F][1][0], faces[L][1][2]}; // FL
        case 9: return {faces[F][1][2], faces[R][1][0]}; // FR
        case 10: return {faces[B][1][0], faces[R][1][2]}; // BR
        case 11: return {faces[B][1][2], faces[L][1][0]}; // BL
        default: return {'?', '?'};
    }
}

bool Cube::isInEslice(int edgeIndex) const {
    return edgeIndex >= 8 && edgeIndex <= 11;
}

int get_orientation_index(const Cube& cube) {
    struct EdgeDef {
        Face f1; int r1, c1;
        Face f2; int r2, c2;
    };

    struct CornerDef {
        Face f1; int r1, c1;
        Face f2; int r2, c2;
        Face f3; int r3, c3;
    };

    const std::array<EdgeDef, 12> edges = {{
        {U,0,1, F,0,1}, {U,1,0, L,0,1}, {U,2,1, B,0,1}, {U,1,2, R,0,1},
        {D,0,1, F,2,1}, {D,1,0, L,2,1}, {D,2,1, B,2,1}, {D,1,2, R,2,1},
        {F,1,2, R,1,0}, {F,1,0, L,1,2}, {B,1,0, L,1,0}, {B,1,2, R,1,2}
    }};

    const std::array<CornerDef, 8> corners = {{
        {U,0,2, R,0,0, F,0,2}, // URF
        {U,0,0, F,0,0, L,0,2}, // UFL
        {U,2,0, L,0,0, B,0,2}, // ULB
        {U,2,2, B,0,0, R,0,2}, // UBR
        {D,0,2, F,2,2, R,2,0}, // DRF
        {D,0,0, L,2,2, F,2,0}, // DFL
        {D,2,0, B,2,2, L,2,0}, // DLB
        {D,2,2, R,2,2, B,2,0}  // DBR
    }};

    // ---- Edge orientation ----
    int edge_orientation = 0;
    for (int i = 0; i < 12; ++i) {
        char c1 = cube.getSticker(edges[i].f1, edges[i].r1, edges[i].c1);
        char c2 = cube.getSticker(edges[i].f2, edges[i].r2, edges[i].c2);

        bool flip = false;
        if ((c1 == 'W' || c1 == 'Y') && !(edges[i].f1 == U || edges[i].f1 == D)) flip = true;
        if ((c2 == 'W' || c2 == 'Y') && !(edges[i].f2 == U || edges[i].f2 == D)) flip = true;

        edge_orientation = (edge_orientation << 1) | (flip ? 1 : 0);
    }

    // ---- Corner orientation ----
    int corner_orientation = 0;
    for (int i = 0; i < 8; ++i) {
        const auto& corner = corners[i];
        std::array<char, 3> facelets = {
            cube.getSticker(corner.f1, corner.r1, corner.c1),
            cube.getSticker(corner.f2, corner.r2, corner.c2),
            cube.getSticker(corner.f3, corner.r3, corner.c3)
        };

        int ori = -1;
        for (int j = 0; j < 3; ++j) {
            if (facelets[j] == 'W' || facelets[j] == 'Y') {
                ori = j;
                break;
            }
        }
    }

    return edge_orientation * 2187 + corner_orientation;
}



int get_e_slice_index(const Cube& cube) {
    struct EdgeDef {
        Face face1;
        int row1, col1;
        Face face2;
        int row2, col2;
    };

    const std::array<EdgeDef, 12> edges = {{
        {U, 0, 1, F, 0, 1}, // UF
        {U, 1, 0, L, 0, 1}, // UL
        {U, 2, 1, B, 0, 1}, // UB
        {U, 1, 2, R, 0, 1}, // UR
        {D, 0, 1, F, 2, 1}, // DF
        {D, 1, 0, L, 2, 1}, // DL
        {D, 2, 1, B, 2, 1}, // DB
        {D, 1, 2, R, 2, 1}, // DR
        {F, 1, 2, R, 1, 0}, // FR
        {F, 1, 0, L, 1, 2}, // FL
        {B, 1, 2, R, 1, 2}, // BR
        {B, 1, 0, L, 1, 0}  // BL
    }};

    const std::array<std::string, 4> e_slice_edges = {"FR", "FL", "BL", "BR"};
    const std::array<std::pair<char, char>, 4> e_colors = {
        std::make_pair('G', 'R'),
        std::make_pair('G', 'O'),
        std::make_pair('B', 'O'),
        std::make_pair('B', 'R')
    };

    int mask = 0;

    for (int i = 0; i < 12; ++i) {
        char c1 = cube.getSticker(edges[i].face1, edges[i].row1, edges[i].col1);
        char c2 = cube.getSticker(edges[i].face2, edges[i].row2, edges[i].col2);

        for (const auto& [ec1, ec2] : e_colors) {
            if ((c1 == ec1 && c2 == ec2) || (c1 == ec2 && c2 == ec1)) {
                mask |= (1 << i);
                break;
            }
        }
    }

    return mask; // 12-bit mask; use it directly or map to compressed index (e.g., 0–494)
}


void Cube::print() const {
    const char* faceNames[6] = {"U", "D", "F", "B", "L", "R"};
    for (int f = 0; f < 6; ++f) {
        std::cout << "Face " << f << " (" << faceNames[f] << "):\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                std::cout << faces[f][i][j];
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

const std::array<std::array<std::array<char, 3>, 3>, 6>& Cube::getFaces() const {
    return faces;
}

void Cube::rotate_face_clockwise(Face f) {
    auto& face = faces[f];
    std::array<std::array<char, 3>, 3> temp = face;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            face[j][2 - i] = temp[i][j];
}

void Cube::rotate_face_counterclockwise(Face f) {
    rotate_face_clockwise(f);
    rotate_face_clockwise(f);
    rotate_face_clockwise(f);
}

void Cube::rotate_face_180(Face f) {
    rotate_face_clockwise(f);
    rotate_face_clockwise(f);
}

void Cube::turnU() {
    rotate_face_clockwise(U);
    std::array<char, 3> temp = faces[F][0];
    faces[F][0] = faces[R][0];
    faces[R][0] = faces[B][0];
    faces[B][0] = faces[L][0];
    faces[L][0] = temp;
}

void Cube::turnU_prime() {
    rotate_face_counterclockwise(U);
    std::array<char, 3> temp = faces[F][0];
    faces[F][0] = faces[L][0];
    faces[L][0] = faces[B][0];
    faces[B][0] = faces[R][0];
    faces[R][0] = temp;
}

void Cube::turnU2() {
    rotate_face_180(U);
    std::swap(faces[F][0], faces[B][0]);
    std::swap(faces[L][0], faces[R][0]);
}

void Cube::turnD() {
    rotate_face_clockwise(D);
    std::array<char, 3> temp = faces[F][2];
    faces[F][2] = faces[L][2];
    faces[L][2] = faces[B][2];
    faces[B][2] = faces[R][2];
    faces[R][2] = temp;
}

void Cube::turnD_prime() {
    rotate_face_counterclockwise(D);
    std::array<char, 3> temp = faces[F][2];
    faces[F][2] = faces[R][2];
    faces[R][2] = faces[B][2];
    faces[B][2] = faces[L][2];
    faces[L][2] = temp;
}

void Cube::turnD2() {
    rotate_face_180(D);
    std::swap(faces[F][2], faces[B][2]);
    std::swap(faces[L][2], faces[R][2]);
}

void Cube::turnF() {
    rotate_face_clockwise(F);
    std::array<char, 3> temp = {faces[U][2][0], faces[U][2][1], faces[U][2][2]};
    for (int i = 0; i < 3; ++i) {
        faces[U][2][i] = faces[L][2 - i][2];
        faces[L][2 - i][2] = faces[D][0][2 - i];
        faces[D][0][2 - i] = faces[R][i][0];
        faces[R][i][0] = temp[i];
    }
}

void Cube::turnF_prime() {
    rotate_face_counterclockwise(F);
    std::array<char, 3> temp = {faces[U][2][0], faces[U][2][1], faces[U][2][2]};
    for (int i = 0; i < 3; ++i) {
        faces[U][2][i] = faces[R][i][0];
        faces[R][i][0] = faces[D][0][2 - i];
        faces[D][0][2 - i] = faces[L][2 - i][2];
        faces[L][2 - i][2] = temp[i];
    }
}

void Cube::turnF2() {
    turnF();
    turnF();
}

void Cube::turnB() {
    rotate_face_clockwise(B);
    std::array<char, 3> temp = {faces[U][0][0], faces[U][0][1], faces[U][0][2]};
    for (int i = 0; i < 3; ++i) {
        faces[U][0][i] = faces[R][i][2];
        faces[R][i][2] = faces[D][2][2 - i];
        faces[D][2][2 - i] = faces[L][2 - i][0];
        faces[L][2 - i][0] = temp[i];
    }
}

void Cube::turnB_prime() {
    rotate_face_counterclockwise(B);
    std::array<char, 3> temp = {faces[U][0][0], faces[U][0][1], faces[U][0][2]};
    for (int i = 0; i < 3; ++i) {
        faces[U][0][i] = faces[L][2 - i][0];
        faces[L][2 - i][0] = faces[D][2][2 - i];
        faces[D][2][2 - i] = faces[R][i][2];
        faces[R][i][2] = temp[i];
    }
}

void Cube::turnB2() {
    turnB();
    turnB();
}

void Cube::turnL() {
    rotate_face_clockwise(L);
    std::array<char, 3> temp = {faces[U][0][0], faces[U][1][0], faces[U][2][0]};
    for (int i = 0; i < 3; ++i) {
        faces[U][i][0] = faces[B][2 - i][2];
        faces[B][2 - i][2] = faces[D][i][0];
        faces[D][i][0] = faces[F][i][0];
        faces[F][i][0] = temp[i];
    }
}

void Cube::turnL_prime() {
    rotate_face_counterclockwise(L);
    std::array<char, 3> temp = {faces[U][0][0], faces[U][1][0], faces[U][2][0]};
    for (int i = 0; i < 3; ++i) {
        faces[U][i][0] = faces[F][i][0];
        faces[F][i][0] = faces[D][i][0];
        faces[D][i][0] = faces[B][2 - i][2];
        faces[B][2 - i][2] = temp[i];
    }
}

void Cube::turnL2() {
    turnL();
    turnL();
}

void Cube::turnR() {
    rotate_face_clockwise(R);
    std::array<char, 3> temp = {faces[U][0][2], faces[U][1][2], faces[U][2][2]};
    for (int i = 0; i < 3; ++i) {
        faces[U][i][2] = faces[F][i][2];
        faces[F][i][2] = faces[D][i][2];
        faces[D][i][2] = faces[B][2 - i][0];
        faces[B][2 - i][0] = temp[i];
    }
}

void Cube::turnR_prime() {
    rotate_face_counterclockwise(R);
    std::array<char, 3> temp = {faces[U][0][2], faces[U][1][2], faces[U][2][2]};
    for (int i = 0; i < 3; ++i) {
        faces[U][i][2] = faces[B][2 - i][0];
        faces[B][2 - i][0] = faces[D][i][2];
        faces[D][i][2] = faces[F][i][2];
        faces[F][i][2] = temp[i];
    }
}

void Cube::turnR2() {
    turnR();
    turnR();
}

void Cube::move(const std::string& m) {
    if (m == "U") turnU();
    else if (m == "U'") turnU_prime();
    else if (m == "U2") turnU2();
    else if (m == "D") turnD();
    else if (m == "D'") turnD_prime();
    else if (m == "D2") turnD2();
    else if (m == "F") turnF();
    else if (m == "F'") turnF_prime();
    else if (m == "F2") turnF2();
    else if (m == "B") turnB();
    else if (m == "B'") turnB_prime();
    else if (m == "B2") turnB2();
    else if (m == "L") turnL();
    else if (m == "L'") turnL_prime();
    else if (m == "L2") turnL2();
    else if (m == "R") turnR();
    else if (m == "R'") turnR_prime();
    else if (m == "R2") turnR2();
}

void Cube::scramble(const std::vector<std::string>& moves) {
    for (const auto& m : moves)
        move(m);
}
