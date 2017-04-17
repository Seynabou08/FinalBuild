#include "Player.h"

Player::Player(Map map, char p, vector<Role> &roleDeck, vector<Card*> &cardDeck, int pCount, int i)
{
	this->location = 7; //Atlanta is location 7
	this->cards = vector<Card*>(20);
	switch (pCount) //draws cards based on player count
	{
	case 1:
		drawCards(map, cardDeck, 4);
		break;
	case 2:
		drawCards(map, cardDeck, 4);
		break;
	case 3:
		drawCards(map, cardDeck, 3);
		break;
	case 4:
		drawCards(map, cardDeck, 2);
		break;
	}
	this->role = roleDeck[roleDeck.size() - 1];
	roleDeck.pop_back();

	//Choosing a color
	switch (p)
	{
	case 'b':
		this->pawn = BLUE;
		break;

	case 'g':
		this->pawn = GREEN;
		break;

	case 'r':
		this->pawn = RED;
		break;

	case 'y':
		this->pawn = YELLOW;
		break;

	case 'x':
		this->pawn = BLACK;
		break;

	}
	this->rc = ReferenceCard();
	this->id = i;
}

Player::Player()
{
	this->location = 7;
	this->cards = vector<Card*>();
	this->role = Role();
	this->pawn = BLACK;
	this->rc = ReferenceCard();
	this->id = 0;
}
Player::~Player()
{
	this->cards.clear();
}

vector<Card*> Player::getHand()
{
	return this->cards;
}

void Player::setHand(vector<Card*> c)
{
	this->cards = c;
}


void Player::setRole(Role rCard)
{
	this->role = rCard;
}

Card Player::getEventCard()
{
	return eCard;
}

string Player::getRole()
{
	return this->role.getRole();
}

City Player::getCity()
{
	return city;
}

void Player::setPawn(char ch)
{
	switch(ch)
	{
	case 'b':
		this->pawn = BLUE;
		break;

	case 'g':
		this->pawn = GREEN;
		break;

	case 'r':
		this->pawn = RED;
		break;

	case 'y':
		this->pawn = YELLOW;
		break;

	case 'x':
		this->pawn = BLACK;
		break;
	}
}

void Player::setId(int i)
{
	id = i;
}

void Player::setLocation(int i)
{
	location = i;
}

char Player::getPawn()
{
	switch (this->pawn)
	{
	case BLUE:
		return 'b';

	case RED:
		return 'r';

	case YELLOW:
		return 'y';

	case GREEN:
		return 'g';

	case BLACK:
		return 'x';

	default:
		return 'x';
	}
}

int Player::getId()
{
	return this->id;
}

int Player::getLocation()
{
	return this->location;
}


///////////PRINT FUNCTIONS/////////////////////

void Player::printPossessions()
{
	cout << "Player id: " << this->id << endl;
	cout << "Player location: " << this->location << endl;
	switch (this->pawn)
	{
	case BLUE:
		cout << "Player pawn: blue" << endl;
		break;

	case RED:
		cout << "Player pawn: red" << endl;
		break;

	case YELLOW:
		cout << "Player pawn: yellow" << endl;
		break;

	case GREEN:
		cout << "Player pawn: green" << endl;
		break;

	default:
		cout << "Player pawn: black" << endl;;
	}

	cout << "Player cards: " << endl;
	this->displayHand();
	cout << "Player Role: " << this->role.getName() << endl;
	cout << "Player reference card: " << endl;
	this->printReference();
}

void Player::displayHand()
{
	for (int i = 0; i < cards.size(); i++)
	{
		cout << "Card at index " << i << ": " << cards[i]->getName() << endl;
	}
}

void Player::displayHandWithColors()
{
	for (int i = 0; i < cards.size(); i++)
	{
		cout << "Card at index " << i << ": " << cards[i]->getName() << " (" << cards[i]->getColor() << ")" << endl;
	}
}

void Player::printReference()
{
	this->rc.displayCard();
}

