#include "Ceasar.h"

Ceasar::Ceasar( std::string _path): Substitution( _path){

  std::cout << solve();
}

char Ceasar::switchChar( char _c){

  char temp = '!';
  int pos = 0;

  for(int c = 0; c < alphabet.size(); c++){

    if( alphabet.at(c) == _c){

      pos = c;
      break;
    }
  }

  if(pos + cipherNumber > alphabet.size()){ pos = (pos + cipherNumber) - alphabet.size();}

  return alphabet.at(pos);
}

std::string Ceasar::solve(){

  for(int c = 0; c < alphabet.size(); c++){

    if( keyMap.at(0).second == alphabet.at(c)){

      cipherNumber = c;
      break;
    }
  }

  solvedString = "";

  for(auto c: cipher){

       solvedString += switchChar(c);
   }

  return solvedString;
}

//if there is a higher value then the solved string is most likley correct
bool Ceasar::check(){

  if( dictionaryQuotient() > 30 ){ return true; } return false;
}
