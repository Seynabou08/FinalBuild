#include "ReferenceCard.h"
#include "../Cards/Role.h"
#include "../Cards/Card.h"
#include "../Cards/CityCard.h"
#include "../Cards/EventCard.h"
#include "../Cards/EpidemicCard.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

/**#include "boost_1_63_0/boost/archive/text_oarchive.hpp"
#include "boost_1_63_0boost/archive/text_iarchive.hpp"**/

class Player
{
public:

	//Constructors and Destructor methods
	Player(Map map, char p, vector<Role> &roleDeck, vector<Card*> &deck, int pCount, int id);
	Player();
	~Player();

	//toString methods 
	void printPossessions();
	void printReference();
	void displayHand();
	void displayHandWithColors();
	void displayActionsLeft();

	//Accessor and Mutator methods
	vector<Card*> getHand();
	void setHand(vector<Card*> c);
	void setRole(Role rCard);
	void setPawn(char ch);
	void setId(int i);
	void setLocation(int i);

	void setEventCard(Card ecard);
	void removeEvent();
	Card getEventCard();

	string getRole();
	City getCity();
	char getPawn();
	int getId();
	int getLocation();
	int getHandSize(); //size of hand

	//actions
	void move(Map m);
	void flight(int a);
	bool buildStation(Map* m);
	bool treatDisease(Map m);
	bool shareKnowledge(Player* target);
	bool discoverCure(Map m);
	void dispatcherAbility(vector<Player>*, Map* m, int playerIndex);
	bool useEventCard(int playerNum, InfectionDeck ideck, Map newMap);
	bool contingencyPlanner(int playerNum, InfectionDeck ideck, Map newMap);
	
	//automatic mandatory actions
	void startTurn();
	void subtractAction();
	void increaseAction();
	void concludeTurn(vector<Card*> &deck, Map map);
	void drawCards(Map map, vector<Card*> &deck, int num); //Changed so that pointer is passed
	bool checkAction();
	void discard(int a);

	//pawn color enum type
	enum pawnColors { BLACK, GREEN, BLUE, RED, YELLOW };

private:
	int id;
	int location;
	City city;
	pawnColors pawn;
	vector <Card*> cards;
	Role role;
	int actionsLeft;
	ReferenceCard rc;
	Card eCard;
	vector<EpidemicCard*> epCard;

};
#endif 