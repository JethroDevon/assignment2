#ifndef BUTTON_H
#define BUTTON_H

#include "Sprites.h"

//class draws a mouse click-able button on the screen, class is derived from sprites class
class Button: public Sprites{
    public:

        //plain button
        Button(int, int, int, int, std::string, sf::RenderWindow &);

        //button can take an image or an animation and call it on click
        Button(int, int, int, int, std::string, sf::RenderWindow &, std::string);

        //draw the button
        void drawBox();

        //draws a buttons animation in the form of a sprite
        void animateButton();

        //sets colours for text box, else they are left to default
        void setBorderColor(sf::Color);
        void setBackgroundColor(sf::Color);

        //prepares button object
        void setRects();


    private:

        //the shape object
        sf::RectangleShape rectangle;

        //this stores a drawrable image of text
        sf::Text sftext;

        //string to write within the button
        std::string text;

        //font is going to remain bold sans
        sf::Font font;
};

#endif // BUTTON_H
