#include "BattleArena.h"
// constructors
BattleArena::BattleArena(): Building()
{
	this -> display_code = 'A';
	this -> max_num_rivals = 3;
	this -> num_rivals_remaining = 3;
	this -> dollar_cost_per_fight = 4.0;
	this -> stamina_cost_per_fight = 3;
	this -> state = RIVALS_AVAILABLE;

	cout << "BattleArena default constructed" << endl;
}

BattleArena::BattleArena(unsigned int max_rivals, unsigned int stamina_cost, double dollar_cost, int in_Id, Point2D in_loc): Building('A', in_Id, in_loc)
{
	this -> max_num_rivals = max_rivals;
	this -> num_rivals_remaining = max_rivals;
	this -> dollar_cost_per_fight = dollar_cost;
	this -> stamina_cost_per_fight = stamina_cost;
	this -> state = RIVALS_AVAILABLE;

	cout << "BattleArena constructed" << endl;
}

// getters for private members
unsigned int BattleArena::GetNumRivalsRemaining()
{
	return this -> num_rivals_remaining;
}

double BattleArena::GetDollarCost()
{
	return this -> dollar_cost_per_fight;
}

unsigned int BattleArena::GetStaminaCost()
{
	return this -> stamina_cost_per_fight;
}

// other member functions
bool BattleArena::HasEnoughRivals()
{
	if(this -> num_rivals_remaining > 0) {
		// arena has at least one rival left
		return true;
	} else {
		// arena is out of rivals
		return false;
	}
}

bool BattleArena::IsAbleToFight(double budget, unsigned int stamina)
{
	if(budget >= this -> dollar_cost_per_fight && stamina >= this -> stamina_cost_per_fight) {
		// pokemon is able to battle with given stamina and dollar amount
		return true;
	} else {
		return false;
	}
}

bool BattleArena::IsBeaten()
{
	if(this -> num_rivals_remaining <= 0) {
		// arena is out of rivals
		return true;
	} else {
		return false;
	}
}

void BattleArena::RemoveOneRival()
{
	this -> num_rivals_remaining -= 1;
}

bool BattleArena::Update()
{
	if(this -> IsBeaten() && this -> state == RIVALS_AVAILABLE) {
		// arena has no more rivas, but state has not been changed to reflect beaten status
		this -> state = NO_RIVALS_AVAILABLE;
		this -> display_code = 'a';
		return true;
	} else {
		// arena is not beaten or this function has already returned true
		return false;
	}
}

void BattleArena::ShowStatus()
{
	cout << "Battle Arena Status: ";
	Building::ShowStatus();
	cout << "\tMax number of rivals: " << this -> max_num_rivals << endl <<
			"\tStamina cost per fight: " << this -> stamina_cost_per_fight << endl <<
			"\tDollar cost per fight: " << this -> dollar_cost_per_fight << endl <<
			"\t" << this -> num_rivals_remaining << " rival(s) are remaining for this arena" << endl;
}
