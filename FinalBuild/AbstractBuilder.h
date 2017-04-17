#pragma once
#include "Map/Map.h"
#include "Player/Player.h"

class AbstractBuilder
{
public:
	AbstractBuilder() {};

	~AbstractBuilder()
	{

	}
	//Destructor made virtual
	/*
	virtual ~AbstractBuilder()
	{
		delete player;
		delete map;
		player = NULL;
		map = NULL;
	}
	*/
	
	virtual void Load(ifstream* myfile) = 0;
	virtual void Save() = 0;

};