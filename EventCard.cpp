#include "EventCard.h"

EventCard::EventCard(string n, int i) :Card(n, 'r', i)
{
	eCard = Card(n, 'r', i);
	this->setType("Event Card");
}

EventCard::EventCard() : Card("null", 'r', 0)
{
	eCard = Card("null", 'r', 0);
}

EventCard::~EventCard(){}

/*
string EventCard::getEventCard()
{
	return this->getName;
}*/


void EventCard::printEventCard()
{
	cout << this->getName() << this->getId() << endl;
}

