#pragma once
#include <vector>
#include "AbstractStatsObserver.h"
using namespace std;

#ifndef GAMESTATISTICSOBSERVER_H
#define GAMESTATISTICSOBSERVER_H

class GameStatisticsObservable; //forward declaration

class GameStatisticsObserver : public AbstractStatsObserver
{
private:
	GameStatisticsObservable* subject;
	AbstractStatsObserver* decorator;
	bool hasDecorator = false;

	//data received from update()
	int numCitiesInfected;	//number of cities infected by the players
	vector<int> numResourcesPerPlayer;	//total number of resources at each player possesion
	int numCubesOnMap;	//the number of disease cubes on the map
	int numResourcesRemaining; //the remaining resources as a supply available during the game

public:
	GameStatisticsObserver(GameStatisticsObservable* subject);
	GameStatisticsObserver(GameStatisticsObservable* subject, AbstractStatsObserver* decorator);
	~GameStatisticsObserver();

	void update(); //sets stats and displays it on console
};

#endif

