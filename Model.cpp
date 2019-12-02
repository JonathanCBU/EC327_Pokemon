#include "Model.h"
// constructor
Model::Model()
{
    this -> time = 0;

    // Create objects
    Pokemon* P_ptr1 = new Pokemon("Pikachu", 2, 23, 3, 6, 15, 1, 'P', Point2D(5, 1));
    Pokemon* P_ptr2 = new Pokemon("Bulbasaur", 1, 26, 4, 3.7, 15, 2, 'P', Point2D(10, 1));

    PokemonCenter* C_ptr1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    PokemonCenter* C_ptr2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));

    PokemonGym* G_ptr1 =  new PokemonGym(10, 1, 2.0, 3, 1, Point2D()); 
    PokemonGym* G_ptr2 = new PokemonGym(20, 5, 7.5, 8, 2, Point2D(5, 5));

    // PA4 new objects

    BattleArena* A_ptr1 = new BattleArena(2, 1, 1, 1, Point2D(15, 12));

    Rival* R_ptr1 = new Rival("Nate", 16, 3, 7.2, 15, 1, Point2D(15, 12), A_ptr1);
    Rival* R_ptr2 = new Rival("Noah", 29, 6.4, 3.6, 15, 2, Point2D(15, 12), A_ptr1);

    // add objects to object_lst by pushing to back
    this -> object_lst.push_back(P_ptr1);
    this -> object_lst.push_back(P_ptr2);
    this -> object_lst.push_back(C_ptr1);
    this -> object_lst.push_back(C_ptr2);
    this -> object_lst.push_back(G_ptr1);
    this -> object_lst.push_back(G_ptr2);
    this -> object_lst.push_back(R_ptr1);
    this -> object_lst.push_back(R_ptr2);
    this -> object_lst.push_back(A_ptr1);

    this -> pokemon_lst.push_back(P_ptr1);
    this -> pokemon_lst.push_back(P_ptr2);

    this -> center_lst.push_back(C_ptr1);
    this -> center_lst.push_back(C_ptr2);

    this -> gym_lst.push_back(G_ptr1);
    this -> gym_lst.push_back(G_ptr1);

    this -> rival_lst.push_back(R_ptr1);
    this -> rival_lst.push_back(R_ptr2);

    this -> arena_lst.push_back(A_ptr1);

    this -> active_ptrs = this -> object_lst;

    cout << "Model Default Constructed" << endl;
}

// dectructor
Model::~Model()
{

  for(list <GameObject*>::iterator it = object_lst.begin(); it != object_lst.end(); ++it) {
    delete *it;
  }
  cout << "Model destructed." << endl;
}

Pokemon* Model::GetPokemonPtr(int id)
{
  // loop through each list item using iterator
  for(list <Pokemon*>::iterator it = pokemon_lst.begin(); it != pokemon_lst.end(); ++it) {
    if((*it) -> GetId() == id) {
      return *it;
    }
  }
  return 0; // return 0 if none of the pokemon objects have matching id (assumes we don't need to error check here)
}

PokemonCenter* Model::GetPokemonCenterPtr(int id)
{
  // loop through each list item using iterator
  for(list <PokemonCenter*>::iterator it = center_lst.begin(); it != center_lst.end(); ++it) {
    if((*it) -> GetId() == id) {
      return *it;
    }
  }
  return 0; // return 0 if none of the center objects have matching id
}

PokemonGym* Model::GetPokemonGymPtr(int id)
{
  // loop through each list item using iterator
  for(list <PokemonGym*>::iterator it = gym_lst.begin(); it != gym_lst.end(); ++it) {
    if((*it) -> GetId() == id) {
      return *it;
    }
  }
  return 0; // return 0 if none of the gym objects have matching id 
}

BattleArena* Model::GetBattleArenaPtr(int id)
{
  // loop through each list item using iterator
  for(list <BattleArena*>::iterator it = arena_lst.begin(); it != arena_lst.end(); ++it) {
    if((*it) -> GetId() == id) {
      return *it;
    }
  }
  return 0; // return 0 if invalid input
}

