#include "Rival.h"

// constructor (no default yet because not specified in doc; may add later)
Rival::Rival(string name, double hp, double phys_dmg, double magic_dmg, double def, int id, Point2D in_loc): GameObject(in_loc, id, 'R')
{
	this -> name = name;
    this -> health = hp;
    this -> physical_damage = phys_dmg;
    this -> magical_damage = magic_dmg;
    this -> defense = def;
    this -> is_in_arena = false;
    this -> current_arena = NULL;
    this -> state = ALIVE_RIVAL;
}

void Rival::TakeHit(double physical_damage, double magic_damage, double defense)
{
    int dmg_type = rand() & 1; // chooses 1 or 0 with equal probability
    double damage = 0.0; // damage to subtract from health
    if(dmg_type == 0) {
        // randomly selected magic damage
        damage = (100.0 - defense) / 100 * magic_damage;
    } else {
        damage = (100.0 - defense) / 100 * physical_damage;
    }
    this -> health -= damage; // subtract damage from health
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

// Update and ShowStatus functions which have become the worst part of these PAs
bool Rival::Update()
{   
    if(this -> IsAlive()) {
        // rival is still alive
        return false;
    } else {
        // rival has fainted
        return true;
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