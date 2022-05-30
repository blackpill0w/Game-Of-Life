#include "button.h"

namespace sfmlUtils {

const sf::Vector2f Button::defaultPosition{ sf::Vector2f(0.f, 0.f) };
const sf::Color Button::defaultBgColor{ sfmlUtils::blackColor };
const sf::Color Button::defaultFgColor{ sfmlUtils::whiteColor };
const sf::Color Button::defaultHoverBgColor{ sfmlUtils::lightestGreyColor };

sfmlUtils::Button::Button
(
   std::string text,
   std::string fontFile,
   sf::Vector2f position,  // Has a default value
   std::function< void() > functionToRun,
   sf::Color bgColor,
   sf::Color fgColor,
   sf::Color hoverBgColor
)
: button{},
   font{}, sfmlText{},
   functionToRun{ functionToRun },
   bgColor{ bgColor }, fgColor{ fgColor }, hoverBgColor{ hoverBgColor },
   hovered{ false }
{
   if (! font.loadFromFile(fontFile)) {
      return;
   }
   sfmlText.setFont(font);
   sfmlText.setString(text);
   sfmlText.setFillColor(fgColor);

   button.setFillColor(bgColor);

   float textWidth = sfmlText.getGlobalBounds().width;
   float textHeight = sfmlText.getGlobalBounds().height;
   float marginX = 30.f;
   float marginY = 20.f;

   button.setSize(sf::Vector2f(textWidth + marginX, textHeight + marginY));
   
   button.setPosition(position);
   // NOTE: I am not sure why this works
   sfmlText.setPosition(position.x + marginX / 2.f - 2.f, position.y);
}

void Button::run(sf::RenderWindow *window, sf::Vector2i &mousePos, bool &mousePressed) {
   window->draw(this->button);
   window->draw(this->sfmlText);
   // Check if hover
   if (!hovered && this->button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
      this->hovered = true;
      button.setFillColor(this->hoverBgColor);
   }
   // Check if no longer hovered
   else if (hovered && !this->button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
      this->hovered = false;
      button.setFillColor(this->bgColor);
      // Check if pressed
      if (mousePressed && functionToRun) {
         functionToRun();
      }
   }
}

}