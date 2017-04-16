#include "GameStatisticsObserver.h"
#include "GameStatisticsObservable.h"
#include <iostream>

GameStatisticsObserver::GameStatisticsObserver(GameStatisticsObservable * subject)
{
	this->subject = subject;
	subject->attach(this);
}

GameStatisticsObserver::GameStatisticsObserver(GameStatisticsObservable * subject, AbstractStatsObserver * decorator)
{
	this->decorator = decorator;
	hasDecorator = true;
	this->subject = subject;
	subject->attach(this);
}

GameStatisticsObserver::~GameStatisticsObserver()
{
}

void GameStatisticsObserver::update()
{
	//update data
	this->numCitiesInfected = subject->numCitiesInfected;
	this->numResourcesPerPlayer = subject->numResourcesPerPlayer;
	this->numCubesOnMap = subject->numCubesOnMap;
	this->numResourcesRemaining = subject->numResourcesRemaining;

	//display data
	cout << "----------Stats----------" << endl;
	cout << "Cities infected: " << this->numCitiesInfected << endl;
	cout << "Resources per player: ";
	for (int i = 0; i < numResourcesPerPlayer.size(); i++) {
		if (i < numResourcesPerPlayer.size() - 1)
			cout << numResourcesPerPlayer[i] << ", ";
		else
			cout << numResourcesPerPlayer[i] << endl;
	}
	cout << "Cubes on map: " << this->numCubesOnMap << endl;
	cout << "Resources remaining: " << this->numResourcesRemaining << endl;
	if (hasDecorator) {
		decorator->update();
	}
	cout << "-------------------------" << endl;
}
