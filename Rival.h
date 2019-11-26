#ifndef RIVAL_H
#define RIVAL_H
#include "BattleArena.h"
using namespace std;

enum RivalStates {
	FAINTED_RIVAL = 1;
	ALIVE_RIVAL = 0;
}

class Rival: public GameObject
{
	public:
	Rival(string name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int id, Point2D in_loc);

	void TakeHit(double physical_damage, double magical_damage, double defense);
	double get_phys_dmg();
	double get_magic_dmg();
	double get_defense();
	double get_health();
	bool Update();
	void ShowStatus();

	protected:
	string name;
	double health;
    double physical_damage;
    double magical_damage;
    double defense;
    bool is_in_arena;
    BattleArena* current_arena;
};
#endif