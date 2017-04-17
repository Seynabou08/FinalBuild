#pragma once
#include "../Map/MapSaver.h"
#include "../Player/PlayerSaver.h"
#include <iostream>
#include <fstream>
class Director
{
private:
	AbstractBuilder *builder;

public:
	ifstream myfile;

	Director();
	~Director();

	void setBuilder(AbstractBuilder *builder) { this->builder = builder; }

	void ConstructMap(MapSaver* mapSaver)
	{
		mapSaver->Load(&myfile);
	}
	void ConstructPlayer(PlayerSaver* playerSaver, Player* player)
	{
		playerSaver->Load(&myfile, player);
	}

	void SaveMap(MapSaver* mapSaver)
	{
		mapSaver->Save();
	}
	void SavePlayer(PlayerSaver* playerSaver, Player* player)
	{
		playerSaver->Save(player);
	}

};