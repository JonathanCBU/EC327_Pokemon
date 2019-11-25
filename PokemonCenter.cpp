#include "PokemonCenter.h"
// contructors
PokemonCenter::PokemonCenter(): Building()
{
    this -> display_code = 'C';
    this -> stamina_capacity = 100;
    this -> num_stamina_points_remaining = stamina_capacity;
    this -> dollar_cost_per_stamina_point = 5;
    this -> state = STAMINA_POINTS_AVAILABLE; // state set to 0
    cout << "Pokemon Center default constructed" << endl;
}

PokemonCenter::PokemonCenter(int in_Id, double stamina_cost, unsigned int stamina_cap, Point2D in_loc): Building('C', in_Id, in_loc)
{
    this -> stamina_capacity = stamina_cap;
    this -> num_stamina_points_remaining = stamina_capacity;
    this -> dollar_cost_per_stamina_point = stamina_cost;
    this -> state = STAMINA_POINTS_AVAILABLE;
    cout << "Pokemon Center constructed" << endl;
}

// public member functions
bool PokemonCenter::HasStaminaPoints()
{
    if (this -> num_stamina_points_remaining > 0) {
        return true;
    } else {
        return false;
    }
}

unsigned int PokemonCenter::GetNumStaminaPointsRemaining()
{
    return this -> num_stamina_points_remaining;
}

bool PokemonCenter::CanAffordStaminaPoints(unsigned int stamina_points, double budget)
{
    if (budget >= stamina_points * this -> dollar_cost_per_stamina_point) {
        // pokemon can afford desired points at this center's unit price
        return true;
    } else {
        return false;
    }
}

double PokemonCenter::GetDollarCost(unsigned int stamina_points)
{
    return stamina_points * this -> dollar_cost_per_stamina_point;
}

unsigned int PokemonCenter::DistributeStamina(unsigned int points_needed) // set default in PokemonCenter.h
{
    if (this -> num_stamina_points_remaining >= points_needed) {
        // center does not use up all its stamina left
        this -> num_stamina_points_remaining = this -> num_stamina_points_remaining - points_needed;
        return points_needed;
    } else {
        // center will use up all remaining points
        unsigned int num_points_to_give; // store points to use up
        this -> num_stamina_points_remaining = 0;
        return num_points_to_give; // return what was left in center
    }
}

bool PokemonCenter::Update()
{
    if (this -> num_stamina_points_remaining <= 0 && this -> state != NO_STAMINA_POINTS_AVAILABLE) {
        this -> state = NO_STAMINA_POINTS_AVAILABLE; // sate set to 1
        this -> display_code = 'c'; // indicates stamina is out
        cout << "PokemonCenter " << this -> id_num << " has run out of stamina points" << endl;
        return true;
    } else {
        return false;
    }
}

void PokemonCenter::ShowStatus()
{
    cout << "Pokemon Center Status: ";
    Building::ShowStatus();
    cout << "\tPokemon dollars per stamina point: " << this -> dollar_cost_per_stamina_point << endl;
    cout << "\thas " << this -> num_stamina_points_remaining << " stamina point(s) remaining" << endl;
}

PokemonCenter::~PokemonCenter()
{
  cout << "PokemonCenter destructed" << endl;
}
