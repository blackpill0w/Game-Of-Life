#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include "constants.h"
#include <iostream>

class Cell {
   public:
      bool alive;
      bool aliveNext;
      sf::RectangleShape square;
      int cellsNearMe[8];
      int x;
      int y;
      int index;
   private:
      sf::Color BLACK{ sf::Color(0, 0, 0, 255) };
      sf::Color WHITE{ sf::Color(255, 255, 255, 255) };
      sf::Color &aliveColor{ BLACK };
      sf::Color &deadColor{ WHITE };
   public:
      Cell(float initialX, float initialY, int myX, int myY);
      void setCellsNearMe();
      void draw(sf::RenderWindow *window);
      void checkClicked(sf::Vector2i &mousePos);
      void checkState(std::vector<Cell> *cells);
      void update();
      void resize(float newSquareSide);
   private:
      bool isClicked(sf::Vector2i &mousePos);
};

#endif