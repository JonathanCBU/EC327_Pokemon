#include "Rival.cpp"

// constructor (no default yet because not specified in doc; may add later)
Rival::Rival(string name, double hp, double phys_dmg, double magic_dmg, double def, int id, Point2D in_loc): GameObject(in_loc, id, 'R')
{
	this -> name = name;
    this -> health = hp;
    this -> physical_damage = phys_dmg;
    this -> magic_damage = magic_dmg;
    this -> defense = def;
    this -> is_in_arena = false;
    this -> current_arena = NULL;
}