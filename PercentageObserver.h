#pragma once
#include <vector>
#include "AbstractStatsObserver.h"
using namespace std;

#ifndef PERCENTAGEOBSERVER_H
#define PERCENTAGEOBSERVER_H

class GameStatisticsObservable; //forward declaration

class PercentageObserver : public AbstractStatsObserver
{
public:
	GameStatisticsObservable* subject;
	AbstractStatsObserver* decorator;
	bool hasDecorator = false;

	double percentCitiesInfected; //percentage of cities that are infected

	PercentageObserver(GameStatisticsObservable* subject);
	PercentageObserver(GameStatisticsObservable* subject, AbstractStatsObserver* decorator);
	~PercentageObserver();


	void update(); //sets stats and displays it on console
};

#endif
