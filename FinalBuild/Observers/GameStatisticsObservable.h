#pragma once
#include <vector>
#include "../Map/City.h"
#include "../Player/Player.h"
#include "../Cards/Card.h"
#include "../Cards/InfectionDeck.h"
#include "AbstractStatsObserver.h"


using namespace std;

#ifndef GAMESTATISTICSOBSERVABLE_H
#define GAMESTATISTICSOBSERVABLE_H

class GameStatisticsObservable
{
public:
	vector<AbstractStatsObserver*> obs;

	int numCitiesInfected;	//number of cities infected by the players
	vector<int> numResourcesPerPlayer;	//total number of resources at each player possesion
	int numCubesOnMap;	//the number of disease cubes on the map
	int numResourcesRemaining; //the remaining resources as a supply available during the game
	int numCubesRemaining;	//number of disease cubes remaining
	double percentCitiesInfected;	//percentage of cities infected

	//functions to update the data
	void updateCitiesInfected(vector<City*> cities);
	void updateNumResourcesPerPlayer(vector<Player> players);
	void updateNumCubesOnMap(vector<City*> cities);
	void updateNumResourcesRemaining(vector<Card*> deck);
	void updateNumCubesRemaining(InfectionDeck* deck);

	GameStatisticsObservable(int numPlayers);
	~GameStatisticsObservable();

	void attach(AbstractStatsObserver* ob);
	void detach(AbstractStatsObserver* ob);
	void notify();

};


#endif