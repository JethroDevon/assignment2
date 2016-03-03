#include "sockWrapper.h"
#include <iostream>

//TCP client constructor, first initialiser list arg is directly initialising thread as it cannot have a default constructor
sockWrapper::sockWrapper(std::string _clientName, std::string _ipAddress, unsigned short _port): run( &sockWrapper::runConnection, this), connectionName( _clientName), IP( _ipAddress), port ( _port){

    isAlive = false;
    toSend = false;
    socket.setBlocking(false);
}

sockWrapper::~sockWrapper(){

}

std::string sockWrapper::getName(){

    return connectionName;
}

void sockWrapper::send( std::string _message){

    _message += '\r';
    _message += '\0';

    const char* toSend = _message.c_str();
    socket.send( toSend, strlen(toSend));
}

void sockWrapper::recieve(){

    char data[1024];
    std::size_t received = 0;

    // TCP socket:
    if(socket.receive(data, 1000, received) == sf::Socket::Done){

        std::string temp;
        temp = ((std::string) data).substr( 0, received);
        temp += '\n';
        messageStack.push(temp);
        std::cout<< temp << std::endl;       
    }
}

//returns size of message stack
int sockWrapper::unreadMessages(){

    return messageStack.size();
}

void sockWrapper::connect(){

    //connect to server
    socket.connect(getIP(), getPort());

    //returns 0 if there is no connection, this is grounds to set alive to false
    //and close this socket
    if(socket.getRemotePort() != 0){

        setAlive(true);
        run.launch();
        std::cout << "connection to " << connectionName <<" completed."<< std::endl;
    }else{

        setAlive(false);
        std::cout << "connection to " << connectionName << " failed." << std::endl;
    }
}

std::string sockWrapper::getIP(){

    return IP;
}

unsigned short sockWrapper::getPort(){

    return port;
}

bool sockWrapper::getAlive(){

    return isAlive;
}

void sockWrapper::setAlive( bool _a){

    isAlive = _a;
}

std::string sockWrapper::getMessage(){

    if(!messageStack.empty()){

        std::cout << messageStack.size()<<std::endl;
        std::string temp = messageStack.back();
        messageStack.pop();
        return temp;
    }
}

void sockWrapper::setPostMessage(std::string _m){

    message = _m;
}

bool sockWrapper::getToSend(){

    return toSend;
}

void sockWrapper::setToSend(bool _b){

    toSend = _b;
}

std::string sockWrapper::postMessage(){

    return message;
}

void sockWrapper::closeSocket(){

    socket.disconnect();
}

void sockWrapper::runThread(){

    run.launch();
}

void sockWrapper::runConnection(){

    while(getAlive()){

        //mutex lock to avoid waste-full spinning
        mutex.lock();

        if(getToSend()){

            send(postMessage());

            messageStack.push( getName() + ": " + message);

            //sets message back to ""
            message = "";

            //sets flag to post something back to false
            setToSend(false);
        }

        sf::sleep(sf::milliseconds(1));

        recieve();

        //mutex lock to avoid waste-full spinning
        mutex.unlock();
    }
}
 