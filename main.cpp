#include <SFML/Graphics.hpp>
#include "sockWrapper.h"
#include "Connection.h"
#include "Splash.h"
#include "Button.h"
#include "Message.h"
#include "textIn.h"
#include "textOut.h"

int main(){

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "", false);

    //splash uses the window for the splash screen display
    //Splash splash(window, "media/spaceman.png", 4, 8, 2);

    //function in splash can return window to desired size after, should make that auto-matic
    //splash.returnWindow(800 , 600, "PAP c++ Assignment 2");

    textOut textBox(20, 20, 600, 400, 20, window);

    textIn textField( 20, 460, 300, 30, window);


    //setting frame rate
    window.setFramerateLimit(12);

    //connection object with timeout passed into args
    Connection connection(1000);

    sf::sleep(sf::milliseconds(100));

    //connection.createServer(6677);
    connection.addSocket("local", "chat.freenode.net", 6666);

    connection.sendTo("local", "NICK revenge\r\nUser mrdv * * :mow mow\r\n" );


    //main window loop is presently for debugging
     while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){


            switch(event.type){

                case sf::Event::Closed:

                    window.close();
                    break;

                case sf::Event::KeyPressed:

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){

                        connection.sendTo( "local", textField.getText());
                        textBox.addString(textField.getText());
                    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

                        window.close();
                        connection.killConnection("local");
                    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){

                
                    }

                    break;

            }
        }

        if(connection.dataAvailable("local")){

            textBox.addString(connection.receiveFrom("local"));
        }


        //refreshes background
        window.clear(sf::Color::Black);

        textField.drawText();
        textBox.drawBox();

        textField.keyListen(event);

        //displays everything to draw to the window
        window.display();
     }
}
