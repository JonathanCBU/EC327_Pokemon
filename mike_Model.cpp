#include "Model.h"

//***Constructors & Destructors
//Done
Model::Model(const Model& cpy) {

  this->object_ptrs = cpy.object_ptrs;
  this->active_ptrs = cpy.active_ptrs;
  this->pokemon_ptrs = cpy.pokemon_ptrs;
  this->center_ptrs = cpy.center_ptrs;
  this->gym_ptrs = cpy.gym_ptrs;
  this->rival_ptrs = cpy.rival_ptrs;
  this->arena_ptrs = cpy.arena_ptrs;  
}
Model::Model() {
  this -> time = 0;
  
  Point2D pm1(5, 1);
  Point2D pm2(10, 1);
  Point2D pc1(1, 20);
  Point2D pc2(10, 20);
  Point2D pg2(5,5);
  Point2D pr1(15, 12);
  Pokemon* Pokemon1 = new Pokemon("Mikey", 1, 20, 5, 4, 15, 2, 'P', pm1);
  Pokemon* Pokemon2 = new Pokemon("Ibrahim", 2, 20, 5, 4, 15, 1, 'P', pm2);
  PokemonCenter* PokeCenter1 = new PokemonCenter(1, 1, 100, pc1);
  PokemonCenter* PokeCenter2 = new PokemonCenter(2, 2, 200, pc2);
  PokemonGym* PokeGym1 = new PokemonGym;
  PokemonGym* PokeGym2 = new PokemonGym(20, 5, 7.5, 8, 2, pg2);
  BattleArena* BattleArena1 = new BattleArena(3, 3, 2.5, 1, pr1);
  Rival* Rival1 = new Rival("Densmore", 1, 20, 5, 4, 15, 1, pr1, BattleArena1);
  Rival* Rival2 = new Rival("Burak", 1, 20, 5, 4, 15, 2, pr1, BattleArena1);
  Rival* Rival3 = new Rival("Derek", 1, 20, 5, 4, 15, 3, pr1, BattleArena1);

  this->object_ptrs.push_back(Pokemon1);
  this->object_ptrs.push_back(Pokemon2);
  this->pokemon_ptrs.push_back(Pokemon1);
  this->pokemon_ptrs.push_back(Pokemon2);

  this->object_ptrs.push_back(PokeCenter1);
  this->object_ptrs.push_back(PokeCenter2);
  this->center_ptrs.push_back(PokeCenter1);
  this->center_ptrs.push_back(PokeCenter2);
  
  this->object_ptrs.push_back(PokeGym1);
  this->object_ptrs.push_back(PokeGym2);
  this->gym_ptrs.push_back(PokeGym1);
  this->gym_ptrs.push_back(PokeGym2);
  
  this->object_ptrs.push_back(BattleArena1);
  this->arena_ptrs.push_back(BattleArena1);

  this->object_ptrs.push_back(Rival1);
  this->object_ptrs.push_back(Rival2);
  this->object_ptrs.push_back(Rival3);
  this->rival_ptrs.push_back(Rival1);
  this->rival_ptrs.push_back(Rival2);
  this->rival_ptrs.push_back(Rival3);

  this->active_ptrs.push_back(Pokemon1);
  this->active_ptrs.push_back(Pokemon2);
  this->active_ptrs.push_back(PokeCenter1);
  this->active_ptrs.push_back(PokeCenter2);
  this->active_ptrs.push_back(PokeGym1);
  this->active_ptrs.push_back(PokeGym2);
  this->active_ptrs.push_back(BattleArena1);
  this->active_ptrs.push_back(Rival1);
  this->active_ptrs.push_back(Rival2);
  this->active_ptrs.push_back(Rival3);
  cout << "Model default constructed" << endl;
}
Model::~Model() {

  list<GameObject*>::iterator it;
  for(it=this->object_ptrs.begin(); it != this->object_ptrs.end(); ++it) {
    delete *it;
  }

  cout << "Model destructed." << endl;
}

//***Member Functions
Pokemon* Model::GetPokemonPtr(int id) {

  Pokemon* ptr = NULL;  

  list<Pokemon*>::iterator it;
  for (it = this->pokemon_ptrs.begin(); it != this->pokemon_ptrs.end(); ++it) {
    if((*it)->GetId() == id) {
      ptr = *it;
    }
  }


  return ptr;
} 

PokemonCenter* Model::GetPokemonCenterPtr(int id) {

  PokemonCenter* ptr = NULL;  

  list<PokemonCenter*>::iterator it;
  for (it = this->center_ptrs.begin(); it != this->center_ptrs.end(); ++it) {
    if((*it)->GetId() == id) {
      ptr = *it;
    }
  }
  

  return ptr;
}

PokemonGym* Model::GetPokemonGymPtr(int id) {

  PokemonGym* ptr = NULL;  

  list<PokemonGym*>::iterator it;
  for (it = this->gym_ptrs.begin(); it != this->gym_ptrs.end(); ++it) {
    if((*it)->GetId() == id) {
      ptr = *it;
    }
  }

  return ptr;
}

