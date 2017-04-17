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
	switch (ch)
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

void Player::buildStation(Map* m)
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
		}
	}
	else cout << "None of your city card match the city you are in so you can't build a research station. Choose another action." << endl;

}

void Player::treatDisease(Map m)
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
	}
	else
	{
		//city has no infection to remove
	}
	delete[] cp; //not sure if we need this or not
}

void Player::shareKnowledge(Player* tg)
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
				}
				else {
					//take card
					(this->cards).push_back(tg->getHand()[cardIndex]);   //adds card to hand of this player
					newHand = tg->getHand();                           //creates new hand for tg
					newHand.erase(newHand.begin() + cardIndex);         //removes card from new hand
					tg->setHand(newHand);                            //replaces old hand of tg
					this->subtractAction();
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
				}
				else {
					//give card
					newHand = tg->getHand();                             //similar logic
					newHand.push_back((this->getHand())[cardIndex]);
					tg->setHand(newHand);
					(this->cards).erase((this->cards).begin() + cardIndex);
					this->subtractAction();
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
}

void Player::discoverCure(Map m)
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
				return;
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
			}
			else if (areRepeatInput) {
				cout << "You inputted the same index more than once..." << endl;
			}
			else if (!areSameColor) {
				cout << "You must input 5 cards of the same color" << endl;
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
				return;
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
			}
			else if (areRepeatInput) {
				cout << "You inputted the same index more than once..." << endl;
			}
			else if (!areSameColor) {
				cout << "You must input 5 cards of the same color" << endl;
			}
		}
	}
	else {
		cout << "You must be at a research station to discover a cure" << endl;
	}
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

	while (choice < 0 || choice >= players->size() || choice == playerIndex) cin >> choice;

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

	}
}

void Player::useEventCard(int i, int playerNum, InfectionDeck ideck, Map newMap)
{/*

	int choice = i;
	int cityChoice;
	int cardId;
	int num = 0;

	//check for event card
	// DOESNT TAKE IN ACCOUNT IF THE PLAYER HAS MORE THAN ONE EVENT CARD
	bool hasEventCard = false;
	bool contingencyPlannner = false;
	char answer;
	Card* eventc;
	int matchingCardIndex;

	if (this->getRole() == "Contingency Planner" && this->getEventCard().getType() == "Event Card") {
		cout << "You are a contingency planner, do you want to use your assigned event card or an event card in your hand? Enter 'y' for yes or 'n' for no:" << endl;
		cin >> answer;
		while (answer != 'y' || answer != 'n') cout << "Enter 'y' for yes or 'n' for no:" << endl;
	}

	if (answer == 'y')

		this->contingencyPlanner(i, playerNum, ideck, newMap);

		}

	else
		
		
		(hasEventCard) {

		cout << "Which event card do you own?" << endl;

		cout << "1: Airlift" << endl;
		cout << "2: Resilient population" << endl;
		cout << "3: Government Grant" << endl;
		cout << "4: Forcast" << endl;
		cout << "5: Use Contingency role" << endl;

		while (num > 5 || num <= 0)
		{
			cin >> num;
			if (num > 5 || num <= 0) {
				cout << "You must choose an integer between 1 and 5!" << endl;
			}
		}

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

				if (this->getRole() == "Contingency Planner")
					this->removeEvent();

				else
					this->discard(cardId);
			}
			break;
		}

		case 2: // Resilient population
		{
			int discard;

			ideck.showDiscardPile();

			cout << "Which card do you want to remove from the game?" << endl;
			cin >> discard;

			if (this->getRole() == "Contingency Planner")
				this->removeEvent();

			else
				this->discard(cardId);

			break;
		}

		case 3: // Government Grant
		{

			cout << "In which city do you want to add a reserch center?";
			cin >> cityChoice;
			while (cityChoice <= 0 || cityChoice > 48) cin >> cityChoice;

			this->buildStation(&newMap);
			this->increaseAction();

			if (this->getRole() == "Contingency Planner")
				this->removeEvent();

			else
				this->discard(cardId);

			break;
		}


		case 4: // Forcast event card
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

				if (this->getRole() == "Contingency Planner")
					this->removeEvent();

				else
					this->discard(cardId);

			}

			break;
		}

		case 5:
			if (this->getRole() == "Contingency Planner" && this->getEventCard().getType() == "Event Card") {

			}
			break;


		}
	}
	else
		//cout << "You don't own an event card. Choose another action." << endl;
		if (this->getEventCard().getType() == "Event Card") {
			cout << i << this->getEventCard().getName() << endl;
			hasEventCard = true;

		}



	/*	if (this->getRole() != "Contingency Planner" || this->getEventCard().getType() != "Event Card") {
	for (int j = 0; j < this->getHandSize(); j++) {
	if (this->getHand()[j]->getType() == "Event Card") {
	cout << i << this->getHand()[j]->getName() << endl;
	cardId = j;
	num = this->getHand()[j]->getId();
	hasEventCard = true;
	}

	}
	}

	else if (this->getEventCard().getType() == "Event Card") {
	cout << i << this->getEventCard().getName() << endl;
	cardId = j;
	num = this->getHand()[j]->getId();
	hasEventCard = true;



	}
	*/

}

void Player::contingencyPlanner(int i, int playerNum, InfectionDeck ideck, Map newMap)
{/*

	int choice = i;
	int cityChoice;
	int cardId;
	int num = 0;


	int num = this->getEventCard().getId();

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

		break;
	}
	}*/
}




int Player::getHandSize() {
	return this->cards.size();
}




