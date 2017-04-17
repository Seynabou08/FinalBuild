#include "../Player/Player.h"
#include "../Map/Map.h"
using namespace std;

#ifndef PLAYERACTION_H
#define PLAYERACTION_H
class PlayerAction
{
	public:
		PlayerAction();
		~PlayerAction();
		void flow(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
	
	private:
		virtual bool execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck)=0;
		
};
#endif

#ifndef ACTIONENV_H
#define ACTIONENV_H
class ActionEnvelope
{
	public:
		ActionEnvelope();
		~ActionEnvelope();
		void setAct(char choice);
		void flow(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
		
	private:
		PlayerAction *act;
	
};
#endif

#ifndef DRIVE_H
#define DRIVE_H
class Drive : public PlayerAction
{
	public:
		Drive();
		~Drive();

	private:	
		bool execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
};
#endif

#ifndef DFLIGHT_H
#define DFLIGHT_H

class DFlight : public PlayerAction
{
public:
	DFlight();
	~DFlight();

private:
	bool execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
};
#endif

#ifndef CFLIGHT_H
#define CFLIGHT_H
class CFlight : public PlayerAction
{
public:
	CFlight();
	~CFlight();

private:
	bool execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
};
#endif

#ifndef SFLIGHT_H
#define SFLIGHT_H
class SFlight : public PlayerAction
{
public:
	SFlight();
	~SFlight();

private:
	bool execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
};
#endif

#ifndef BUILTRESEARCH_H
#define BUILTRESEARCH_H
class BuildResearch : public PlayerAction
{
public:
	BuildResearch();
	~BuildResearch();

private:
	bool execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
};
#endif

#ifndef TREATDISEASE_H
#define TREATDISEASE_H
class TreatDisease : public PlayerAction
{
public:
	TreatDisease();
	~TreatDisease();

private:
	bool execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
};
#endif

#ifndef SHAREKNOWLEDGE_H
#define SHAREKNOWLEDGE_H
class ShareKnowledge : public PlayerAction
{
public:
	ShareKnowledge();
	~ShareKnowledge();

private:
	bool execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
};
#endif

#ifndef DISCOVERCURE_H
#define DISCOVERCURE_H
class DiscoverCure : public PlayerAction
{
public:
	DiscoverCure();
	~DiscoverCure();

private:
	bool execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
};
#endif

#ifndef PLAYEVENT_H
#define PLAYEVENT_H
class PlayEvent : public PlayerAction
{
public:
	PlayEvent();
	~PlayEvent();

private:
	bool execute(Player* p1, vector<Player> players, Map* m, int d, InfectionDeck* ideck);
};
#endif

#ifndef USERROLE_H
#define USERROLE_H
#endif