void Player::displayActionsLeft()
{
	cout << "Actions remaining: " << this->actionsLeft << endl;
}
//////////AUTOMATIC ACTIONS//////////////////
void Player::startTurn()
{
	actionsLeft = 4;
}

void Player::subtractAction()
{
	actionsLeft--;
}

void Player::increaseAction()
{
	this->actionsLeft++;
}

void Player::concludeTurn(vector<Card*> &deck, Map map)
{
	this->drawCards(map, deck, 2);
}

void Player::drawCards(Map map, vector<Card*> &deck, int num)	//Changing so that pointer is passed
{
	int userCards = this->cards.size(); //number of cards in user hand
	int lastCard = deck.size(); //index of last card
	if (lastCard == 0) //if deck runs out
	{
		//game over
	}

	else //draw
	{
		for (int a = 0; a < num; a++)
		{
			if (deck.back()->getName() == "Epidemic Card")
			{
				/*EpidemicCard* epCard;
				epCard = deck.back();
				epCard->playCard(map);*/
			}
			else
			{
				this->cards.push_back(deck.back());
				deck.pop_back();
			}
		}
	}
}

//  returns true if the user still has actions left this turn.

bool Player::checkAction()
{
	if (actionsLeft == 0)
		return false;
	else
		return true;
}

void Player::discard(int a)
{
	//vector<Card*> cards = this->getHand(); //does it make a copy
	//cards[a] = cards.back();
	//cards.pop_back();

	this->cards[a] = this->cards.back();
	this->cards.pop_back();
}

////////PLAYER ACTIONS/////////////////////////////////
void Player::move(Map m)
{
	//This method was supposed to make sire the player can only drive to neighbouring cities, we will try to fix the error.
	//the player can drive anywhere but wont be shown any option but the neighbouring cities.

	vector<City*> cities = m.getConnectedCities(this->location);
	vector<int> cityIndex;
	bool correctInput = false;
	int choice;
	cout << "Select the index of the city you would like to drive to: " << endl;
	for (int i = 0; i < cities.size(); i++) //print possible cities player can drive to
	{
		//cout << cities[i]->index << " : " << cities[i]->getName() << endl;
		cityIndex.push_back(cities[i]->index);
	}
	cities.clear();

	while (!correctInput) //get player input with verification
	{
		cin >> choice;
		for (int i = 0; i < cityIndex.size(); i++)
		{
			if (choice == cityIndex[i])
				correctInput = true;
		}
		if (!correctInput)
			cout << "sorry, you have entered an invalid index" << endl;
	}
	this->location = choice;

	this->subtractAction();


}

void Player::flight(int a)
{
	int choice;

	choice = a;

	this->location = choice;

	this->subtractAction();
}

bool Player::buildStation(Map* m)
{

	bool hasMatchingCard = false;
	int matchingCardIndex;
	for (int j = 0; j < getHandSize(); j++) {
		if (getHand()[j]->getId() == getLocation()) {
			hasMatchingCard = true;
			matchingCardIndex = j;
		}
	}
	if (hasMatchingCard || (getRole() == "Operation Expert")) {
		if (m->researchStationNum > 0)
		{
			City* location = m->accessCity(getLocation());
			location->setResearchCenter(true);

			cout << "A research station was built in " << location->getName() << endl;
			m->researchStationNum--;
			this->subtractAction();
			if (getRole() != "Operation Expert")
				discard(matchingCardIndex);
			return true;
		}
	}
	return false;

}

bool Player::treatDisease(Map m)
{
	int loc = this->location;
	City c;
	char cityColor;
	City* cp = m.accessCity(loc);
	c = *cp;
	cityColor = c.getColor();
	if (c.infected == true) //if the city has infection cubes
	{
		if ((cityColor == 'b' && m.blueCure) || (cityColor == 'y' && m.yellowCure) || (cityColor == 'w' && m.whiteCure) || (cityColor == 'r' && m.redCure))
		{   //if cure for city is discovered
			c.setInfectionLevel(0);
			c.setInfection(false);
		}
		else if (this->getRole() == "Medic") {	//medic always removes every infection
			c.setInfectionLevel(0);
			c.setInfection(false);
		}
		else
		{
			c.decrementInfection();
			if (c.getInfection() == 0)
				c.setInfection(false);
		}
		*cp = c;
		this->subtractAction();
		return true;
	}
	else
	{
		return false;
		//city has no infection to remove
	}
	delete[] cp; //not sure if we need this or not
}

