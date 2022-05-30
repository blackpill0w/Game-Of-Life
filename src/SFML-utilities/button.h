////////////////////////////////////////////////////////////
// 
// A simple implementation of buttons for SFML
//
////////////////////////////////////////////////////////////

#include <functional>
#include "sfmlColors.h"

namespace sfmlUtils {

   class Button
   {
      private:
         sf::RectangleShape button;
         std::function< void() > functionToRun;
      public:
         sf::Font font;
         sf::Text sfmlText;
         sf::Color bgColor;
         sf::Color fgColor;
         sf::Color hoverBgColor;
         bool hovered;
         // Default values for some parameters/members
         static const sf::Vector2f defaultPosition;
         static const sf::Color defaultBgColor;
         static const sf::Color defaultFgColor;
         static const sf::Color defaultHoverBgColor;
      public:
         Button
         (
            std::string text,
            std::string fontFile,
            sf::Vector2f position = defaultPosition,
            std::function< void() > functionToRun = nullptr,
            sf::Color bgColor = defaultBgColor,
            sf::Color fgColor = defaultFgColor,
            sf::Color hoverBgColor = defaultHoverBgColor
         );
         void run(sf::RenderWindow *window, sf::Vector2i &mousePos, bool &mousePressed);
   };
}