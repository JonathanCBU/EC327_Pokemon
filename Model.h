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

    list <GameObject*> object_lst;
    list <GameObject*> active_ptrs;


    list <Pokemon*> pokemon_lst;

    list <PokemonCenter*> center_lst;

    list <PokemonGym*> gym_lst;

    // new members from PA4
    list <Rival*> rival_lst;

    list <BattleArena*> arena_lst;
};
#endif
