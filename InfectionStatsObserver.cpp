#include "InfectionStatsObserver.h"
#include "GameStatisticsObservable.h"
#include <iostream>



InfectionStatsObserver::InfectionStatsObserver(GameStatisticsObservable * subject)
{
	this->subject = subject;
	subject->attach(this);
}

InfectionStatsObserver::InfectionStatsObserver(GameStatisticsObservable * subject, AbstractStatsObserver * decorator)
{
	this->decorator = decorator;
	hasDecorator = true;
	this->subject = subject;
	subject->attach(this);
}

InfectionStatsObserver::~InfectionStatsObserver()
{
}

void InfectionStatsObserver::update()
{
	this->numCubesRemaining = subject->numCubesRemaining;
	cout << "Cubes remaining: " << this->numCubesRemaining << endl;
	if (hasDecorator) {
		decorator->update();
	}
}
