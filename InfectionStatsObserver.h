#pragma once
#include <vector>
#include "AbstractStatsObserver.h"
using namespace std;

#ifndef INFECTIONSTATSOBSERVER_H
#define INFECTIONSTATSOBSERVER_H

class GameStatisticsObservable; //forward declaration

class InfectionStatsObserver : public AbstractStatsObserver
{
public:
	GameStatisticsObservable* subject;
	AbstractStatsObserver* decorator;
	bool hasDecorator = false;

	int numCubesRemaining;

	InfectionStatsObserver(GameStatisticsObservable* subject);
	InfectionStatsObserver(GameStatisticsObservable* subject, AbstractStatsObserver* decorator);
	~InfectionStatsObserver();


	void update(); //sets stats and displays it on console
};

#endif
