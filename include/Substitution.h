#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <sstream>


class Substitution{

	public:

        //constructor takes cipher as args
	    Substitution(std::string);

        //calculates relative frequency of each symbol and puts it on RFoSL string
		void relativeFrequency();

        //this function will attempt to descramble the message by matching  RFoL and RFoSL
        //frequency of letters to the closest ones average, it will return the closest match
		std::string solveFrequency();

        //counts the total number of symbols in use
		void storeSymbols();

        //outputs frequency of substituted letters
		void showFrequencyTable();

		//switches character from RFoL with one in same vector position
		//as RFoSL
		char switchChar(char);

		//switches to substituted characters in keyMap
		void switchSubstitutes(char _swapA, char _swapB);

		 //the cipher text to perform analysis on
	    std::string cipher;

	private:

	    //shows keymap characters that may be sustituted
	    void showKeyMap();

	    //loads a text file from path in args and initialises cipher string with it
	    void getCipherFromFile(std::string _path);

        //finds the most common combinations of characters of size args
        std::string maxNCombination(int);

        //a combination to add and the ratio of the combination occurring to others starting with the first char
        //in the first args and the same combination of letters
	    int addCombination(std::string);

	    bool findCombination(std::string);

        bool findPairs(std::string);

	    void initialiseCombination(int);

	    //this vector stores each type of symbol in the cipher text
	    //stores each of the different symbols encountered while parsing the cipher
        std::vector<char> symbols;

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

        //stores common combinations in order of size (<) and occurrence (<)
        std::vector<std::string> commonCombinations;

        //stores only a few of the most common pairs of characters
        std::vector<std::string> commonPairs;

        //this function inserts all the data in the map table, to be called in the constructor
		void initialiseRFoL();

        //organises the vectors to be in order of value
	    void sortVectors();

	    std::string solvedString;
};

#endif // SUBSTITUTION_H
