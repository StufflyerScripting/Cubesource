# Cubesource
A Rubik’s cube solver still WIP. Soon with OpenGL.

This Project will be using Kociemba's Two-Phase algrotihm. It's efficiency combined with C speed is making it a very good solver

## How does it *even* work?
### Phase 1:
Reducing the cube to the H m-subgroup, so all edges and corners are oriented and E-Slice edges are in the E-slice (they don't have to be at the correct spot)
Now the cube is solvable with only U, D, R2, L2, F2 and B2.
