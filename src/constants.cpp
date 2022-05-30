#include "constants.h"

namespace constants {
   extern const int sideBarWidth{ 130 };
   extern const int wWidth{ 720 + sideBarWidth };
   extern const int wHeight{ 600 };
   extern const int cellSize{ 20 };
   extern const int squaresInX{ (wWidth - sideBarWidth) / cellSize };
   extern const int squaresInY{ wHeight / cellSize };
   extern const unsigned fps{ 14u };
   extern const unsigned long cellsNumber{ squaresInX * squaresInY };
}