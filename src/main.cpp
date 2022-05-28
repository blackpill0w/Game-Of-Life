/************************************************/
/*   TODO: split the thing on multiple files    */
/************************************************/



#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "constants.h"
#include "cell.h"

int main() {
   // Those are used for game logic not intialization
   sf::RenderWindow window(
         sf::VideoMode(
            static_cast<unsigned>(constants::wWidth),
            static_cast<unsigned>(constants::wHeight)
         ),
         "Game Of Life",
         sf::Style::Titlebar | sf::Style::Close
   );
   window.setFramerateLimit(constants::fps);

   bool animationStarted{ false };
   bool mouseClicked(false);
   sf::Vector2i mousePos( {0, 0} );

   std::vector<Cell> cells;
   cells.reserve(constants::cellsNumber);
   for (int y = 0; y < constants::squaresInY; y++) {
      for (int x = 0; x < constants::squaresInX; x++) {
         cells.emplace_back(x * constants::cellSize, y * constants::cellSize, x, y);
      }
   }
   for (Cell c: cells) {
      c.setCellsNearMe();
   }
   while (window.isOpen()) {
      sf::Event evnt;
      while (window.pollEvent(evnt)) {
         if (evnt.type == sf::Event::Closed) {
            window.close();
         }
         else if (!animationStarted && evnt.type == sf::Event::MouseButtonPressed) {
            mouseClicked = true;
            mousePos = sf::Mouse::getPosition(window);
         }
         else if (evnt.type == sf::Event::KeyPressed) {
            if (evnt.key.code == sf::Keyboard::G) {
               animationStarted = !animationStarted;
            }
         }
      }
      // Clear
      window.clear(sf::Color(0, 185, 205, 255));
      // Draw
      for (Cell &cell : cells) {
         cell.draw(&window);
         if (mouseClicked && !animationStarted) {
            cell.checkClicked(mousePos);
         }
         else if (animationStarted) {
            cell.checkState(&cells);
         }
      }
      if (mouseClicked) {
         mouseClicked = false;
      }
      if (animationStarted) {
         for (auto& cell : cells) {
            cell.update();
         }
      }
      // Display
      window.display();
   }
}