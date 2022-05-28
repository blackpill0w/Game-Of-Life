#include "constants.h"

namespace constants {
   extern const int wWidth{ 720 };
   extern const int wHeight{ 600 };
   extern const int cellSize{ 20 };
   extern const int squaresInX{ wWidth / cellSize };
   extern const int squaresInY{ wHeight / cellSize };
   extern const unsigned fps{ 10u };
   extern const unsigned long cellsNumber{ squaresInX * squaresInY };
}