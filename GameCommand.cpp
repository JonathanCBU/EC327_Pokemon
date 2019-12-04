#include "GameCommand.h"
#include "Input_Handling.h"
void DoMoveCommand(Model & model, int pokemon_id, Point2D p1)
{
  Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
  if(pokemon_ptr == 0) {
    cout << "Invalid Pokemon ID" << endl;
  } else {
    // pokemon id number is valid and input point is on display grid
    cout << "Moving Pokemon " << pokemon_id  << " to " << p1 << endl;
    pokemon_ptr -> StartMoving(p1);
  }
}

void DoMoveToCenterCommand(Model &model, int pokemon_id, int center_id)
{
  Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
  PokemonCenter* center_ptr = model.GetPokemonCenterPtr(center_id);
  if(pokemon_ptr != 0 && center_ptr != 0) {
    // center and pokemon id numbers are valid
    cout << "Moving Pokemon " << pokemon_id << " to Center " << center_id << endl;
    pokemon_ptr -> StartMovingToCenter(center_ptr);
  } else {
    cout << "Error: Please enter a valid command!" << endl;
  }
}

void DoMoveToGymCommand(Model &model, int pokemon_id, int gym_id)
{
  Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
  PokemonGym* gym_ptr = model.GetPokemonGymPtr(gym_id);
  if(pokemon_ptr != 0 && gym_ptr != 0) {
    // gym and pokemon id numbers are valid
    cout << "Moving Pokemon " << pokemon_id << " to Gym " << gym_id << endl;
    pokemon_ptr -> StartMovingToGym(gym_ptr);
  } else {
    cout << "Error: Please enter a valid command!" << endl;
  }
}  

void DoStopCommand(Model & model, int pokemon_id)
{
  Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);                                                                    
  if(pokemon_ptr != 0) {                                                                                   
    // pokemon id number is valid
    cout << "Stopping Pokemon " << pokemon_id << endl;
    pokemon_ptr -> Stop();                                                                          
  } else {                                                                                                                   
    cout << "Error: Please enter a valid command!" << endl;                                                                  
  }
}

void DoTrainInGymCommand(Model& model, int pokemon_id, unsigned int training_units)
{
  Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
  if(pokemon_ptr != 0) {
    // pokemon id number is valid
    cout << "Training Pokemon " << pokemon_id << endl;
    pokemon_ptr -> StartTraining(training_units);
  } else {
    cout << "Error: Please enter a valid command!" << endl;
  }
}

void DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int stamina_points)
{
  Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
  if(pokemon_ptr != 0) {
    // pokemon id number is valid
    cout << "Recovering Pokemon " << pokemon_id << "'s stamina" << endl;
    pokemon_ptr -> StartRecoveringStamina(stamina_points);
  } else {
    cout << "Error: Please enter a valid command!" << endl;
  }
}

void DoGoCommand(Model& model, View& view)
{
  cout << "Advancing one tick." << endl;
}

void DoRunCommand(Model& model, View& view)
{
  cout << "Advancing to next event." << endl;
}

// PA4 commands
void DoMoveToArenaCommand(Model & model, int pokemon_id, int arena_id)
{
  Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
  BattleArena* arena_ptr = model.GetBattleArenaPtr(arena_id);
  if(pokemon_ptr != 0 && arena_ptr != 0) {
    // both pokemon and arena are valid
    cout << "Moving Pokemon " << pokemon_id << " to Arena " << arena_id << endl;
    pokemon_ptr -> StartMovingToArena(arena_ptr);
  } else {
    cout << "Error: Please enter a valid command!" << endl;
  }
}

void DoBattleCommand(Model & model, int pokemon_id, int rival_id)
{
 Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
 Rival* rival_ptr = model.GetRivalPtr(rival_id);
 if(pokemon_ptr != 0 && rival_ptr != 0) {
   // both object IDs are valid
   cout << "Pokemon " << pokemon_id << " preparing to battle Rival " << rival_id << endl;
   pokemon_ptr -> ReadyBattle(rival_ptr);
 } else {
   cout << "Error: Please enter a valid command!" << endl;
 }
}

void DoNewObjectCommand(Model & model, char type, int id, Point2D p)
{
  // call model.NewCommand to create the object and add it to the proper list
  model.NewCommand(type, id, p);
}
