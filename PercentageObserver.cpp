#include "PercentageObserver.h"
#include "GameStatisticsObservable.h"
#include <iostream>

PercentageObserver::PercentageObserver(GameStatisticsObservable * subject)
{
	this->subject = subject;
	subject->attach(this);
}

PercentageObserver::PercentageObserver(GameStatisticsObservable * subject, AbstractStatsObserver * decorator)
{
	this->decorator = decorator;
	hasDecorator = true;
	this->subject = subject;
	subject->attach(this);
}

PercentageObserver::~PercentageObserver()
{
}

void PercentageObserver::update()
{
	this->percentCitiesInfected = subject->percentCitiesInfected;
	cout << "Cities infected(%) " << this->percentCitiesInfected << endl;
	if (hasDecorator) {
		decorator->update();
	}
}
