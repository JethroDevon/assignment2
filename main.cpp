#include <SFML/Graphics.hpp>
#include "sockWrapper.h"
#include "Connection.h"
#include "Substitution.h"
#include "Ceasar.h"
#include "Splash.h"
#include "Button.h"
#include "Message.h"
#include "textIn.h"
#include "textOut.h"
#include "GUI.h"

int main(){


    //flag to control connection in connection block of logic
    bool connectionRunning = false;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "", false);

    //splash uses the window for the splash screen display
    Splash splash(window, "media/spaceman.png", 4, 8, 2);

    //function in splash can return window to desired size after, should make that auto-matic
    //splash.returnWindow(800 , 600, "PAP c++ Assignment 2");

    GUI gui( 800, 600, window);

    //setting frame rate
    window.setFramerateLimit( 10);

    //faster key press detection
    window.setKeyRepeatEnabled( false);

    //connection object with timeout passed into args, is global for re-use with all application type modes
    Connection connection( 10000);

    //main window loop is presently for debugging
     while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){


            switch( event.type){

                case sf::Event::Closed:

                    window.close();
                    break;

                case sf::Event::KeyPressed:

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){

                      std::string temp = gui.getInput();

                      //send temp string from input box to connection wit hname in args1 and
                      //to the textbos and finally the console
                      connection.sendTo( gui.getName(), gui.getInput());
                      gui.textbox.addString(temp);
                      std::cout << "sending: " << temp << std::endl;

                    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

                      connection.killConnection(gui.getName());
                      window.close();
                    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){

                      connection.killConnection(gui.getName());

                      //false allows connection to be connectable again
                      connectionRunning = false;

                      //launch button must be set to false again however
                      gui.launchBut.setSelected(false);
                    }

                    break;
            }
        }


        if(!connectionRunning){

            //gui functions are to log user in once launch is set to true, this is so user can log out and then log into
            //another server or irc channel
            if( gui.setFeildData(gui.launchBut.getSelected()) && gui.getType() == "IRC"){

                connection.addSocket( gui.getName(), gui.getAddress(), gui.getPort());

                //irc protocol requires a short pause before posting connection data
                sf::sleep(sf::milliseconds(1000));

                //send irc protocol to join chat room at GoldsmithsC++
                connection.sendTo( gui.getName(), "NICK " + gui.getName() + "\r\nUser Cppassignment * * :pap bot\r\nJOIN :#GoldsmithsC++\r\n" );

                connectionRunning = true;

            }else if( gui.setFeildData(gui.launchBut.getSelected()) && gui.getType() == "CHATSRV"){

                std::cout<< gui.launchBut.getSelected();

                //starts a server and runs the thread
                connection.createServer(gui.getPort());

                 //reset launch button to false
                connectionRunning = true;

            }else if( gui.setFeildData(gui.launchBut.getSelected()) && gui.getType() == "CHATCL"){

                //connects a client and runs a thread unless
                connection.addSocket( gui.getName(), gui.getAddress(), gui.getPort());
;
                connectionRunning = true;
            }
        }

        //refreshes background
        window.clear( sf::Color::Blue);

        //outputs to the console if data is pushed to the stack
        if( gui.setFeildData(gui.launchBut.getSelected()) && connection.dataAvailable( gui.getName())){

            //output to console, output box bug is not yet resolved
            std::string temp = connection.receiveFrom( gui.getName());

            std::cout<< "Received: "<< temp;

            gui.textbox.addString( temp);

            //this block demonstrates two dencryption objects functioning when a command is sent to them
            if( temp.substr( 0, 7) == "@CEASAR:"){

              std::cout<<" attempting to decrypt ceasar cipher now, please wait a moment or two...";
              Ceasar cipher(temp.substr( 8));
            }

            if( temp.substr( 0, 10) == "@FREQUENCY:"){

              std::cout<<" attempting to decrypt ceasar cipher now, please wait a moment or two...";
              Ceasar cipher(temp.substr( 11));
            }


            //if the type of the connection is IRC then
            if(gui.getType() == "IRC"){

                //gui.papBOTIN( temp);

                // if( gui.papBOTREADY())
                    // connection.sendTo( gui.getName(), gui.papBOTOUT());
            }
        }

        gui.drawComponents();

        gui.inputListen( event);

        //displays everything to draw to the window
        window.display();

        //close window if close button is selected
        if( gui.closeBut.getSelected()){

            connection.killConnection(gui.getName());
            window.close();
        }
     }
}
