#include "GameStatisticsObservable.h"

GameStatisticsObservable::GameStatisticsObservable(int numPlayers)
{
	numResourcesPerPlayer = vector<int>(numPlayers);	//have to initialize
}

GameStatisticsObservable::~GameStatisticsObservable()
{
}

void GameStatisticsObservable::attach(AbstractStatsObserver * ob)
{
	this->obs.push_back(ob);
}

void GameStatisticsObservable::detach(AbstractStatsObserver * ob)
{
	for (int i = 0; i < obs.size(); i++) {
		if (obs[i] == ob) {
			obs.erase(obs.begin() + i);
			return;
		}
	}
}

void GameStatisticsObservable::notify()
{
	for (int i = 0; i < obs.size(); i++) {
		obs[i]->update();
	}
}

void GameStatisticsObservable::updateCitiesInfected(vector<City*> cities)
{
	this->numCitiesInfected = 0;
	for (int i = 0; i < cities.size(); i++) {
		if (cities[i]->infectionLevel > 0) {
			this->numCitiesInfected++;
		}
	}

	this->percentCitiesInfected = this->numCitiesInfected / (double)cities.size();
}

void GameStatisticsObservable::updateNumResourcesPerPlayer(vector<Player> players)
{
	for (int i = 0; i < players.size(); i++) {
		this->numResourcesPerPlayer[i] = players.at(i).getHandSize();	//resources might mean more than number of cards?
	}
}

void GameStatisticsObservable::updateNumCubesOnMap(vector<City*> cities)
{
	this->numCubesOnMap = 0;
	for (int i = 0; i < cities.size(); i++) {
		this->numCubesOnMap += cities[i]->getInfection();
	}
}

void GameStatisticsObservable::updateNumResourcesRemaining(vector<Card*> deck)
{
	this->numResourcesRemaining = deck.size();
}

void GameStatisticsObservable::updateNumCubesRemaining(InfectionDeck * deck)
{
	this->numCubesRemaining = deck->infectionCubes;
}