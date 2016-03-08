#include "GUI.h"

///TO-DO, make font virtual loading function in sprites, have gui objects become the virtual function things demonstrate upcasting 
///makes sprites copyable too
GUI::GUI(int _swidth, int _sheight, sf::RenderWindow & _rw): rw( _rw), swidth( _swidth), sheight(_sheight),

	//magic number is the size of the button plus two pixels so the button is drawn to finish
	//two pixels of the top right edge, size of buttons is 20 pixel square, launch button is at bottom in middle
	closeBut( _swidth - 22, 2, 20, 20, "X",  _rw),
	launchBut( 300, 130, 60, 20, "LAUNCH!", _rw){

	
	///TO-DO: Create array of unique pointers to type sprite and dynamically push these components to it, access
	//child member functions of vector of unique_pointers to parent class using dynamic_cast<textIn*> (base from auto loop)
	//if does not return null pointer then access with reference and then call function

	//temporary solution, pushing textFeilds to vector and naming IDs, 1 is name, 2 is address, 3 is port
	components.push_back( new textIn( 100, 50, 50, 30, rw));
	components.back()->setID(1);
	components.back()->setClearText( false);
	components.push_back( new textIn( 100, 90, 70, 30, rw));
	components.back()->setID(2);
	components.back()->setClearText( false);
	components.push_back( new textIn( 100, 130, 180, 30, rw));
	components.back()->setID(3);
	components.back()->setClearText( false);
	components.push_back( new textIn( 100, 170, 300, 30, rw));
	components.back()->setID(4);
}

GUI::~GUI(){

	while(!components.empty()){

		components.pop_back();
	}

	components.clear();
}

//this function loops through GUI componet array calling draw functions
void GUI::drawComponents(){

	closeBut.drawBox();
	launchBut.drawBox();

	for(auto &s: components){

			s->drawBox();
	}
}

//this function makes sure only one text box is being written in at a time
void GUI::componentSelection(){

	//when the mouse is clicked this function sets all components selected flag to false
	//unless the mouse is hovering over the box at the time
	for(auto s: components){

		if (sf::Mouse::isButtonPressed){

			if( !s->mouseOver())
				s->setSelected(false);
		}
	}
}

//this function takes in a number as args and returns a string if there is data in the feilds else an error string
std::string GUI::feildData(int _e){

	std::string temp = "";

	//loops through child classes of Sprites
	for(auto &s: components){

		if(s->getID() == _e){

			temp = s->getText();
		}
	} 

	//returns temp string, pointer declasred is also destroyed here
	return temp;
}


int GUI::getPort(){

	return bport;
}

std::string GUI::getName(){

	return bname;
}

std::string GUI::getInput(){

	return input;
}

std::string GUI::getAddress(){

	return baddress;
}

//pass launch button into args, if all feilds are not null then true is returned
//on click, else false is returned and error is output to console
bool GUI::setFeildData(bool _getLaunch){

	if(_getLaunch){

	setName();
	setAddress();
	setPort();


		if( bname == ""){

			std::cout<< "name feild empty." <<std::endl;
			return false;
		}if( bport == 0){
			
			std::cout<< "port feild empty." <<std::endl;
			return false;
		}if( baddress == ""){
			
			std::cout<< "address feild empty." <<std::endl;
			return false;
		}
	}

	return _getLaunch;
}

void GUI::inputListen( sf::Event &_event){

	if(!launchBut.getSelected()){

		//switches off other selected boxes
		componentSelection();

		for(auto &s: components){

			if(s->getSelected()){

				s->keyListen( _event);
			}
		}
	}
}

void GUI::setName(){

	bname = feildData(1);
}

void GUI::setAddress(){

	baddress = feildData(3);
}

void GUI::setPort(){

	bport = atoi(feildData(2).c_str());
}

//sts input from input box
void GUI::setInput(){

	input = feildData(4);
}


void GUI::drawLabels(){


}

std::string GUI::getType(){

	return type;
}

