#pragma once
#include "Card.h"
#include <string>
#include <vector>
#include "InfectionDeck.h"
#include "Map.h"
using namespace std;

class EpidemicCard : public Card {
public:

	//Constructors
	EpidemicCard();
	EpidemicCard(string n, char c, int a);
	//Destructor
	~EpidemicCard();

	void setEpidemic(int a);
	void playCard(Map map); //pass the infection deck
};