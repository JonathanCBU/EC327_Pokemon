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

    // add objects to object_ptrs by pushing to back
    this -> object_ptrs.push_back(P_ptr1);
    this -> object_ptrs.push_back(P_ptr2);
    this -> object_ptrs.push_back(C_ptr1);
    this -> object_ptrs.push_back(C_ptr2);
    this -> object_ptrs.push_back(G_ptr1);
    this -> object_ptrs.push_back(G_ptr2);
    this -> object_ptrs.push_back(R_ptr1);
    this -> object_ptrs.push_back(R_ptr2);
    this -> object_ptrs.push_back(A_ptr1);

    this -> pokemon_ptrs.push_back(P_ptr1);
    this -> pokemon_ptrs.push_back(P_ptr2);

    this -> center_ptrs.push_back(C_ptr1);
    this -> center_ptrs.push_back(C_ptr2);

    this -> gym_ptrs.push_back(G_ptr1);
    this -> gym_ptrs.push_back(G_ptr2);

    this -> rival_ptrs.push_back(R_ptr1);
    this -> rival_ptrs.push_back(R_ptr2);

    this -> arena_ptrs.push_back(A_ptr1);

    this -> active_ptrs.push_back(P_ptr1);
    this -> active_ptrs.push_back(P_ptr2);
    this -> active_ptrs.push_back(C_ptr1);
    this -> active_ptrs.push_back(C_ptr2);
    this -> active_ptrs.push_back(G_ptr1);
    this -> active_ptrs.push_back(G_ptr2);
    this -> active_ptrs.push_back(R_ptr1);
    this -> active_ptrs.push_back(R_ptr2);
    this -> active_ptrs.push_back(A_ptr1);

    cout << "Model Default Constructed" << endl;
}

// dectructor
Model::~Model()
{

  for(list <GameObject*>::iterator it = object_ptrs.begin(); it != object_ptrs.end(); it++) {
    delete *it;
  }
  cout << "Model destructed." << endl;
}

Pokemon* Model::GetPokemonPtr(int id)
{
  // loop through each list item using iterator
  for(list <Pokemon*>::iterator it = pokemon_ptrs.begin(); it != pokemon_ptrs.end(); it++) {
    if((*it) -> GetId() == id) {
      return *it;
    }
  }
  return 0; // return 0 if none of the pokemon objects have matching id (assumes we don't need to error check here)
}

PokemonCenter* Model::GetPokemonCenterPtr(int id)
{
  // loop through each list item using iterator
  for(list <PokemonCenter*>::iterator it = center_ptrs.begin(); it != center_ptrs.end(); it++) {
    if((*it) -> GetId() == id) {
      return *it;
    }
  }
  return 0; // return 0 if none of the center objects have matching id
}

PokemonGym* Model::GetPokemonGymPtr(int id)
{
  // loop through each list item using iterator
  for(list <PokemonGym*>::iterator it = gym_ptrs.begin(); it != gym_ptrs.end(); it++) {
    if((*it) -> GetId() == id) {
      return *it;
    }
  }
  return 0; // return 0 if none of the gym objects have matching id 
}

BattleArena* Model::GetBattleArenaPtr(int id)
{
  // loop through each list item using iterator
  for(list <BattleArena*>::iterator it = arena_ptrs.begin(); it != arena_ptrs.end(); it++) {
    if((*it) -> GetId() == id) {
      return *it;
    }
  }
  return 0; // return 0 if invalid input
}

Rival* Model::GetRivalPtr(int id)
{
  // loop through each list item using iterator
  for(list <Rival*>::iterator it = rival_ptrs.begin(); it != rival_ptrs.end(); it++) {
    if((*it) -> GetId() == id) {
      return *it;
    }
  }
  return 0;
}