BattleArena* Model::GetPokemonArenaPtr(int id) {
  
  BattleArena* ptr = NULL;  

  list<BattleArena*>::iterator it;
  for (it = this->arena_ptrs.begin(); it != this->arena_ptrs.end(); ++it) {
    if((*it)->GetId() == id) {
      ptr = *it;
    }
  }

  //or return empty
  return ptr;
} 

Rival* Model::GetRivalPtr(int id) {

  Rival* ptr = NULL;  

  list<Rival*>::iterator it;
  for (it = this->rival_ptrs.begin(); it != this->rival_ptrs.end(); ++it) {
    if((*it)->GetId() == id) {
      ptr = *it;
    }
  }

  return ptr;
}

bool Model::Update() {
  //variables for running
  bool update = false;
  bool gym = true;
  bool exhausted = true;
  bool arena = true;
  int activenum = 0;
  int pokenum = 0;
  
  //incriment time
  this -> time += 1;

  list<GameObject*>::iterator GOit;
  for(GOit=this->object_ptrs.begin(); GOit != this->object_ptrs.end(); ++GOit) {
    if ((*GOit)->Update()) {
      update = true;
    }
    //Remove Dead objects
    if ((*GOit)->GetCode() == 'p' || (*GOit)->GetCode() == 'r' || (*GOit)->GetCode() == 'c' || (*GOit)->GetCode() == 'g' || (*GOit)->GetCode() == 'a') {
      this->active_ptrs.remove(*GOit);
      cout << "Dead object removed" << endl;
    }
  }
  
  //check gyms
  list<PokemonGym*>::iterator PGit;
  for (PGit=this->gym_ptrs.begin(); PGit != this->gym_ptrs.end(); ++PGit) {
    if (!(*PGit)->IsBeaten()) {
      gym = false;
    }
  }
  

  //Fix
  list<Pokemon*>::iterator it;
  for (it = this->pokemon_ptrs.begin(); it != this->pokemon_ptrs.end(); ++it) {
    if((*it)->GetCode() == 'P') {
      exhausted = false;
    }
  }

  //check if arena is beaten
  list<BattleArena*>::iterator Ait;
  for (Ait = this->arena_ptrs.begin(); Ait != this->arena_ptrs.end(); ++Ait) {
    if (!(*Ait)->IsBeaten()) {
      arena = false;
    }
  }
  
  //gyms beaten
  if(gym) {
    cout << "GAMEOVER: You win! All Pokemon Gyms beaten!" << endl;
    exit(0);
  }

  //pokemon exhausted
  if(exhausted) {
    cout << "GAME OVER: You lose! All of your Pokemon are tired!" << endl;
    exit(0);
  }

  if(arena) {
    cout << "GAME OVER: You Win! No more rivals remaining!" << endl;
    exit(0);
  }

  return update;
  
}

//plot all objects
void Model::Display(View& view) {

  list<GameObject*>::iterator it;
  for(it=this->active_ptrs.begin(); it != this->active_ptrs.end(); ++it) {
    view.Plot(*it);
  }
  
  return;
}

void Model::ShowStatus() {

  cout << "Time: " << this->time << endl;  
  list<GameObject*>::iterator it;
  for(it=this->object_ptrs.begin(); it != this->object_ptrs.end(); ++it) {
    (*it)->ShowStatus();
  }
  
  return;  
}

void Model::addPokemon(int id, Point2D loc) {

  Pokemon* Pokemon1 = new Pokemon("NewPokemon", 2, 20, 5, 4, 15, id, 'P', loc);

  this->object_ptrs.push_back(Pokemon1);
  this->active_ptrs.push_back(Pokemon1);
  this->pokemon_ptrs.push_back(Pokemon1);
  
  return;
}

void Model::addCenter(int id, Point2D loc) {

  PokemonCenter* Pokecenter = new PokemonCenter(id, 2, 20, loc);

  this->object_ptrs.push_back(Pokecenter);
  this->active_ptrs.push_back(Pokecenter);
  this->center_ptrs.push_back(Pokecenter);
  
  return;
}

void Model::addGym(int id, Point2D loc) {

  PokemonGym* Pokegym = new PokemonGym(20, 3, 4, 8, id, loc);

  this->object_ptrs.push_back(Pokegym);
  this->active_ptrs.push_back(Pokegym);
  this->gym_ptrs.push_back(Pokegym);
  
  return;
}

void Model::addRival(int id, Point2D loc) {

  Rival* Rival1 = new Rival("NewRival", 2, 20, 5, 4, 15, id, loc, NULL);

  this->object_ptrs.push_back(Rival1);
  this->active_ptrs.push_back(Rival1);
  this->rival_ptrs.push_back(Rival1);
  
  return;
}
