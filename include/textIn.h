#ifndef TEXTIN_H
#define TEXTIN_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>
#include <vector>
#include <stdexcept>
#include "Sprites.h"

class textIn: public Sprites{

    public:

        //xposition, yposition, width, height and the window to draw the sprite in
        textIn(int, int, int, int, sf::RenderWindow &);

        //returns string to send text on
        std::string send();

        //displays the box to draw text in
        void drawBox();

        //listens to key presses when selected
        void keyListen(sf::Event &);

        //gets or returns the string 'text'
        std::string getText();

        //these functions are to change the default behaviour of the text box, normall on get string hte text box clears unless is set otherwise
        bool clearText();
        void setClearText( bool);

        //clears the texty text box for frexh text receiving
        void clearTextBox();

    private:

        //prepares elements in the textbox to be drawn in the right places
        void setRects();

        //functions to draw the caret and set its position
        void setCaret( int, int, int);
        void drawCaret();

        //returns index of text object in text vector that the caret is colliding with
        int textIndex();

        //inserts text in arg2 at index in arg1
        void insertChar(int, int);

        //adds a character to the string text, takes a unicode integer as args
        void addChar(int);

        //removes last character from the string text unless its empty
        void removeChar();

        //removes a sf::Text obecect from vector text at the index num in args
        void removeChar(int);

        //for reseting hte caretPositions array and re initialising it with all caret positions
        //on the array
        void resetPositions();

        //sets caret to front or back of text graphics
        void caretFront();
        void caretBack();

        //stores sf::font
        sf::Font font;

        //this rectangle displays text within it, caret will display  the text cursor
        sf::RectangleShape rectangle, caret, caret2;

        //send text is true if there is text to send, selected is true if mouse is over the text box when it clicks
        //caretX and caretY keep track of where the caret is but do not effect its moving, caret Index stores the
        //position on the string to draw the caret
        bool sendText, withButton, clear;
        int caretX, caretY, caretIndex;

        //this function returns the distance that the string of texts overlaps the text box, if it doesn't it returns the minus
        //distance
        int textboxOverlap();

        //lastKey remembers the last key code hit and calls the ticks function, this way the user doesn't
        //stream characters out when they just want one
        int lastKey;

        //name for heading of text input box if needed and text to appear in
        //text box automatically
        std::string name, initText;

        //stores an array of individual characters, these will be drawn in the form of a
        //sentence but allow the insertion of text
        std::vector<sf::Text> text;

        //this stores each position in front of each sfml character type drawn onto the screen
        std::vector<int> caretPosition;
};

#endif // TEXTIN_H
