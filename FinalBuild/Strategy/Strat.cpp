#include "Strat.h"
PlayerAction::PlayerAction(){}
PlayerAction::~PlayerAction(){}
void PlayerAction::flow(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
	if(execute(p1, players, m, d, ideck))
		p1->subtractAction(); 
	else
		cout << "action unsuccessfull; no moves subtracted" << endl;
}
	
ActionEnvelope::ActionEnvelope()
{
	this->act = NULL;
}
ActionEnvelope::~ActionEnvelope(){}
void ActionEnvelope::setAct(char choice)
{
	switch(choice)
	{
		case '1':
		{
			this->act = new Drive();
			break;
		}
		case '2':
		{
			this->act = new DFlight();
			break;
		}
		case '3':
		{
			this->act = new CFlight();
			break;
		}
		case '4':
		{
			this->act = new SFlight();
			break;
		}
		case '5':
		{
			this->act = new BuildResearch();
			break;
		}		
		case '6':
		{
			this->act = new TreatDisease();
			break;
		}		
		case '7':
		{
			this->act = new ShareKnowledge();
			break;
		}		
		case '8':
		{
			this->act = new DiscoverCure();
			break;
		}		
		case '9':
		{
			this->act = new PlayEvent();
			break;
		}		
	}
}
void ActionEnvelope::flow(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
	this->act->flow(p1, players,  m, d, ideck);
}


Drive::Drive(){}
Drive::~Drive(){}
bool Drive::execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
	if (p1->getRole() == "Dispatcher") //d is used as player num
	{
		int choice = 0;
		cout << "Which player's pawn do you want to move?";
		cin >> choice;
		while (choice > d || choice <= 0) {
			cout << "Please enter a number between 1 and " << d <<"." << endl;
			cin >> choice;
		}
	}
	(*m).showCity(p1->getLocation());
	p1->move(*m);
	p1->increaseAction(); //action is automatically subtracted in move
	return true;
}

DFlight::DFlight(){}
DFlight::~DFlight(){}
bool DFlight::execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
					if (p1->getRole() == "Dispatcher")
					{
						int choice = 0;
						cout << "Which player's pawn do you want to move?";
						cin >> choice;
						while (choice > d || choice <= 0) {
							cout << "Please enter a number between 1 and " << d << "." << endl;
							cin >> choice;
						}
					}

					p1->displayHand();

					if (p1->getHandSize() == 0)
					{
						cout << "You are out of city cards select another action." << endl;
						return false;
					}

					cout << "Which city do you want to move to" << endl;

					int cardInt = -1;
					while (cardInt == -1 || cardInt >= p1->getHandSize()) {
						cin >> cardInt;
					}

					p1->flight(p1->getHand()[cardInt]->getId());
					p1->increaseAction();
					p1->discard(cardInt);
					return true;
}

CFlight::CFlight(){}
CFlight::~CFlight(){}
bool CFlight::execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
	if (p1->getRole() == "Dispatcher")
					{
		char choice;
						cout << "Which player's pawn do you want to move?";
						cin >> choice;
						while (choice > d || choice <= 0) {
							cout << "Please enter a number between 1 and " << d <<"." << endl;
							cin >> choice;
						}

					}				

					//check for matching card
					bool hasMatchingCard = false;
					int matchingCardIndex;
					for (int j = 0; j < p1->getHandSize(); j++) {
						if (p1->getHand()[j]->getId() == p1->getLocation()) {
							hasMatchingCard = true;
							matchingCardIndex = j;
						}
					}

					if (hasMatchingCard) {

						//SHOW ALL CITIES AND IDs
						for (int k = 0; k < (*m).cities.size(); k++) {
							cout << "(" << k << ") " << (*m).cities[k]->getName() << endl;
						}

						cout << "Choose a city to fly to" << endl;

						int cityID;
						cin >> cityID;
						p1->flight(cityID);
						p1->increaseAction();
						p1->discard(matchingCardIndex);
					}
					else {
						cout << "You cannot take a charter flight as you do not have a card matching the city you are currently on" << endl;
						return false;
					}
					return true;
}

SFlight::SFlight(){}
SFlight::~SFlight(){}
bool SFlight::execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
		
					int choice = 0;

					City* location = (*m).accessCity(p1->getLocation());
					vector<int> validCities; //indexes of cities with research stations

					if (location->researchCenter == true)
					{

						if (p1->getRole() == "Dispatcher")
						{
							cout << "Which player's pawn do you want to move?";
							cin >> choice;
							while (choice > d || choice <= 0) {
								cout << "Please enter a number between 1 and " << d << "." << endl;
								cin >> choice;
							}
						}

						for (int j = 0; j < 47; j++)
						{
							City* newLoc = (*m).accessCity(j);
							if (newLoc->researchCenter == true)
							{
								cout << newLoc->accessCity() << " : " << newLoc->getName();
								validCities.push_back(newLoc->accessCity());
							}
						}

						bool isValidCity = false;

						while (!isValidCity) {

							int newLocation;
							cout << "Enter the ID of the city you want to move to:" << endl;
							cin >> newLocation;
							if (newLocation == 123)
								return false; //loop cancelled
							//verify if valid city
							for (int k = 0; k < validCities.size(); k++) {
								if (newLocation == validCities[k]) {
									isValidCity = true;
								}
							}

							if (isValidCity) {
								p1->flight(newLocation);
								p1->increaseAction();
								p1->subtractAction();
								return true;
							}
						}
					}
					return false;
}	

