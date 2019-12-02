#include "Rival.h"

// constructor (no default yet because not specified in doc; may add later)
Rival::Rival(string name, double hp, double phys_dmg, double magic_dmg, double def, int id, Point2D in_loc, BattleArena* arena): GameObject(in_loc, id, 'R')
{
	this -> name = name;
    this -> health = hp;
    this -> physical_damage = phys_dmg;
    this -> magical_damage = magic_dmg;
    this -> defense = def;
    this -> is_in_arena = false;
    this -> current_arena = arena;
    this -> state = ALIVE_RIVAL;

    cout << "Rival constructed" << endl;
}

void Rival::TakeHit(double physical_damage, double magic_damage, double defense)
{
    int dmg_type = rand() & 1; // chooses 1 or 0 with equal probability
    double damage = 0.0; // damage to subtract from health
    if(dmg_type == 0) {
        // randomly selected magic damage
        damage = (100.0 - defense) / 100 * magic_damage;
	cout << this -> name << " was hit for " << damage <<
	  " points of magic damage!" << endl;
    } else {
        damage = (100.0 - defense) / 100 * physical_damage;
	cout << this -> name << " was hit for " << damage << 
	  " points of phyisical damge!" << endl;
    }
    this -> health -= damage; // subtract damage from health
    cout << "Health reduced to " << this -> health << endl;
    cout << "**********" << endl;
}

// getters for private members
double Rival::get_phys_dmg()
{
    return this -> physical_damage;
}

double Rival::get_magic_dmg()
{
    return this -> magical_damage;
}

double Rival::get_defense()
{
    return this -> defense;
}

double Rival::get_health()
{
    return this -> health;
}

// made by me to call remove rival when battle lost
BattleArena* Rival::get_arena()
{
  return this -> current_arena;
}

string Rival::get_name()
{
    return this -> name;
}

// Update and ShowStatus functions which have become the worst part of these PAs
bool Rival::Update()
{   
    if(!this -> IsAlive() && this -> state == ALIVE_RIVAL) {
        // rival is not alive but state has not been changed te reflect
        this -> state = FAINTED_RIVAL;
	this -> current_arena -> RemoveRival();
        return true; // only return true once
    } else {
        // rival is alive
        return false;
    }
}

void Rival::ShowStatus()
{
    cout << this -> name << " status: ";
    GameObject::ShowStatus();

    switch (this -> state)
    {
        case FAINTED_RIVAL: {
            cout << " fainted" << endl;
            break;
        }

        case ALIVE_RIVAL: {
            cout << " alive" << endl;
            break;
        }
    }

    cout << "\tHealth: " << this -> health << endl <<
        "\tPhysical Damage: " << this -> physical_damage << endl <<
        "\tMagical Damage: " << this -> magical_damage << endl <<
        "\tDefense: " << this -> defense << endl;
}

bool Rival::IsAlive()
{
    // set state based on rival health
    if(this -> health > 0) {
        // rival is still alive
        this -> state = ALIVE_RIVAL;
        return true;
    } else {
        // rival has fainted
        this -> state = FAINTED_RIVAL;
        return false;
    }
}

bool Rival::ShouldBeVisible()
{
  if(this -> IsAlive()) {
    // Rival is still alive
    return true;
  } else {
    return false;
  }
}

Rival::~Rival()
{
    cout << "Rival destructed" << endl;
}
