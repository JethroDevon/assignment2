#ifndef CEASAR_H
#define CEASAR_H

#include "Substitution.h"
#include <string>

class Ceasar: public Substitution{

    public:

      Ceasar( std::string);
      virtual std::string solve();

    private:


      virtual char switchChar( char );

      //if there is a higher value then the solved string is most likley correct
      bool check();

      int cipherNumber;

      //to check against the size the cipher may be
      std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
};
#endif // Ceasar