BuildResearch::BuildResearch(){}
BuildResearch::~BuildResearch(){}
bool BuildResearch::execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
	p1->increaseAction();
	return p1->buildStation(m);
}

TreatDisease::TreatDisease(){}
TreatDisease::~TreatDisease(){}
bool TreatDisease::execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
	p1->increaseAction();
	return p1->treatDisease(*m);
}	

ShareKnowledge::ShareKnowledge(){}
ShareKnowledge::~ShareKnowledge(){}
bool ShareKnowledge::execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
	int pc;
	p1->increaseAction();
	cout << "Which player would you like to share knowledge with?" << endl;
	cin >> pc;
	if (pc<1 || pc>d)
	{
		cout << "that player doesn't exist!" << endl;
		return false;
	}
	return p1->shareKnowledge(&players.at(pc));
}

DiscoverCure::DiscoverCure(){}
DiscoverCure::~DiscoverCure(){}
bool DiscoverCure::execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
	p1->increaseAction();
	return p1->discoverCure(*m);
}

PlayEvent::PlayEvent(){}
PlayEvent::~PlayEvent(){}
bool PlayEvent::execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)
{
					int choice = 0;
					int cityChoice;
					int cardId;
					int num;

					//check for event card
					// DOESNT TAKE IN ACCOUNT IF THE PLAYER HAS MORE THAN ONE EVENT CARD
					bool hasMatchingCard = false;
					int matchingCardIndex;
					if (p1->getRole() != "Contingency Planner" || p1->getEventCard().getType() != "Event Card") {
						for (int j = 0; j < p1->getHandSize(); j++) {
							if (p1->getHand()[j]->getType() == "Event Card") {
								cout << p1->getHand()[j]->getName() << endl;
								cardId = j;
								num = p1->getHand()[j]->getId();
							}
						}
					}


					switch (num) {
					case'1':
					{

						cout << "Which player's pawn do you want to move?";
						cin >> choice;
						while (choice <= 0 || choice > d) cin >> choice;

						cout << "Which city do you want to move it to?";
						cin >> cityChoice;
						while (cityChoice <= 0 || cityChoice > 48) cin >> cityChoice;
						//test this out
						//p1->flight(cityChoice);
						(&players.at(choice))->flight(p1->getHand()[cityChoice]->getId());
						(&players.at(choice))->increaseAction();
						(&players.at(choice))->increaseAction();

						if (p1->getRole() == "Contingency Planner")
							p1->removeEvent();

						else
							p1->discard(cardId);

						return true;
						break;
					}

					case'3': //take a card from the discard pile of infection cards and remove it from game
					{
						int discard;

						(*ideck).showDiscardPile();

						cout << "Which card do you want to remove from the game?" << endl;
						cin >> discard;

						if (p1->getRole() == "Contingency Planner")
							p1->removeEvent();

						else
							p1->discard(cardId);

						return true;
						break;
					}

					case'4':
					{

						cout << "In which city do you want to add a reserch center?";
						cin >> cityChoice;
						while (cityChoice <= 0 || cityChoice > 48) cin >> cityChoice;

						p1->buildStation(m);
						p1->increaseAction();

						if (p1->getRole() == "Contingency Planner")
							p1->removeEvent();

						else
							p1->discard(cardId);

						return true;
						break;
					}


					case'5': //examine the top 6 cards of the infection deck and rearrange them to your liking
					{
						int ind;
						vector<InfectionCard> temp;


						for (int j = 0; j < 6; j++)
						{
							temp.push_back((*ideck).deck.front());
							cout << (*ideck).deck.at(j).getCityName() << endl;
						}

						string numbers[] = { "sixth","fifth","forth","third","second","first" };

						for (int j = 0; j < 6; j++) {

							cout << "Which card do you want to be in the " << numbers[j] << " position?" << endl;
							cin >> ind;

							(*ideck).deck.at(5 - j) = temp.at(ind);
							temp.at(ind) = temp.back();
							temp.pop_back();


							for (int k = 0; k < temp.size(); k++)
							{
								cout << temp.at(k).getCityName() << endl;
							}

							if (p1->getRole() == "Contingency Planner")
								p1->removeEvent();

							else
								p1->discard(cardId);
						}

						return true;
						break;
					}
				}
				return false;
}


	