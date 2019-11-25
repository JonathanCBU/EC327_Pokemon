#include "PokemonGym.h"
// constructors
PokemonGym::PokemonGym(): Building()
{
    this -> display_code = 'G';
    this -> state = NOT_BEATEN;
    this -> max_number_of_training_units = 10;
    this -> num_training_units_remaining = max_number_of_training_units;
    this -> stamina_cost_per_training_unit = 1;
    this -> dollar_cost_per_training_unit = 1.0;
    this -> experience_points_per_training_unit = 2;
    cout << "PokemonGym default constructed" << endl;
}

PokemonGym::PokemonGym(unsigned int max_training_units, unsigned int stamina_cost, double
                        dollar_cost, unsigned int exp_points_per_unit, int in_id, 
                        Point2D in_loc): Building('G', in_id, in_loc)
{
    this -> max_number_of_training_units = max_training_units;
    this -> num_training_units_remaining = max_number_of_training_units;
    this -> stamina_cost_per_training_unit = stamina_cost;
    this -> experience_points_per_training_unit = exp_points_per_unit;
    this -> dollar_cost_per_training_unit = dollar_cost;
    this -> state = NOT_BEATEN;
    cout << "PokemonGym constructed" << endl;
}

// public member functions
double PokemonGym::GetDollarCost(unsigned int unit_qty)
{
    return this -> dollar_cost_per_training_unit * unit_qty;
}

unsigned int PokemonGym::GetStaminaCost(unsigned int unit_qty)
{
    return this -> stamina_cost_per_training_unit * unit_qty;
}

unsigned int PokemonGym::GetNumTrainingUnitsRemaining()
{
    return this -> num_training_units_remaining;
}

bool PokemonGym::IsAbleToTrain(unsigned int unit_qty, double budget, unsigned int stamina)
{
    if (budget >= this -> dollar_cost_per_training_unit * unit_qty && stamina >= this -> stamina_cost_per_training_unit * unit_qty) {
        return true;
    } else {
        return false;
    }
}

unsigned int PokemonGym::TrainPokemon(unsigned int training_units)
{
    if (this -> num_training_units_remaining - training_units >= 0) {
        // gym will not go negative if training all requested units
        this -> num_training_units_remaining = this -> num_training_units_remaining - training_units;
        return training_units * this -> experience_points_per_training_unit; // return number of exp gained
    } else {
        // gym will max out training and cannot complete full request
        unsigned int num_trained = this -> num_training_units_remaining; // store num_trained for return statement
        this -> num_training_units_remaining = 0;
        return num_trained * this -> experience_points_per_training_unit; // return number of exp gained
    }
}

bool PokemonGym::Update()
{
    if (this -> num_training_units_remaining <= 0 && this -> state == NOT_BEATEN) {
        // to run when gym is first beaten
        this -> state = BEATEN;
        this -> display_code = 'g';
        cout << this -> display_code << this -> id_num << " has been beaten." << endl;
        return true;
    } else {
        return false;
    }
}

bool PokemonGym::IsBeaten()
{
    if (this -> num_training_units_remaining == 0) {
        return true;
    } else {
        return false;
    }
}

void PokemonGym::ShowStatus() 
{
    cout << "Pokemon Gym Status: ";
    Building::ShowStatus();
    cout << "\tMax number of training units: " << this -> max_number_of_training_units << endl;
    cout << "\tStamina cost per training unit: " << this -> stamina_cost_per_training_unit << endl;
    cout << "\tPokemon dollar per training unit: " << this -> dollar_cost_per_training_unit << endl;
    cout << "\tExperience points per training unit: " << this -> experience_points_per_training_unit << endl;
    cout << "\t" << this -> num_training_units_remaining << " training unit(s) are remaining for this gym" << endl;
}
PokemonGym::~PokemonGym()
{
  cout << "PokemonGym destructed" << endl;
}
