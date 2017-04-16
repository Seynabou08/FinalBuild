//#pragma once
#include "City.h"
#include <string>
#include <vector>

using namespace std;

#ifndef INFECTIONCARD_H
#define INFECTIONCARD_H

class InfectionDeck; //forward declaration

class InfectionCard
{
private:
	int id;
public:
	City* city;

	//Constructors
	InfectionCard();
	~InfectionCard();
	InfectionCard(City* city);

	//Mutator and accessors
	int getID();
	string getCityName();
	void playCard();    //increment level based on infection marker
	void playCardQuarantine(vector<City*> cities);    //plays card but doesn't affect cities near quarantine specialist
	void setLevel(int level);  //set level manually
	void makeOutbreak(); //raises the outbreak number and decreases the available infection cubes.

};
#endif

