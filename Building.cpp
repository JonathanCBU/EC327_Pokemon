#include "Building.h"
// constructors
Building::Building(): GameObject('B')
{ 
    this -> pokemon_count = 0;
    cout << "Building default constructed" << endl;
}

Building::Building(char in_code, int in_Id, Point2D in_loc): GameObject(in_loc, in_Id, in_code)
{
    this -> pokemon_count = 0;
    this -> state = 0;
    cout << "Building constructed" << endl;
}

// member functions
void Building::AddOnePokemon()
{
    this -> pokemon_count++;
}

void Building::RemoveOnePokemon()
{
    this -> pokemon_count--;
}

void Building::ShowStatus()
{
    GameObject::ShowStatus(); // access parent function

    cout << endl << "\t" << this -> pokemon_count;
    if ( this -> pokemon_count == 1 ) {
        cout << " pokemon is in this building" << endl;
    } else {
        cout << " pokemon are in this building" << endl;
    }
}

bool Building::ShouldBeVisible()
{
    return true;
}