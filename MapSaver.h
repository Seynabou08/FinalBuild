#pragma once
#include "AbstractBuilder.h"
#include "Map.h"

class MapSaver : public AbstractBuilder
{
private:
	Map* map;

public:

	MapSaver(Map* map) {
		this->map = map;
	}

	void Load(ifstream* myfile)
	{
		string line;
		string lineToBeInputed;


		if (myfile->is_open())
		{
			int i = 0;
			while (getline(*myfile, line))
			{
				//when it reads the first element it reads and sets the index of the city to the value read. We convert that string to an integer using stoi
				getline(*myfile, lineToBeInputed, ' ');
				map->cities[i]->index = stoi(lineToBeInputed);


				//when it reads the second element it reads and sets the name of the city to the value read.
				getline(*myfile, lineToBeInputed, ' ');
				map->cities[i]->name = lineToBeInputed;


				//when it reads the 3rd element it changes the boolean of the city to the value read.
				getline(*myfile, lineToBeInputed, ' ');
				if (lineToBeInputed == "false") map->cities[i]->infected = false;
				else map->cities[i]->infected = true;

				//when it reads the 4th element it sets the infection level of the city to the values read. We convert that string to an integer using stoi
				getline(*myfile, lineToBeInputed, ' ');

				map->cities[i]->infectionLevel = stoi(lineToBeInputed);


				//when it reads the 5th element it changes the boolean of the city to the values read.
				getline(*myfile, lineToBeInputed, ' ');
				if (lineToBeInputed == "false") map->cities[i]->researchCenter = false;
				else map->cities[i]->researchCenter = true;; //need to convert string to city
				i++;
			}
			myfile->close();
		}

		myfile->close();

	}

	void Save()
	{
		cout << "TRYING TO SAVING MAP" << endl;
		ofstream myfile;
		myfile.open("save.txt");

		if (myfile.is_open()) {
			for (int i = 0; i < 48; i++) {
				myfile << map->cities[i]->index << ' ' << map->cities[i]->name << ' ' <<
					map->cities[i]->infected << ' ' << map->cities[i]->infectionLevel << ' ' << map->cities[i]->researchCenter << '\n';
			}
			cout << "SAVE SUCCESSFUL" << endl;
		}
		else {
			cout << "COULD NOT CREATE SAVE FILE" << endl;
		}

		myfile.close();
	}
};