bool Player::shareKnowledge(Player* tg)
{//TODO CHANGE SO THAT YOU CAN ONLY GIVE THE CARD CORRESPONDING TO THE CITY YOU'RE BOTH IN
	if (this->checkAction())
	{
		char option;
		int index;
		vector<Card*> newHand;

		if (this->location == tg->getLocation()) {
			cout << "Press 't' to take a card, and 'g' to give one" << endl;
			cin >> option;
			if (option == 't')
			{
				int cardIndex = -1; //the card index of the card matching the city in tg's hand
				for (int i = 0; i < tg->getHandSize(); i++) {
					if (tg->getHand()[i]->getId() == this->location) {
						cardIndex = i;
					}
				}
				if (cardIndex == -1) {
					cout << "The other player does not have the card for the city" << endl;
					return false;
				}
				else {
					//take card
					(this->cards).push_back(tg->getHand()[cardIndex]);   //adds card to hand of this player
					newHand = tg->getHand();                           //creates new hand for tg
					newHand.erase(newHand.begin() + cardIndex);         //removes card from new hand
					tg->setHand(newHand);                            //replaces old hand of tg
					this->subtractAction();
					return true;
				}
			}
			else if (option == 'g')
			{
				int cardIndex = -1; //the card index of the card matching the city in tg's hand
				for (int i = 0; i < this->getHandSize(); i++) {
					if (this->getHand()[i]->getId() == this->location) {
						cardIndex = i;
					}
				}
				if (cardIndex == -1) {
					cout << "You do not have the card for the city" << endl;
					return false;
				}
				else {
					//give card
					newHand = tg->getHand();                             //similar logic
					newHand.push_back((this->getHand())[cardIndex]);
					tg->setHand(newHand);
					(this->cards).erase((this->cards).begin() + cardIndex);
					this->subtractAction();
					return true;
				}
			}
			else
			{
				cout << "Invalid Option. Try again." << endl;
			}
		}

		//Researcher specific action
		if (this->location == tg->getLocation() && (this->getRole() == "Researcher" || tg->getRole() == "Researcher"))
		{
			cout << "Press 't' to take a card, and 'g' to give one" << endl;
			cin >> option;
			if (option == 't')
			{
				cout << "Player " << tg->getId() << "s hand: " << endl;
				tg->displayHand();
				cout << "Enter the index you want to take the card from" << endl;
				cin >> index;
				(this->cards).push_back(tg->getHand()[index]);   //adds card to hand of this player
				newHand = tg->getHand();                           //creates new hand for tg
				newHand.erase(newHand.begin() + index);         //removes card from new hand
				tg->setHand(newHand);                            //replaces old hand of tg
				this->subtractAction();
				return true;
			}
			else if (option == 'g')
			{
				cout << "Player" << this->id << " hand: " << endl;
				this->displayHand();
				cout << "Enter the index you want to take the card from" << endl;
				cin >> index;
				newHand = tg->getHand();                             //similar logic
				newHand.push_back((this->getHand())[index]);
				tg->setHand(newHand);
				(this->cards).erase((this->cards).begin() + index);
				this->subtractAction();
				return true;
			}
			else
			{
				cout << "Invalid Option. Try again." << endl;
			}
			//cout << "Player" << this->id << " select the card you want " << endl;
		}

		else if (this->location != tg->getLocation())
		{
			cout << "Sorry, this player is not on this space" << endl;
		}
	}
	return false;
}

