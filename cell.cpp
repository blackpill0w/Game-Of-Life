#include "cell.h"

Cell::Cell(float initialX, float initialY, int myX, int myY):
   alive{ false }, aliveNext{ false }, square{ sf::RectangleShape(sf::Vector2f(constants::cellSize, constants::cellSize)) },
   cellsNearMe{ -1, -1, -1, -1, -1, -1, -1, -1 }, x{ myX }, y{ myY }
{  
   this->square.setPosition(sf::Vector2f(initialX, initialY));
   this->square.setFillColor(deadColor);
   this->square.setOutlineThickness(1.f);
   this->square.setOutlineColor(BLACK);

   this->setCellsNearMe();

}

bool Cell::isClicked(sf::Vector2i &mousePos) {
   return (std::abs(mousePos.x - this->square.getPosition().x) < 1 && std::abs(mousePos.y - this->square.getPosition().y) < 1);
}

void Cell::checkClicked(sf::Vector2i &mousePos) {
   if (isClicked(mousePos)) {
      this->alive = !(this->alive);
   }
   if (this->alive)
      this->square.setFillColor(aliveColor);
   else
      this->square.setFillColor(deadColor);
}

void Cell::setCellsNearMe() {
   int myIndex{ this->x + this->y*constants::squaresInX };

   if (this->x > 0) {
      // Cell left
      cellsNearMe[0] = myIndex - 1;
      if (y > 0) {
         // Cell left up
         cellsNearMe[1] = myIndex - 1 - constants::squaresInX;
      }
      if (y + 1 < constants::squaresInY) {
         // Cell left down
         cellsNearMe[2] = myIndex - 1 + constants::squaresInX;
      }
   }

   if (this->x + 1 < constants::squaresInX) {
      // Cell right
      cellsNearMe[3] = myIndex + 1;
      if (y > 0) {
         // Cell right up
         cellsNearMe[4] = myIndex + 1 - constants::squaresInX;
      }
      if (y + 1 < constants::squaresInY) {
         // Cell right down
         cellsNearMe[5] = myIndex + 1 + constants::squaresInX;
         }
   }
   if (y > 0)
      cellsNearMe[6] = myIndex - constants::squaresInX;
   if (y + 1 < constants::squaresInY)
      cellsNearMe[7] = myIndex + constants::squaresInX;

}

void Cell::checkState(std::vector<Cell> *cells) {
   int aliveNeighbours{ 0 };
   for (auto& c: this->cellsNearMe) {
      if ( c != -1 && (*cells)[static_cast< unsigned long >(c)].alive ) {
         aliveNeighbours++;
      }
   }
   if (this->alive) {
      if (aliveNeighbours < 2 || aliveNeighbours > 3) {
         std::cout << "Index: " << this->x + this->y*constants::squaresInX << '\n';
         std::cout << "Alive neighbours: " << aliveNeighbours << '\n';
         this->aliveNext = false;
      }
   }
   else {
      if (aliveNeighbours == 3)
         this->aliveNext = true;
   }
}

void Cell::update() {
   if (this->aliveNext) {
      this->alive = true;
      this->square.setFillColor(aliveColor);
   }
   else {
      this->alive = false;
      this->square.setFillColor(deadColor);
   }
}

void Cell::draw(sf::RenderWindow *window) {
   window->draw(this->square);
}

void Cell::resize(float newSquareSide) {
   this->square.setSize(sf::Vector2f(newSquareSide, newSquareSide));
}
