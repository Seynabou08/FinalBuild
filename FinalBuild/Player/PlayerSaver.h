#pragma once
#include "AbstractBuilder.h"
#include "Map.h"
#include "EventCard.h"
#include "Role.h"
#include "Player.h"


class PlayerSaver : public AbstractBuilder
{
private:
	Player* player;

public:
	PlayerSaver(Player* player) {
		this->player = player;
	}
	// ~PlayerSaver();

	void Save() // Player* player)
	{
		cout << "TRYING TO SAVE MAP" << endl;
		ofstream myfile;
		int num = player->getId();
		num++;
		std::string numId = to_string(num);
		myfile.open("player" + numId + "save.txt");

		if (myfile.is_open()) {

			myfile << numId << ' ' << player->getLocation() << ' ' << player->getRole()  << ' ' << player->getPawn() << endl;

			for (int i = 0; i < player->getHandSize(); i++)
			{
				myfile << player->getHand()[i]->getType() << '-' << player->getHand()[i]->getName() << '-' << player->getHand()[i]->getId() << endl;
			}


			cout << "SAVE SUCCESSFUL" << endl;
		}
		else {
			cout << "COULD NOT CREATE SAVE FILE" << endl;
		}

		myfile.close();

	}


	void Load(ifstream* myfile) // , Player* player)
	{
		int num = player->getId();
		string numId = to_string(num);
		myfile->open("player" + numId + "save.txt");

		string line;
		string lineToBeInputed;



		if (myfile->is_open())
		{
			int i = 0;
			while (getline(*myfile, line))
			{
				//Getting the id
				getline(*myfile, lineToBeInputed, ' ');
				player->setId(stoi(lineToBeInputed));

				//Getting the location
				getline(*myfile, lineToBeInputed, ' ');
				player->setLocation(stoi(lineToBeInputed));

				//Getting the role
				getline(*myfile, lineToBeInputed, '-');
				string s1 = lineToBeInputed;
				getline(*myfile, lineToBeInputed, '-');
				string s2 = lineToBeInputed;
				getline(*myfile, lineToBeInputed, ' ');
				int j = stoi(lineToBeInputed);
				Role rcard = Role(s2, j);
				player->setRole(rcard);

				const char *charac = lineToBeInputed.c_str();
				const char c = *charac;
				player->setPawn(c);


				//Getting the hand
				vector<Card*> cards;
				//player->getHand[i]->getName() << " " << player->getHand[i]->getId << endl;
				if (myfile->is_open()) 
				{
					getline(*myfile, lineToBeInputed, '-');
					string s1 = lineToBeInputed;

					getline(*myfile, lineToBeInputed, '-');
					string s2 = lineToBeInputed;

					getline(*myfile, lineToBeInputed, ' ');
					int j = stoi(lineToBeInputed);

					if (s1 == "city card")
					{
						City* city = &City(j);
						CityCard* ccard = &CityCard(city);
						cards.push_back(ccard);
					}
					else if (s1 == "event card")
					{
						EventCard* ecard = &EventCard(s2,j);
						cards.push_back(ecard);
					}


				}
				myfile->close();
			}

			myfile->close();

		}

	}
};
