#include "EpidemicCard.h"
#include "Map.h"


EpidemicCard::EpidemicCard() :Card(){
}

EpidemicCard::EpidemicCard(string n, char c, int a) : Card(n, c, a){
}

EpidemicCard::~EpidemicCard()
{
}

void EpidemicCard::setEpidemic(int a)
{
	this->setName("Epidemic Card");
	this->setId(a);
}

void EpidemicCard::playCard(Map map)
{
	//Move the infection rate marker forward 1 space on the Infection Rate Track.
	InfectionDeck::infectionMarker++;
	InfectionDeck* infDeck = map.infectionDeck;


	//draw the bottom card from the infection deck and make outbreak
	infDeck->deck.back().makeOutbreak();
	//move card to discard pile
	infDeck->discardPile.push_back(infDeck->deck.back());
	infDeck->deck.pop_back();

	infDeck->intensify();
}