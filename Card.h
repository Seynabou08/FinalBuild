#include <string>
#include <iostream>
using namespace std;

#ifndef CARD_H
#define CARD_H

class Card
{
    public:

		//Constructors
        Card();
        Card(string n, char c, int i);
		//Destructor
        ~Card();

		//Accessor and Mutator methods
        string getName();
        char getColor();
        int getId();
		string getType();
        void setName(string n);
        void setColor(char c);
        void setId(int i);
		void setType(string t);

        void printCard();

    private:
        string name;
        char color;
        int id;
		string type;

};
#endif