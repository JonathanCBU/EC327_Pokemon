#ifndef MODEL_H
#define MODEL_H
#include "Pokemon.h"
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
    Rival * GetRivalPtr(int id);
    BattleArena * GetBattleArenaPtr(int id);
    bool Update();
    void Display(View& view);
    void ShowStatus();

    private:
    Model(const Model& M); // copy constructor
    
    int time;

    list <GameObject*> object_ptrs;

    list <GameObject*> active_ptrs;

    list <Pokemon*> pokemon_ptrs;

    list <PokemonCenter*> center_ptrs;

    list <PokemonGym*> gym_ptrs;

    // new members from PA4
    list <Rival*> rival_ptrs;

    list <BattleArena*> arena_ptrs;
};
#endif
