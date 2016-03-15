#ifndef GUI_H
#define GUI_H

#include <sstream>
#include "Sprites.h"
#include "textIn.h"
#include "textOut.h"
#include "Button.h"

class GUI{

    public:

        GUI(int , int, sf::RenderWindow &rw);
        virtual ~GUI();

        //exit button
        Button closeBut, launchBut;

         //text output
        textOut textbox;

        //draws gui components
        void drawComponents();

        //draws gui components
        void drawLabels();

        //this is used to save code repetition in getAddress, Name and Port
        std::string feildData( int);

        //returns address feild data
        std::string getAddress();

        //returns name feild data
        std::string getName();

        //returns name feild data
        std::string getInput();

        //manages which box is selected, only one can be selected at a time
        void componentSelection( int);

        //listens for keyboard input
        void inputListen( sf::Event &);

        //gets port feild data
        int getPort();

        //returns addressfeild data
        void setAddress();

        //returns name feild data
        void setName();

        //gets port feild data
        void setPort();

        void setInput();

        std::string getType();

        //calls all setters, used to get feild data before connecting
        bool setFeildData( bool);

        void clearText();

    private:

        //keeps screen height and screen width
        int sheight, swidth;

        //vector type array of sprites for drawring each gui component iterativley, vector is a unique pointer of ancestor
        //type to gui component, the unique pinter is to avoid object slicing, this is where not enough memory is alocated to each object on the vector but
        //the code still compiles: http://stackoverflow.com/questions/13091302/stdvector-for-parent-and-child-class
        std::vector <textIn*> components;

        //default type is chat client
        std::string type = "CHATSRV", baddress, bname, input;   

        //stores port number to return
        int bport;

        //bools to store values of buttons
        bool launched, closed;

        sf::RenderWindow &rw;
};

#endif // GUI_H