bool Player::discoverCure(Map m)
{
	if (m.accessCity(getLocation())->researchCenter) { //check to see if player is at research station
		if (this->getRole() != "Scientist") {
			displayHandWithColors();

			int cardInt1, cardInt2, cardInt3, cardInt4, cardInt5;

			cout << "Enter the ID of the cards you want to discard: (5 of same color)" << endl;

			cin >> cardInt1 >> cardInt2 >> cardInt3 >> cardInt4 >> cardInt5;

			if (cardInt1 >= getHandSize() ||
				cardInt2 >= getHandSize() ||
				cardInt3 >= getHandSize() ||
				cardInt4 >= getHandSize() ||
				cardInt5 >= getHandSize()
				) {
				cout << "Indexes selected were out of range" << endl;
				return false;
			}

			bool areSameColor = false;	//check to see if all cities are same color
			bool areRepeatInput = true; //check to make sure same card wasn't inputted twice
			if (
				m.accessCity(cardInt1)->getColor() == m.accessCity(cardInt2)->getColor() &&
				m.accessCity(cardInt1)->getColor() == m.accessCity(cardInt3)->getColor() &&
				m.accessCity(cardInt1)->getColor() == m.accessCity(cardInt4)->getColor() &&
				m.accessCity(cardInt1)->getColor() == m.accessCity(cardInt5)->getColor()
				) {
				areSameColor = true;
			}
			if (
				cardInt1 != cardInt2 && cardInt1 != cardInt3 && cardInt1 != cardInt4 && cardInt1 != cardInt5
				&& cardInt2 != cardInt3 && cardInt2 != cardInt4 && cardInt2 != cardInt5
				&& cardInt3 != cardInt4 && cardInt3 != cardInt5
				&& cardInt4 != cardInt5
				) {
				areRepeatInput = false;
			}


			if (areSameColor && !areRepeatInput) {
				if (areSameColor && !areRepeatInput) {
					char cityColor = m.accessCity(cardInt1)->getColor();
					if (cityColor == 'b')
						m.blueCure = true;
					else if (cityColor == 'y')
						m.yellowCure = true;
					else if (cityColor == 'w')
						m.whiteCure = true;
					else if (cityColor == 'r')
						m.redCure = true;
				}

				discard(cardInt1);
				discard(cardInt2);
				discard(cardInt3);
				discard(cardInt4);
				discard(cardInt5);
				return true;
			}
			else if (areRepeatInput) {
				cout << "You inputted the same index more than once..." << endl;
				return false;
			}
			else if (!areSameColor) {
				cout << "You must input 5 cards of the same color" << endl;
				return false;
			}
		}
		else {	//player is a scientist
			displayHandWithColors();

			int cardInt1, cardInt2, cardInt3, cardInt4;

			cout << "Enter the ID of the cards you want to discard: (4 of same color because SCIENTIST)" << endl;

			cin >> cardInt1 >> cardInt2 >> cardInt3 >> cardInt4;

			if (cardInt1 >= getHandSize() ||
				cardInt2 >= getHandSize() ||
				cardInt3 >= getHandSize() ||
				cardInt4 >= getHandSize()
				) {
				cout << "Indexes selected were out of range" << endl;
				return false;
			}

			bool areSameColor = false;	//check to see if all cities are same color
			bool areRepeatInput = true; //check to make sure same card wasn't inputted twice
			if (
				m.accessCity(cardInt1)->getColor() == m.accessCity(cardInt2)->getColor() &&
				m.accessCity(cardInt1)->getColor() == m.accessCity(cardInt3)->getColor() &&
				m.accessCity(cardInt1)->getColor() == m.accessCity(cardInt4)->getColor()
				) {
				areSameColor = true;
			}
			if (
				cardInt1 != cardInt2 && cardInt1 != cardInt3 && cardInt1 != cardInt4
				&& cardInt2 != cardInt3 && cardInt2 != cardInt4
				&& cardInt3 != cardInt4
				) {
				areRepeatInput = false;
			}


			if (areSameColor && !areRepeatInput) {
				if (areSameColor && !areRepeatInput) {
					char cityColor = m.accessCity(cardInt1)->getColor();
					if (cityColor == 'b')
						m.blueCure = true;
					else if (cityColor == 'y')
						m.yellowCure = true;
					else if (cityColor == 'w')
						m.whiteCure = true;
					else if (cityColor == 'r')
						m.redCure = true;
				}

				discard(cardInt1);
				discard(cardInt2);
				discard(cardInt3);
				discard(cardInt4);
				return true;
			}
			else if (areRepeatInput) {
				cout << "You inputted the same index more than once..." << endl;
				return false;
			}
			else if (!areSameColor) {
				cout << "You must input 5 cards of the same color" << endl;
				return false;
			}
		}
	}
	else {
		cout << "You must be at a research station to discover a cure" << endl;
		return false;
	}
	return false;
}

