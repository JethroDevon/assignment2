#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include "StringLoader.h"
#include <algorithm>
#include <vector>
#include <cstdio>
#include <sstream>
#include <stdlib.h>


class Substitution{

	public:

    //constructor takes cipher as args
	  Substitution(std::string);

		~Substitution();

	  StringLoader stringload;

    //calculates relative frequency of each symbol and puts it on RFoSL string
		void relativeFrequency();

    //this function will attempt to descramble the message by matching  RFoL and RFoSL
    //frequency of letters to the closest ones average, it will return the closest match
		std::string solve();

    //counts the total number of symbols in use
		void storeSymbols();

    //outputs frequency of substituted letters
		void showFrequencyTable();

		//switches character from RFoL with one in same vector position
		//as RFoSL
		char switchChar( char);

		//switches to substituted characters in keyMap
		void switchKeys( char, char);

		void swapKVP( char, char);

		void updateCipher();

		//the cipher text to perform analysis on
	  std::string cipher;

	protected:

	    //shows keymap characters that may be substituted
	    void showKeyMap();

	    //loads a text file from path in args and initialises cipher string with it
	    void getCipher( std::string _path);

      //finds the most common combinations of characters of size args
      std::string maxNCombination( int);

      //a combination to add and the ratio of the combination occurring to others starting with the first char
      //in the first args and the same combination of letters
	    int addCombination( std::string);

			//returns true if common combination is in common combination array
	    bool findCombination( std::string);

			//returns true if common combination is in common combination array
			char getValue( char _key);

			//returns true if common word is in commonWords Array
			bool findWords( std::string);

			//returns true for each pair that is present in cipher
      bool findPairs( std::string);

			//initialises common combination array
	    void initialiseCombination( int);

			//initialises words array
			void initialiseWords( int);

			//initialises common word array
			std::string maxNWords();

			//loads array of words seperated by spaces onto cipherArray
			void initCipherArray();

			//initialises the std:: vector dictionary
			void initDictionary( std::string);

			float dictionaryQuotient();

	    //this vector stores each type of symbol in the cipher text
	    //stores each of the different symbols encountered while parsing the cipher
      std::vector<char> symbols;

			//stores the cipher text on a vector for easy manipulation
			std::vector<std::string>cipherArray;

			//RFoL stands for relative frequency of letters, the frequency is relative to the frequency of use of letters in english
			//map object is a list of characters mapped to the percentage of frequency in which they occur in the english dictionary
			//relative to v, this will be used for comparing against the frequency of other occurrences
      std::vector<std::pair< char, float>> RFoL;

      //Relative frequency of substituted letters is the frequency of letters in the cipher passed into args, operations will
      //be performed on this structure
      std::vector<std::pair< char, float>> RFoSL;

      //this will contain the alphabet on the left and the substituted letters on the right, operations
      //will be performed on this container by various functions after it has been initalised with sortVectors function
      std::vector<std::pair< char, char>> keyMap;

      //stores common combinations in order of size(<) and occurrence(<)
      std::vector<std::string> commonCombinations;

			//stores common words
			std::vector<std::string> commonWords;

      //stores only a few of the most common pairs of characters
      std::vector<std::string> commonPairs;

      //this function inserts all the data in the map table, to be called in the constructor
			void initialiseRFoL();

      //organises the vectors to be in order of value
	    void sortVectors();

			//stores only a few of the most common pairs of characters
			std::vector<std::string> dictionary;

			//the outputted solved string after initialisation
	    std::string solvedString;

			//initialliy faalse, this is so some analysis can know if the string has big amounts with no spaces in
			bool bigwithoutspaces = false;

};

#endif // SUBSTITUTION_H
