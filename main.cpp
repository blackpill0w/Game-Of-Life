/************************************************/
/*   TODO: split the thing on multiple files    */
/************************************************/



#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>

sf::Color BLACK(0, 0, 0, 255);
sf::Color WHITE(255, 255, 255, 255);
const int cellSize{20};

class Cell {
   public:
      bool alive;
      sf::RectangleShape square;
      sf::Color aliveColor;
      sf::Color deadColor;
      const std::vector<Cell*> cellsNearMe;
      int x;
      int y;

   private:
      bool isClicked(sf::Vector2i &mousePos) {
         return (std::abs(mousePos.x - this->square.getPosition().x) < 1 && std::abs(mousePos.y - this->square.getPosition().y) < 1);
      }
      void setCellsNearMe() {

      }

   public:
      Cell(float initialX, float initialY, int myX, int myY) :
        alive{ false }, square{ sf::RectangleShape(sf::Vector2f(cellSize, cellSize)) },
        aliveColor{ BLACK }, deadColor{ WHITE }, cellsNearMe{ 0 }, x{ myX }, y{ myY }
      {  
         this->square.setPosition(sf::Vector2f(initialX, initialY));
         this->square.setFillColor(deadColor);
         this->square.setOutlineThickness(1.f);
         this->square.setOutlineColor(BLACK);

         // TODO: 
         setCellsNearMe();
      }
   void checkState(sf::Vector2i &mousePos) {
      if (isClicked(mousePos)) {
         this->alive = !(this->alive);
         if (this->alive) {
               this->square.setFillColor(aliveColor);
         } else {
               this->square.setFillColor(deadColor);
         }
         std::cout << "index" << x*(720/20)+y*(600/20) << "\n";
      }
   }
   void draw(sf::RenderWindow *window) {
      window->draw(this->square);
   }
   void resize(float newSquareSide) {
      this->square.setSize(sf::Vector2f(newSquareSide, newSquareSide));
   }
   void update() {
   }
};

void adjustMousePos(sf::Vector2i *mousePos) {
   mousePos->x = (mousePos->x / cellSize) * cellSize;
   mousePos->y = (mousePos->y / cellSize) * cellSize;
}

int main() {
   // Those are used for game logic not intialization
   int wWidth{720};
   int wHeight{600};

   sf::RenderWindow window(sf::VideoMode(720u, 600u), "Game Of Life",
                           sf::Style::Titlebar | sf::Style::Close);
   window.setFramerateLimit(60u);

   bool mouseClicked(false);
   sf::Vector2i mousePos({0, 0});

   int maxX = wWidth / cellSize;
   int maxY = wHeight / cellSize;
   std::vector<Cell> cells;
   cells.reserve(static_cast<size_t>(maxX * maxY));
   for (int x = 0; x < maxX; x++) {
      for (int y = 0; y < maxY; y++) {
         cells.push_back(Cell(x * cellSize, y * cellSize, x, y));
      }
   }
   while (window.isOpen()) {
      sf::Event evnt;
      while (window.pollEvent(evnt)) {
         if (evnt.type == sf::Event::Closed) {
               window.close();
         } else if (evnt.type == sf::Event::MouseButtonPressed) {
               mouseClicked = true;
               mousePos = sf::Mouse::getPosition(window);
               adjustMousePos(&mousePos);
         }
      }
      // Clear
      window.clear(sf::Color(0, 185, 205, 255));
      // Draw
      for (Cell &cell : cells) {
         cell.draw(&window);
         if (mouseClicked) {
            cell.checkState(mousePos);
         }
      }
      if (mouseClicked)
         mouseClicked = false;
      // Display
      window.display();
   }
}