void Player::setEventCard(Card ecard)
{
	eCard = ecard;
}

void Player::removeEvent()
{
	Card card = Card();
	eCard = card;
}

void Player::dispatcherAbility(vector<Player>* players, Map* m, int playerIndex)
{
	int choice = playerIndex;
	int location;
	City* newLoc;

	cout << "Which player's pawn do you want to move?" << endl;
	cin >> choice;

	while (choice <= 0 || choice > players->size() || choice == playerIndex + 1) cin >> choice;
	choice--;	//players are displayed 1-4, but indexed 0-3

	cout << "Which ability do you want to do?" << endl;
	cout << "1: Move pawn to city containing another pawn" << endl;
	cout << "2: Move another player's pawn as if it was your own" << endl;

	int ability = 0;
	while (ability < 1 || ability > 2) {
		cin >> ability;
	}

	if (ability == 1) {	//move pawn to city containing another pawn
						//display list of cities with pawns on them
		cout << "Choose the city you want to move this player " << choice << " to " << endl;
		for (int i = 0; i < players->size(); i++) {
			cout << i << ": " << m->cities[players->at(i).getLocation()]->getName() << endl;
		}
		int cityChoice = -1;
		while (cityChoice < 0 || cityChoice >= players->size()) {
			cin >> cityChoice;
		}
		players->at(choice).setLocation(players->at(cityChoice).getLocation());
		players->at(playerIndex).subtractAction();
	}
	else if (ability == 2) { //move another player's pawn as if it was your own
		cout << "Choose type of movement:" << endl;
		cout << "1. Drive/Ferry" << endl;
		cout << "2. Direct Flight" << endl;
		cout << "3. Charter Flight" << endl;
		cout << "4. Shuttle Flight" << endl;

		int moveType = 0;
		while (moveType <= 0 || moveType >= 5) {
			cin >> moveType;
		}

		if (moveType == 1) {
			m->showCity(players->at(choice).getLocation());
			players->at(choice).move(*m);
			players->at(choice).increaseAction();
			players->at(playerIndex).subtractAction();
		}
		else if (moveType == 2) {
			players->at(playerIndex).displayHand();

			if (players->at(playerIndex).getHandSize() == 0)
			{
				cout << "You are out of city cards select another action." << endl;
				return;
			}

			cout << "Which city do you want to move to" << endl;

			int cardInt = -1;
			while (cardInt == -1 || cardInt >= players->at(playerIndex).getHandSize()) {
				cin >> cardInt;
			}
			players->at(choice).flight(players->at(playerIndex).getHand()[cardInt]->getId());
			players->at(playerIndex).discard(cardInt);
			players->at(choice).increaseAction();
			players->at(playerIndex).subtractAction();
		}
		else if (moveType == 3) {

			//check for matching card
			bool hasMatchingCard = false;		//TODO MATCHING WHOSE LOCATION?
			int matchingCardIndex;
			for (int j = 0; j < players->at(playerIndex).getHandSize(); j++) {
				if (players->at(playerIndex).getHand()[j]->getId() == players->at(playerIndex).getLocation()) {
					hasMatchingCard = true;
					matchingCardIndex = j;
				}
			}

			if (hasMatchingCard) {

				//SHOW ALL CITIES AND IDs
				for (int k = 0; k < m->cities.size(); k++) {
					cout << "(" << k << ") " << m->cities[k]->getName() << endl;
				}

				cout << "Choose a city to fly to" << endl;

				int cityID;
				cin >> cityID;
				players->at(choice).flight(cityID);
				players->at(playerIndex).discard(matchingCardIndex);
				players->at(choice).increaseAction();
				players->at(playerIndex).subtractAction();
			}
			else {
				cout << "You cannot take a charter flight as you do not have a card matching the city you are currently on" << endl;
			}
		}
		else if (moveType == 4) {
			City* location = m->accessCity(players->at(choice).getLocation());
			vector<int> validCities; //indexes of cities with research stations

			if (location->researchCenter == true) {
				for (int j = 0; j < 47; j++)
				{
					City* newLoc = m->accessCity(j);
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

					//verify if valid city
					for (int k = 0; k < validCities.size(); k++) {
						if (newLocation == validCities[k]) {
							isValidCity = true;
						}
					}

					if (isValidCity) {
						players->at(choice).flight(newLocation);
						players->at(choice).increaseAction();
						players->at(playerIndex).subtractAction();
						break;
					}
				}
			}
			else {
				cout << "Player is not located on a city with a research center" << endl;
			}
		}

	}
}