Rival* Model::GetRivalPtr(int id)
{
  // loop through each list item using iterator
  for(list <Rival*>::iterator it = rival_lst.begin(); it != rival_lst.end(); ++it) {
    if((*it) -> GetId() == id) {
      return *it;
    }
  }
  return 0;
}

bool Model::Update()
{
  this -> time++; // step one tick

  // EXHAUSTED POKEMON LOOSE CONDITION
  int num_tired_pokemon = 0; // counter for tired pokemon
  for(list <Pokemon*>::iterator it = pokemon_lst.begin(); it != pokemon_lst.end(); ++it) {
    if((*it) -> IsExhausted()) {
      num_tired_pokemon++;
    }
  }
  if(num_tired_pokemon == this -> pokemon_lst.size()) {
    cout << "GAME OVER: You lose! All of your pokemon are tired!" << endl;
    exit(0); // leave program from function
  }
  
  // FAINTED  POKEMON LOOSE CONDITION
  int num_fainted_pokemon = 0; // counter for fainted pokemon
  for(list <Pokemon*>::iterator it = pokemon_lst.begin(); it != pokemon_lst.end(); ++it) {
    if(!(*it) -> IsAlive()) {
      num_fainted_pokemon++;
    }
  }
  if(num_fainted_pokemon == this -> pokemon_lst.size()) {
    cout << "GAME OVER: You lose! All of your pokemon have fainted!" << endl;
    exit(0); // leave program from function
  }

  // FAINTED RIVALS WIN CONDITION
  int num_arenas_beaten = 0; // counter for beaten arenas (internal rivals fainted)
  for(list <BattleArena*>::iterator it = arena_lst.begin(); it != arena_lst.end(); ++it) {
    if((*it) -> IsBeaten()) {
      num_arenas_beaten++;
    }
  }
  if(num_arenas_beaten == this -> arena_lst.size()) {
    cout << "GAME OVER: You Win! All Battle Arenas are beaten!" << endl;
    exit(0); // leave program from function
  }

  // BEATEN GYMS WIN CONDITION
  int num_gyms_beaten = 0; // counter for beaten gyms (internal units all trained)
  for(list <PokemonGym*>::iterator it = gym_lst.begin(); it != gym_lst.end(); ++it) {
    if((*it) -> IsBeaten()) {
      num_gyms_beaten++;
    }
  }
  if(num_gyms_beaten == this -> gym_lst.size()) {
    cout << "GAME OVER: You Win! All Pokemon Gyms are beaten!" << endl;
    exit(0); // leave program from function
  }
  
  // if function reaches this point then model must continue to update all objects
  int true_Updates = 0; // counts number of update calls that return true
  for(list <GameObject*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); ++it) {
    if((*it) -> Update()) {
      true_Updates++;
    }
  }

  
Commented block out for causing seg fault after removing dead objects and causing infinite loop in run command again
  // remove dead objects from active_ptrs
  for(list <GameObject*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); ++it) {
    if(!(*it) -> ShouldBeVisible()) {
      active_ptrs.erase(it);
      cout << "Dead Object Removed" << endl;
    }
  }
  
  if(true_Updates > 0) {
    // return true if any update returned true
    return true;
  } else {
    return false;
  }
}

void Model::Display(View& view)
{
  cout << "Time: " << this -> time << endl;
  view.Clear(); // clear view for printing

  for(list <GameObject*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); ++it) {
    view.Plot(*it); // plot each object in model instance if should be visible
  }

  view.Draw(); // draw each object to the display
}


void Model::ShowStatus()
{
  cout << "Time: " << this -> time << endl;
  for(list<GameObject*>::iterator it = object_lst.begin(); it != object_lst.end(); ++it) {
    (*it) -> ShowStatus();
  }
}

