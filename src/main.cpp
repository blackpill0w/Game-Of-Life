#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <vector>

#include "SFML-utilities/sfmlColors.h"
#include "SFML-utilities/button.h"

#include "constants.h"
#include "cell.h"


int main() {
   sf::RenderWindow window(
         sf::VideoMode(
            static_cast<unsigned>(constants::wWidth),
            static_cast<unsigned>(constants::wHeight)
         ),
         "Game Of Life",
         sf::Style::Titlebar | sf::Style::Close
   );
   window.setFramerateLimit(constants::fps);

   bool mouseClicked(false);
   bool animationStarted{ false };
   sfmlUtils::Button pauseButton(
      " Play ", "UbuntuMono-R.ttf",
      sf::Vector2f(constants::wWidth - constants::sideBarWidth + 10.f, 30),
      // A lambda to change the state of the animation
      [&animationStarted, &pauseButton](){ 
         animationStarted = !animationStarted;
         if (!animationStarted) {
            pauseButton.sfmlText.setString(" Play ");
         }
         else {
            pauseButton.sfmlText.setString(" Pause");
         }
      }
   );

   sf::Vector2i mousePos( {0, 0} );

   std::vector<Cell> cells;
   cells.reserve(constants::cellsNumber);
   for (int y = 0; y < constants::squaresInY; y++) {
      for (int x = 0; x < constants::squaresInX; x++) {
         cells.emplace_back(x * constants::cellSize, y * constants::cellSize, x, y);
      }
   }
   for (Cell c: cells) {
      // Each cell stores the indices of cells surrounding it.
      c.setCellsNearMe();
   }
   while (window.isOpen()) {
      sf::Event evnt;
      while (window.pollEvent(evnt)) {
         if (evnt.type == sf::Event::Closed) {
            window.close();
         }
         else if (evnt.type == sf::Event::MouseButtonPressed) {
            mouseClicked = true;
         }
      }
      // Clear
      window.clear(sfmlUtils::lightGreyColor);
      // Draw
      mousePos = sf::Mouse::getPosition(window);
   
      pauseButton.run(&window, mousePos, mouseClicked);
      if (!animationStarted) {
         for (Cell &cell : cells) {
            cell.draw(&window);
            if (mouseClicked){   
               cell.checkClicked(mousePos);
            }
         }
      }
      else if (animationStarted) {
         for (Cell &cell : cells) {
            cell.draw(&window);
            cell.checkState(&cells);
         }
      }
      if (animationStarted) {
         for (Cell& cell : cells) {
            cell.update();
         }
      }
      if (mouseClicked) {
         mouseClicked = false;
      }
      // Display
      window.display();
   }
}