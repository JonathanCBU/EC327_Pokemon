#ifndef MODEL_H
#define MODEL_H
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
using namespace std;

class Model
{
    public:
    Model();
    ~Model();

    Pokemon * GetPokemonPtr(int id);
    PokemonCenter * GetPokemonCenterPtr(int id);
    PokemonGym * GetPokemonGymPtr(int id);
    bool Update();
    void Display(View& view);
    void ShowStatus();

    private:
    Model(const Model& M); // copy constructor
    int time;
    GameObject* object_ptrs[10];
    int num_objects;

    Pokemon* pokemon_ptrs[10];
    int num_pokemon;

    PokemonCenter* center_ptrs[10];
    int num_centers;

    PokemonGym* gym_ptrs[10];
    int num_gyms;
};
#endif