bool Player::useEventCard(int playerNum, InfectionDeck ideck, Map newMap)
{
	int choice = 0;
	int cityChoice;
	int cardId;
	int num = 0;

	//check for event card
	// DOESNT TAKE IN ACCOUNT IF THE PLAYER HAS MORE THAN ONE EVENT CARD
	bool hasEventCard = false;
	int matchingCardIndex;

	for (int j = 0; j < this->getHandSize(); j++) {
		if (this->getHand()[j]->getType() == "Event Card") {
			cout << j << " " << this->getHand()[j]->getId() << endl;
			cardId = j;
			num = this->getHand()[j]->getId();
			hasEventCard = true;
		}
	}
	if (hasEventCard) {

		/*cout << "Which event card will you use?" << endl;

		cout << "1: Airlift" << endl;
		cout << "3: Resilient population" << endl;
		cout << "4: Government Grant" << endl;
		cout << "5: Forcast" << endl;


		while (num > 5 || num <= 0)
		{
		cin >> cardId;
		if (cardId > 5 || cardId <= 0) {
		cout << "You must choose an integer between 1 and 4!" << endl;
		}
		}
		*/
		switch (num) {

		case 1: // Airlift
		{
			if (this->getHand()[cardId]->getName() == "Airlift") {
				cout << "Which player's pawn do you want to move?";
				cin >> choice;
				while (choice <= 0 || choice > playerNum) cin >> choice;

				cout << "Which city do you want to move it to?";
				cin >> cityChoice;
				while (cityChoice <= 0 || cityChoice > 48) cin >> cityChoice;

				//test this out
				//this->flight(cityChoice);

				this->flight(this->getHand()[cityChoice]->getId());

				if (this->getRole() == "Contingency Planner")
					this->removeEvent();

				else
					this->discard(cardId);
				return true;
			}
			else
			{
				cout << "you don't own this event card." << endl;
				return false;
			}

		}

		case 2: // Resilient population
		{
			if (this->getHand()[cardId]->getName() == "Resilient Population") {
				int discard;

				ideck.showDiscardPile();

				cout << "Which card do you want to remove from the game?" << endl;
				cin >> discard;

				if (this->getRole() == "Contingency Planner")
					this->removeEvent();

				else
					this->discard(cardId);

				return true;


			}
			else
			{
				cout << "you don't own this event card." << endl;
				return false;
			}
		}

		case 3: // Government Grant
		{

			if (this->getHand()[cardId]->getName() == "Government Grant") {
				cout << "In which city do you want to add a reserch center?";
				cin >> cityChoice;
				while (cityChoice < 0 || cityChoice > 48) cin >> cityChoice;

				newMap.cities[cityChoice]->setResearchCenter(true);
				//this->buildStation(&newMap);
				this->increaseAction();

				if (this->getRole() == "Contingency Planner")
					this->removeEvent();

				else
					this->discard(cardId);

				return true;


			}
			else
			{
				cout << "you don't own this event card." << endl;
				return false;
			}
		}


		case 4: // Forcast event card
		{
			if (this->getHand()[cardId]->getName() == "Forcast") {

				int ind;
				vector<InfectionCard> temp;


				for (int j = 0; j < 6; j++)
				{
					temp.push_back(ideck.deck.front());
					cout << ideck.deck.at(j).getCityName() << endl;
				}

				string numbers[] = { "sixth","fifth","forth","third","second","first" };

				for (int j = 0; j < 6; j++) {

					cout << "Which card do you want to be in the " << numbers[j] << " position?" << endl;
					cin >> ind;

					ideck.deck.at(5 - j) = temp.at(ind);
					temp.at(ind) = temp.back();
					temp.pop_back();


					for (int k = 0; k < temp.size(); k++)
					{
						cout << temp.at(k).getCityName() << endl;
					}

					if (this->getRole() == "Contingency Planner")
						this->removeEvent();

					else
						this->discard(cardId);

					return true;

				}

			}
			else
			{
				cout << "you don't own this event card." << endl;
				return false;
			}
		}

		}
	}
	else
	{
		cout << "You don't own an event card. Choose another action." << endl;
		return false;
	}


}

