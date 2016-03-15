#include "GUI.h"

///TO-DO, make font virtual loading function in sprites, have gui objects become the virtual function things demonstrate upcasting 
///makes sprites copyable too
GUI::GUI(int _swidth, int _sheight, sf::RenderWindow & _rw): rw( _rw), swidth( _swidth), sheight(_sheight),

	//magic number is the size of the button plus two pixels so the button is drawn to finish
	//two pixels of the top right edge, size of buttons is 20 pixel square, launch button is at bottom in middle
	closeBut( _swidth - 22, 2, 20, 20, "X",  _rw),
	launchBut( 300, 130, 60, 20, "LAUNCH!", _rw),
	textbox( 100, 210, 400, 300, 25, _rw){

	///TO-DO: Create array of unique pointers to type sprite and dynamically push these components to it, access
	//child member functions of vector of unique_pointers to parent class using dynamic_cast<textIn*> (base from auto loop)
	//if does not return null pointer then access with reference and then call function

	//temporary solution, pushing textFeilds to vector and naming IDs, 1 is name, 2 is address, 3 is port
	components.push_back( new textIn( 100, 50, 50, 30, rw));
	components.back()->setID(1);
	components.push_back( new textIn( 100, 90, 70, 30, rw));
	components.back()->setID(2);
	components.push_back( new textIn( 100, 130, 180, 30, rw));
	components.back()->setID(3);
	components.push_back( new textIn( 100, 170, 300, 30, rw));
	components.back()->setID(4);
	components.back()->setClearText( true);
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
	textbox.drawBox();

	if(type == "IRC" || type == "CHATCL"){
		for(auto &s: components){

				s->drawBox();
		}
	}else if(type == "CHATSRV"){

		for(auto &s: components){
			if(s->getID() == 2 || s->getID() == 4){

				s->drawBox();
			}
		}
	}
}

//this function makes sure only one text box is being written in at a time, argument takes id number of
//the function selected at the time this is called and deselcts all other boxes with a different id number
void GUI::componentSelection(int _id){

	//when the mouse is clicked this function sets all components selected flag to false
	//unless the mouse is hovering over the box at the time
	for(auto s: components){

		if(_id != s->getID() && !s->mouseOver()){

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

	if(type == "CHATSRV"){

		return "server";
	}else{

		return bname;
	}
}

std::string GUI::getInput(){

	//firsts updates string 'input' from textbox
	setInput();

	//then returns the updated string
	return input;
}

std::string GUI::getAddress(){

	return baddress;
}

//pass launch button into args, if all feilds are not null then true is returned
//on click, else false is returned and error is output to console
bool GUI::setFeildData(bool _getLaunch){

	if( _getLaunch){

		setName();
		setAddress();
		setPort();

		//if IRC or chat client modes are active then start so long as feilds are filled in
		if(type == "IRC" || type == "CHATCL"){
				if( bname == ""){

					return false;
				}if( bport == 0){
					
					return false;
				}if( baddress == ""){
					
					return false;
				}
			

		//if chat server mode is active then only port feild needs to be filled in
		}else if(type == "CHATSRV"){

			if( bport == 0){
					
				return false;
			}
		}
	}

	return _getLaunch;
}

void GUI::inputListen( sf::Event &_event){

	for(auto &s: components){

		if(s->getSelected()){

			s->keyListen( _event);
			componentSelection(s->getID());
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

//sets input from input box
void GUI::setInput(){

	input = feildData(4);
}


void GUI::drawLabels(){


}

std::string GUI::getType(){

	return type;
}

