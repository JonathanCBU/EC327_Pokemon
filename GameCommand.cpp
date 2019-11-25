#include "GameCommand.h"

void DoMoveCommand(Model & model, int pokemon_id, Point2D p1)
{
  Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
  if(pokemon_ptr != 0 && p1.x <= 20 && p1.x >= 0 && p1.y <= 20 && p1.y >= 0) {
    // pokemon id number is valid and input point is on display grid
    cout << "Moving Pokemon " << pokemon_id  << " to " << p1 << endl;
    pokemon_ptr -> StartMoving(p1);
  } else {
    cout << "Error: Please enter a valid command!" << endl;
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
