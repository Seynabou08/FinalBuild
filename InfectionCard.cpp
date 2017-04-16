#include "InfectionCard.h"
#include "InfectionDeck.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;


InfectionCard::~InfectionCard()
{
}


InfectionCard::InfectionCard() {
	this->id = 0;
}


InfectionCard::InfectionCard(City* city){
	this->id = city->index;
	this->city = city;
}

int InfectionCard::getID() {
	return this->id;
}

string InfectionCard::getCityName() {
	return this->city->name;
}

void InfectionCard::playCard() {
	if (this->city->infectionLevel == 3 && !this->city->infected) {
		this->city->setInfection(true);
		InfectionDeck::numberOutbreaks++;
		cout << "An outbreak has occurred in " << this->getCityName() << "(" << InfectionDeck::numberOutbreaks << " outbreaks total)" << endl;
	}
	else if (this->city->infectionLevel < 3) {
		this->city->incrementInfection();
		cout << "The infection level in " << this->getCityName() << " is now " << this->city->infectionLevel << endl;
		InfectionDeck::infectionCubes--;
	}
}

void InfectionCard::playCardQuarantine(vector<City*> cities)	//cities is vector of cities on/adjacent to quarantine specialist
{
	bool isQuarantined = false;

	if (this->city->infectionLevel == 3 && !this->city->infected) {
		for (int i = 0; i < cities.size(); i++) {
			if (this->getCityName() == cities[i]->getName()) {
				isQuarantined = true;
			}
		}

		if (!isQuarantined) {
			this->city->setInfection(true);
			InfectionDeck::numberOutbreaks++;
			cout << "An outbreak has occurred in " << this->getCityName() << "(" << InfectionDeck::numberOutbreaks << " outbreaks total)" << endl;
		}
		else {
			cout << "An outbreak was prevented in " << this->getCityName() << " due to the Quarantine Specialist" << endl;
		}
	}
	else if (this->city->infectionLevel < 3) {
		for (int i = 0; i < cities.size(); i++) {
			if (this->getCityName() == cities[i]->getName()) {
				isQuarantined = true;
			}
		}

		if (!isQuarantined) {
			this->city->incrementInfection();
			cout << "The infection level in " << this->getCityName() << " is now " << this->city->infectionLevel << endl;
			InfectionDeck::infectionCubes--;
		}
		else {
			cout << "An outbreak was prevented in " << this->getCityName() << " due to the Quarantine Specialist" << endl;
		}
	}
}

void InfectionCard::setLevel(int level)
{
	this->city->infectionLevel = level;
}


void InfectionCard::makeOutbreak() {
	while (this->city->infectionLevel < 3) {
		this->city->incrementInfection();
		InfectionDeck::infectionCubes--;
	}
	this->city->setInfection(true);
	InfectionDeck::numberOutbreaks++;
}