bool Model::Update()
{  
  this -> time++; // step one tick
  
  // BEATEN POKEMON LOOSE CONDITION (FAINTED OR EXHAUSTED)
  int num_beaten_pokemon = 0;
  for(list <Pokemon*>::iterator it = pokemon_ptrs.begin(); it != pokemon_ptrs.end(); it++) {
    if((*it) -> IsBeaten()) {
      num_beaten_pokemon++;
    }
  }
  if(num_beaten_pokemon == this -> pokemon_ptrs.size()) {
    cout << "GAME OVER: You Lose! All pokemon are exhausted or fainted!" << endl;
    exit(0);
  }

  // FAINTED RIVALS WIN CONDITION
  int num_arenas_beaten = 0; // counter for beaten arenas (internal rivals fainted)
  for(list <BattleArena*>::iterator it = arena_ptrs.begin(); it != arena_ptrs.end(); it++) {
    if((*it) -> IsBeaten()) {
      num_arenas_beaten++;
    }
  }
  if(num_arenas_beaten == this -> arena_ptrs.size()) {
    cout << "GAME OVER: You Win! All Battle Arenas are beaten!" << endl;
    exit(0); // leave program from function
  }

  // BEATEN GYMS WIN CONDITION
  int num_gyms_beaten = 0; // counter for beaten gyms (internal units all trained)
  for(list <PokemonGym*>::iterator it = gym_ptrs.begin(); it != gym_ptrs.end(); it++) {
    if((*it) -> IsBeaten()) {
      num_gyms_beaten++;
    }
  }
  if(num_gyms_beaten == this -> gym_ptrs.size()) {
    cout << "GAME OVER: You Win! All Pokemon Gyms are beaten!" << endl;
    exit(0); // leave program from function
  }
  
  // if function reaches this point then model must continue to update all objects
  int true_Updates = 0; // counts number of update calls that return true
  for(list <GameObject*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++) {
    if((*it) -> Update()) {
      true_Updates++;
    }
  }
    
  // remove dead objects from active_ptrs
  vector <GameObject*> toRemove;
  for(list <GameObject*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++) {
    if(!(*it) -> ShouldBeVisible()) {
      toRemove.push_back(*it);
    }
  }
  
  // loop through vector to remove marked objects
  for(int i = 0; i < toRemove.size(); i++) {
    active_ptrs.remove(toRemove[i]);
    cout << "Dead object removed" << endl;
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

  for(list <GameObject*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++) {
    view.Plot(*it); // plot each object in model instance if should be visible
  }

  view.Draw(); // draw each object to the display
}

void Model::ShowStatus()
{
  cout << "Time: " << this -> time << endl;
  for(list<GameObject*>::iterator it = object_ptrs.begin(); it != object_ptrs.end(); it++) {
    (*it) -> ShowStatus();
  }
}

void Model::NewCommand(char type, int id, Point2D p)
{
  switch(type) 
    {
    case 'g': {
      // check ID input before moving on
      PokemonGym* check_ptr = this -> GetPokemonGymPtr(id);
      if(check_ptr == 0) {
	// there is not a gym object with input id yet
	PokemonGym* newGym = new PokemonGym(10, 2, 2, 3, id, p); // default inputs - unclear if I should ask for each value
	this -> gym_ptrs.push_back(newGym);
	this -> active_ptrs.push_back(newGym);
	this -> object_ptrs.push_back(newGym);
      } else {
	cout << "Not a valid ID number" << endl;
      }
      break;
    }

    case 'c': {
      // check ID input before moving on
      PokemonCenter* check_ptr = this -> GetPokemonCenterPtr(id);
      if(check_ptr == 0) {
	// there is not a center object with input id yet
	PokemonCenter* newCenter = new PokemonCenter(id, 2, 20, p); // default inputs - unclear if I should ask for each value
	this -> center_ptrs.push_back(newCenter);
	this -> active_ptrs.push_back(newCenter);
	this -> object_ptrs.push_back(newCenter);
      } else {
	cout << "Not a valid ID number" << endl;
      }
      break;
    }

    case 'p': {
      // check ID input before moving on
      Pokemon* check_ptr = this -> GetPokemonPtr(id);
      if(check_ptr == 0) {
	// there is not a pokemon object with input id yet
	Pokemon* newPokemon = new Pokemon("Constructed Pokemon", 2, 20, 5, 5, 15, id, 'P', p); // default inputs - unclear if I should ask for each value
	this -> pokemon_ptrs.push_back(newPokemon);
	this -> active_ptrs.push_back(newPokemon);
	this -> object_ptrs.push_back(newPokemon);
      } else {
	cout << "Not a valid ID number" << endl;
      }
      break;
    }

    case 'r': {
      // check ID input before moving on
      Rival* check_ptr = this -> GetRivalPtr(id);
      BattleArena* default_arena = this -> arena_ptrs.front(); // get front arena in arena_ptrs list to place rival in 
      if(check_ptr == 0) {
	// there is not a rival object with input id yet
	Rival* newRival = new Rival("Constructed Rival", 20, 5, 5, 15, id, default_arena -> GetLocation(), default_arena); // default inputs - unclear if I should ask for each value
	this -> rival_ptrs.push_back(newRival);
	this -> active_ptrs.push_back(newRival);
	this -> object_ptrs.push_back(newRival); 
	default_arena -> AddRival();
      } else {
	cout << "Not a valid ID number" << endl;
      }
    }
      break;
    }
}