bool Player::contingencyPlanner( int playerNum, InfectionDeck ideck, Map newMap)
{
	int choice = 0;
	int cityChoice;
	int cardId;
	int num = 0;
	bool hasEventCard = false;
	bool contingencyPlannner = false;
	char answer;
	Card* eventc;
	int matchingCardIndex;

	cout << "You are a contingency planner, do you want to use your assigned event card or an event card in your hand? Enter 'y' for assigned event or 'n' for event card:" << endl;
	cin >> answer;
	while (answer != 'y' || answer != 'n') cout << "Enter 'y' or 'n':" << endl;


	if (answer == 'n')
		return this->useEventCard(playerNum, ideck, newMap);

	else if (answer == 'y') {

		num = this->getEventCard().getId();

		switch (num) {

		case 1: // Airlift
		{
			if (true) {
				cout << "Which player's pawn do you want to move?";
				cin >> choice;
				while (choice <= 0 || choice > playerNum) cin >> choice;

				cout << "Which city do you want to move it to?";
				cin >> cityChoice;
				while (cityChoice <= 0 || cityChoice > 48) cin >> cityChoice;

				//test this out
				//this->flight(cityChoice);

				this->flight(this->getHand()[cityChoice]->getId());

				this->removeEvent();
				return true;

			}
			break;
		}

		case 3: // Resilient population
		{
			int discard;

			ideck.showDiscardPile();

			cout << "Which card do you want to remove from the game?" << endl;
			cin >> discard;

			this->removeEvent();
			return true;

			break;
		}

		case 4: // Government Grant
		{

			cout << "In which city do you want to add a reserch center?";
			cin >> cityChoice;
			while (cityChoice <= 0 || cityChoice > 48) cin >> cityChoice;

			this->buildStation(&newMap);
			this->increaseAction();

			this->removeEvent();
			return true;

			break;
		}

		case 5: // Forcast event card
		{
			int ind;
			vector<InfectionCard> temp;


			for (int j = 0; j < 6; j++)
			{
				temp.push_back(ideck.deck.front());
				cout << ideck.deck.at(j).getCityName() << endl;
			}

			string numbers[] = { "sixth","fifth","forth","third","second","first" };

			for (int j = 0; j < 6; j++) {

				cout << "Which card do you want to be in the " << numbers[j] << " position?" << endl;
				cin >> ind;

				ideck.deck.at(5 - j) = temp.at(ind);
				temp.at(ind) = temp.back();
				temp.pop_back();


				for (int k = 0; k < temp.size(); k++)
				{
					cout << temp.at(k).getCityName() << endl;
				}

			}

			this->removeEvent();
			return true;

			break;
		}
		}
	}
	return false;
}



int Player::getHandSize() {
	return this->cards.size();
}




