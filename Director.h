#pragma once
#include "MapSaver.h"
#include "PlayerSaver.h"
#include <iostream>
#include <fstream>
class Director
{
private:
	AbstractBuilder *builder;

public:
	ifstream myfile;
	/*
	Director();
	~Director();
	*/
	void setBuilder(AbstractBuilder *builder) { this->builder = builder; }

	void ConstructMap()
	{
		builder->Load(&myfile);
	}
	void ConstructPlayer(Player* player)
	{
		builder->Load(&myfile);     //, player);
	}

	void SaveMap()
	{
		builder->Save();
	}
	void SavePlayer(Player* player)
	{
		builder->Save();        // player);
	}

};