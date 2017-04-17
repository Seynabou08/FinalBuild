#include "Role.h"

Role::Role(string n, int i):Card(n,'r', i)
{
    rCard=Card();

}

Role::Role():Card("null", 'r', 0)
{
    rCard=Card();
}

Role::~Role(){}

void Role::setRole(string role, int a)
{
	this->assignedRole=role;
	this->setName("role card");
	this->setId(a);
}

string Role::getRole()
{
	return this->assignedRole;
}


void Role::printRole()
{
    cout<<"This role is that of "<<this->getName()<<", id: "<<this->getId()<<endl;
}


/*void Role::contingencyPlannerAct(vector<Card> &deck)
{
    char choice='0';
    int deckSize=deck.size();

    if(cCard.getId()!=0)
        this->cCard.printCard();

    while((choice!='Y' || choice!='N') && cCard.getId()!=0)
    {
        cout<<"You already have a card saved, would you like to play it? (Y/N)"<<endl;
        cin >> choice;
    }
    if(choice == 'Y')
    {
        //play cCard
    }
   /* else
    {
        for(int i=0; i<deckSize; i++)
        {
            if (deck[i].getType()=='e')
            {
                deck[i].printCard();
                while(choice!='Y' || choice!='N')
                {
                    cout<<"Would you like to take the previous card (Y/N)?"<<endl;
                    cin >> choice;
                }
                if(choice == 'Y')
                {
                    this->cCard=deck[i];
                    deck.erase(deck.begin()+i);
                    i=deckSize; //break
                }
            }
        }
    }
}

void Role::dispatcherAct(vector<Card> &hand, int city, Map m)
{
    
}*/

