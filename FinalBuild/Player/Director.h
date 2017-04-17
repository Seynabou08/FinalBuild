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
	
	void setBuilder(AbstractBuilder *builder) { this->builder = builder; }

	void ConstructMap(ifstream* myfile)
	{
		builder->Load(myfile);
	}
	void ConstructPlayer(ifstream* myfile)
	{
		builder->Load(myfile);  
	}

	void SaveMap()
	{
		builder->Save();
	}
	void SavePlayer()
	{
		builder->Save();  
	}

};