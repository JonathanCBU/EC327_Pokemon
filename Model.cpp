#include "Model.h"
// constructor
Model::Model()
{
    this -> time = 0;

    // object counts
    this -> num_objects = 8;
    this -> num_pokemon = 2;
    this -> num_centers = 2;
    this -> num_gyms = 2;
    this -> num_rivals = 2;
    this -> num_arenas = 1;

    // Create objects
    Pokemon* P_ptr1 = new Pokemon("Pikachu", 2, 23, 3, 6, 15, 1, 'P', Point2D(5, 1));
    Pokemon* P_ptr2 = new Pokemon("Bulbasaur", 1, 26, 4, 3.7, 15, 2, 'P', Point2D(10, 1));

    PokemonCenter* C_ptr1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    PokemonCenter* C_ptr2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));

    PokemonGym* G_ptr1 =  new PokemonGym(10, 1, 2.0, 3, 1, Point2D()); 
    PokemonGym* G_ptr2 = new PokemonGym(20, 5, 7.5, 8, 2, Point2D(5, 5));

    // PA4 new objects

    BattleArena* A_ptr = new BattleArena(3, 3, 4, 1, Point2D(15, 12));

    Rival* R_ptr1 = new Rival("Nate", 16, 3, 7.2, 15, 1, Point2D(15, 12), A_ptr);
    Rival* R_ptr2 = new Rival("Noah", 29, 6.4, 3.6, 15, 2, Point2D(15, 12), A_ptr);

    // store created objects
    this -> object_ptrs[0] = P_ptr1;
    this -> object_ptrs[1] = P_ptr2;
    this -> object_ptrs[2] = C_ptr1;
    this -> object_ptrs[3] = C_ptr2;
    this -> object_ptrs[4] = G_ptr1;
    this -> object_ptrs[5] = G_ptr2;
    this -> object_ptrs[6] = R_ptr1;
    this -> object_ptrs[7] = R_ptr2;
    this -> object_ptrs[8] = A_ptr;

    // add objects to object_lst by pushing to back
    this -> object_lst.push_back(P_ptr1);
    this -> object_lst.push_back(P_ptr2);
    this -> object_lst.push_back(C_ptr1);
    this -> object_lst.push_back(C_ptr2);
    this -> object_lst.push_back(G_ptr1);
    this -> object_lst.push_back(G_ptr2);
    this -> object_lst.push_back(R_ptr1);
    this -> object_lst.push_back(R_ptr2);
    this -> object_lst.push_back(A_ptr);




    this -> pokemon_ptrs[0] = P_ptr1;
    this -> pokemon_ptrs[1] = P_ptr2;

    this -> center_ptrs[0] = C_ptr1;
    this -> center_ptrs[1] = C_ptr2;

    this -> gym_ptrs[0] = G_ptr1;
    this -> gym_ptrs[1] = G_ptr2;

    this -> rival_ptrs[0] = R_ptr1;
    this -> rival_ptrs[1] = R_ptr2;

    this -> arena_ptrs[0] = A_ptr;

    this -> active_ptrs = this -> object_lst;

    cout << "Model Default Constructed" << endl;
}

// dectructor
Model::~Model()
{
  for(int i = 0; i < this -> num_objects; i++) {
    // delete each pointer in object_ptrs
    delete this -> object_ptrs[i];
  }
  cout << "Model destructed." << endl;
}

Pokemon* Model::GetPokemonPtr(int id)
{
  // loop through available pokemon objects
  for(int i = 0; i < this -> num_pokemon; i++) {
    if(this -> pokemon_ptrs[i] -> GetId() == id) {
      // this pointer references a pokemon with desird Id
      return this -> pokemon_ptrs[i];
    }
  }
  return 0; // return 0 if none of the pokemon objects have matching id (assumes we don't need to error check here)
}

PokemonCenter* Model::GetPokemonCenterPtr(int id)
{
  // loop through available center  objects
  for(int i = 0; i < this -> num_centers; i++) {
    if(this -> center_ptrs[i] -> GetId() == id) {
      // this pointer references a center with desird Id
      return this -> center_ptrs[i];
    }
  }
  return 0; // return 0 if none of the center objects have matching id
}

PokemonGym* Model::GetPokemonGymPtr(int id)
{
  // loop through available gym objects
  for(int i = 0; i < this -> num_gyms; i++) {
    if(this -> gym_ptrs[i] -> GetId() == id) {
      // this pointer references a gym with desird Id
      return this -> gym_ptrs[i];
    }
  }
  return 0; // return 0 if none of the gym objects have matching id 
}

BattleArena* Model::GetBattleArenaPtr(int id)
{
  // loop through all available arena objects
  for(int i = 0; i < this -> num_arenas; i++) {
    if(this -> arena_ptrs[i] -> GetId() == id) {
      // pointer references arena
      return this -> arena_ptrs[i];
    }
  }
  return 0; // return 0 if invalid input
}

Rival* Model::GetRivalPtr(int id)
{
  // follow exact same structure as all other get ptr commands
  for(int i = 0; i < this -> num_rivals; i++) {
    if(this -> rival_ptrs[i] -> GetId() == id) {
      return this -> rival_ptrs[i];
    }
  }
  return 0;
}

bool Model::Update()
{
  this -> time++; // step one tick

  int num_gyms_beat = 0; // counter for number of beaten gyms
  for(int i = 0; i < this -> num_gyms; i++) {
    // loop through gym objects and check if they are beaten
    if(this -> gym_ptrs[i] -> IsBeaten()) {
      num_gyms_beat++;
    }
  }

  if(num_gyms_beat == this -> num_gyms) {
    // all gyms are beaten. No need to continue
    cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
    exit(0); // leave program from function
  }

  int num_tired_pokemon = 0; // counter for tired pokemon
  for(int i = 0; i < this -> num_pokemon; i++) {
    // loop through pokemon objects and check if they are excausted
    if(this -> pokemon_ptrs[i] -> IsExhausted()) {
      num_tired_pokemon++;
    }
  }

  if(num_tired_pokemon == this -> num_pokemon) {
    // all pokemon are tired. No need to continue
    cout << "GAME OVER: You lose! All of your pokemon are tired!" << endl;
    exit(0); // leave program from function
  }
  
  // if function reaches this point then model must continue to update all objects
  int true_Updates = 0; // counts number of update calls that return true

  for(int i = 0; i < this -> num_objects; i++) {
    if(this -> object_ptrs[i] -> Update()) {
      // calls update function for each object, but only runs this next block if Update returns true
      true_Updates++;
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

  for(int i = 0; i < this -> num_objects; i++) {
    view.Plot(this -> object_ptrs[i]); // plot each object in model instance if should be visible
  }

  view.Draw(); // draw each object to the display
}


void Model::ShowStatus()
{
  cout << "Time: " << this -> time << endl;
  for(int i = 0; i < this -> num_objects; i++) {
     this -> object_ptrs[i] -> ShowStatus(); // run ShowStatus() for every game object
  }
}

