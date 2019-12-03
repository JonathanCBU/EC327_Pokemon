#ifndef MODEL_H
#define MODEL_H

#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "View.h"
#include "BattleArena.h"
#include <list>
#include <iterator>


class Model {
 private:
  //Private Members
  int time;

  list<GameObject*> object_ptrs;
  list<GameObject*> active_ptrs;
  list<Pokemon*> pokemon_ptrs;
  list<PokemonCenter*> center_ptrs;
  list<PokemonGym*> gym_ptrs;
  list<Rival*> rival_ptrs;
  list<BattleArena*> arena_ptrs;
  
  //Copy Constructor
  Model(const Model&);

 public:
  //Constructor & Destructor
  Model();
  ~Model();

  //Public Member Functions
  Pokemon* GetPokemonPtr(int);
  void addPokemon(int, Point2D);
  PokemonCenter* GetPokemonCenterPtr(int);
  void addCenter(int, Point2D);
  PokemonGym* GetPokemonGymPtr(int);
  void addGym(int, Point2D);
  BattleArena* GetPokemonArenaPtr(int);
  Rival* GetRivalPtr(int);
  void addRival(int, Point2D);
  bool Update();
  void Display(View&);
  void ShowStatus();
};

#endif
