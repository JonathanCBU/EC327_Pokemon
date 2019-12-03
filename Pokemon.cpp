#include "Pokemon.h"
// constructors
Pokemon::Pokemon(): GameObject('P')
{
    // defaults always set for pokemon
    this -> speed = 5;
    this -> is_in_gym = false;
    this -> is_in_center = false;
    this -> stamina = 20;
    this -> experience_points = 0;
    this -> pokemon_dollars = 0;
    this -> training_units_to_buy = 0;
    this -> stamina_points_to_buy = 0;
    this -> name = "Default name";
    this -> current_center = NULL;
    this -> current_gym = NULL;
    this -> state = STOPPED;

    cout << "Pokemon default constructed" << endl;

}

Pokemon::Pokemon(char in_code): GameObject(in_code) // call simple contructor for game object to initialize with a code
{
    this -> speed = 5;
    this -> is_in_gym = false;
    this -> is_in_center = false;
    this -> stamina = 20;
    this -> experience_points = 0;
    this -> pokemon_dollars = 0;
    this -> training_units_to_buy = 0;
    this -> stamina_points_to_buy = 0;
    this -> name = "Default name";
    this -> current_center = NULL;
    this -> current_gym = NULL;
    this -> state = STOPPED;

    cout << "Pokemon constructed" << endl;
}

Pokemon::Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc): GameObject(in_loc, in_id, in_code)
{
    this -> speed = in_speed;
    this -> is_in_gym = false;
    this -> is_in_center = false;
    this -> stamina = 20;
    this -> experience_points = 0;
    this -> pokemon_dollars = 0;
    this -> training_units_to_buy = 0;
    this -> stamina_points_to_buy = 0;
    this -> name = in_name;
    this -> current_center = NULL;
    this -> current_gym = NULL;
    this -> state = STOPPED;

    cout << "Pokemon constructed" << endl;
}

// PA4 new constructor
Pokemon::Pokemon(string in_name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int in_id, char in_code, Point2D in_loc): GameObject(in_loc, in_id, in_code)
{
    this -> speed = speed;
    this -> is_in_gym = false;
    this -> is_in_center = false;
    this -> stamina = 20;
    this -> experience_points = 0;
    this -> pokemon_dollars = 0;
    this -> training_units_to_buy = 0;
    this -> stamina_points_to_buy = 0;
    this -> name = in_name;
    this -> current_center = NULL;
    this -> current_gym = NULL;
    this -> state = STOPPED;

    // initiate PA4 private members
    this -> health = hp;
    this -> store_health = hp;
    this -> physical_damage = phys_dmg;
    this -> magical_damage = magic_dmg;
    this -> defense = def;
    this -> is_in_arena = false;
    this -> target = NULL;
    this -> current_arena = NULL;

    cout << "Pokemon constructed" << endl;

}

// public member functions
void Pokemon::StartMoving(Point2D dest)
{
    Pokemon::SetupDestination(dest); // call other member function
    this -> state = MOVING;
    cout << this -> name << " " << this -> display_code << 
            this -> id_num << " on my way to " << dest << endl;

    // set is_in_gym and is_in_center variables to false as soon as a pokemon begins to move
    if (this -> is_in_center == true) {
        this -> is_in_center = false;
        this -> current_center -> RemoveOnePokemon();
    }
    if (this -> is_in_gym == true) {
        this -> is_in_gym = false;
        this -> current_gym -> RemoveOnePokemon();
    }
    if (this -> is_in_arena == true) {
      this -> is_in_arena = false;
      this -> current_arena -> RemoveOnePokemon();
    }
    
}

void Pokemon::StartMovingToCenter(PokemonCenter* center)
{
    Point2D dest = center -> GetLocation(); // get protected location from pointer
    Point2D loc = this -> GetLocation();
    int dest_Id = center -> GetId(); // get protected id number from pointer
    if (loc.x == dest.x && loc.y == dest.y) {
      // make sure that pokemon state is set to in center
      this -> state = IN_CENTER;
      cout << this -> display_code << this -> id_num << 
                ": I am already at the Pokemon Center!" << endl;
    } else {
        this -> SetupDestination(dest);
        this -> state = MOVING_TO_CENTER;
        this -> current_center = center;
        cout << this -> display_code << this -> id_num << 
                ": on my way to Center " << dest_Id << endl;

        // set is_in_gym and is_in_center variables to false as soon as a pokemon begins to move
        if (this -> is_in_center == true) {
            this -> is_in_center = false;
            this -> current_center -> RemoveOnePokemon();
        }
        if (this -> is_in_gym == true) {
            this -> is_in_gym = false;
            this -> current_gym -> RemoveOnePokemon();
        }
	if (this -> is_in_arena == true) {
	  this -> is_in_arena = false;
	  this -> current_arena -> RemoveOnePokemon();
	}
    }
}

void Pokemon::StartMovingToGym(PokemonGym* gym)
{
    Point2D dest = gym -> GetLocation(); // get protected location from pointer
    Point2D loc = this -> GetLocation();
    int dest_Id = gym -> GetId(); // get protected id number from pointer
    if (loc.x == dest.x && loc.y == dest.y) {
        // x and y coordinates are the same as the destination
      this -> state = IN_GYM;
        cout << this -> display_code << this -> id_num << ": I am already at the Pokemon Gym!" << endl;
    } else {
        // not at destination so begin moving
        this -> SetupDestination(dest);
        this -> state = MOVING_TO_GYM;
        this -> current_gym = gym; // assign to grab information from when updating pokemon
        cout << this -> display_code << this -> id_num << 
                ": on my way to Gym " << dest_Id << endl;
        // set is_in_gym and is_in_center variables to false as soon as a pokemon begins to move
        if (this -> is_in_center == true) {
            this -> is_in_center = false;
            this -> current_center -> RemoveOnePokemon();
        }
        if (this -> is_in_gym == true) {
            this -> is_in_gym = false;
            this -> current_gym -> RemoveOnePokemon();
        }
	if (this -> is_in_arena == true) {
	  this -> is_in_arena = false;
	  this -> current_arena -> RemoveOnePokemon();
	}
    }
}

void Pokemon::StartTraining(unsigned int num_training_units)
{
    if (!this -> is_in_gym) {
        // pokemon is not in a gym so don't check any other parameters
        cout << this -> display_code << this -> id_num << ": I can only train in a Pokemon Gym!" << endl;
    } else {
        if (this -> current_gym -> IsBeaten()) {
            // gym is beaten
            cout << this -> display_code << this -> id_num << ": Cannot train! This Pokemon Gym is already beaten!" << endl;
        } else {
            // check all other parameters
            if (this -> IsExhausted()) {
                // stamina is zero
                cout << this -> display_code << this -> id_num << ": I am exhausted, so no more training for me..." << endl;
            } else if (!this -> current_gym -> IsAbleToTrain(num_training_units, this -> pokemon_dollars, this -> stamina)) {
                // this pokemon cannot train due to its budget and/or stamina
                cout << this -> display_code << this -> id_num << ": Not enough stamina and/or money for training" << endl;
            } else {
                // pokemon is in an unbeaten gym, and has the funds/stmaina to train the desired number of units
                this -> state = TRAINING_IN_GYM; // update state for update function
                this -> training_units_to_buy = min(this -> current_gym -> GetNumTrainingUnitsRemaining(), num_training_units); // set amount to buy using min of units left in gym or requested units
                cout << this -> display_code << this -> id_num << 
                        ": Started to train at Pokemon Gym " << this -> current_gym -> GetId() << 
                        " with " << this -> current_gym -> GetNumTrainingUnitsRemaining() << " training units" << endl;
            }
        }
    }
}

void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points)
{
    if (!this -> is_in_center) {
        // pokemon is not in a center at the moment
        cout << this -> display_code << this -> id_num << ": I can only recover stamina in a Pokemon Center!" << endl;
    } else if (!this -> current_center -> HasStaminaPoints()) {
        // Center has no more stamina points to give out
        cout << this -> display_code << this -> id_num << ": Cannot recover! No more stamina points in this Pokemon Center!" << endl;
    } else if (this -> current_center -> CanAffordStaminaPoints(num_stamina_points, this -> pokemon_dollars)) {
        // pokemon is in a center with points to give and can afford requested number of points
        this -> state = RECOVERING_STAMINA;
        this -> stamina_points_to_buy = min(this -> current_center -> GetNumStaminaPointsRemaining(), num_stamina_points); // set stamina to buy to min
        cout << this -> display_code << this -> id_num << 
                ": Started recovering " << this -> stamina_points_to_buy << 
                " stamina points(s) at Pokemon Center " << this -> current_center -> GetId() << endl;
    } else {
        // pokemon does not have enough money to purchase desired points
        cout << this -> display_code << this -> id_num << ": not enough money to recover stamina" << endl;
    }
}

void Pokemon::Stop()
{
    // unsure how to "Stop whatever it's doing"
    this -> state = STOPPED;
    cout << this -> display_code << this -> id_num << ": Stopping..." << endl;
}

bool Pokemon::IsExhausted()
{
    if (this -> stamina == 0) {
        this -> state = EXHAUSTED;
        return true;
    } else {
        return false;
    }
}

bool Pokemon::ShouldBeVisible()
{
  if (!this -> IsExhausted() && this -> IsAlive()) {
        return true;
    } else {
        return false;
    }
}

bool Pokemon::Update()
{
   // switch case based on current state of pokemon object
    switch (this -> state)
    {
        case STOPPED: {
            this -> ShowStatus();
            return false;
            break;
        }

        case MOVING: {
	  if (this -> IsExhausted() || !this -> IsAlive()) {
                cout << "This Pokemon is too exhausted to move or has fainted" << endl;
                this -> state = STOPPED; // change to stopped if the pokemon can no longer move
                this -> ShowStatus(); // call show status func with now stopped state
                return false;
                break;
            } else {
                this -> ShowStatus();
                return this -> UpdateLocation(); // returns true if pokemon arrives at destination after one more step. Otherwise returns false
                break;
            }
        }
        
        case MOVING_TO_CENTER: {
	  if (this -> IsExhausted() || !this -> IsAlive()) {
                cout << "This Pokemon is too exhausted to move or has fainted" << endl;
                this -> state = STOPPED; // change to stopped if the pokemon can no longer move
                this -> ShowStatus(); // call show status func with now stopped state
                return false;
                break;
            } else {
                if (this -> UpdateLocation()) {
                    // pokemon has arrived at destination center
                    this -> state = IN_CENTER;
                    this -> is_in_center = true;
                    this -> current_center -> AddOnePokemon(); // add a pokemon to center counter
		            this -> ShowStatus();
                    return true;
                } else {
                    // pokemon did not arrive at center yet
		            this -> ShowStatus();
                    return false;
                }
                break;
            }
        }

        case MOVING_TO_GYM: {
	  if (this -> IsExhausted() || !this -> IsAlive()) {
                cout << "This Pokemon is too exhausted to move or has fainted" << endl;
                this -> state = STOPPED; // change to stopped if the pokemon can no longer move
                this -> ShowStatus(); // call show status func with now stopped state
                return false;
                break;
            } else {
                if (this -> UpdateLocation()) {
                    // pokemon has arrived at destination gym
                    this -> state = IN_GYM;
                    this -> is_in_gym = true;
                    this -> current_gym -> AddOnePokemon(); // add a pokemon to the gym we just entered
		            this -> ShowStatus();
                    return true;
                } else {
                    // pokemon did not arrive at gym yet
		            this -> ShowStatus();
                    return false;
                }
                break;
            }
        }

        case IN_CENTER: {
            this -> ShowStatus();
            return false;
            break;
        }
        case IN_GYM: {
            this -> ShowStatus();
            return false;
            break;
        }

        case TRAINING_IN_GYM: {
            unsigned int num_trained = this -> current_gym -> TrainPokemon(training_units_to_buy);
            this -> stamina = this -> stamina - this -> current_gym -> GetStaminaCost(this -> training_units_to_buy); // reduce stamina of pokemon
            this -> pokemon_dollars = this -> pokemon_dollars - this -> current_gym -> GetDollarCost(this -> training_units_to_buy); // reduce dollars of pokemon
            this -> experience_points = this -> experience_points + num_trained; // add experience points based on amount trained in gym
            cout << "** " << this -> name << " completed " << this -> training_units_to_buy << " training unit(s)! **" << endl;
            cout << "** " << this -> name << " gained " << num_trained << " experience point(s)! **" << endl;
            this -> state = IN_GYM;
	        this -> ShowStatus();
            return true;
            break;
        }

        case RECOVERING_STAMINA: {
            unsigned int num_recovered = this -> current_center -> DistributeStamina(this -> stamina_points_to_buy);
            this -> stamina = this -> stamina + num_recovered; // take stamina from center for pokemon
            this -> pokemon_dollars = this -> pokemon_dollars - this -> current_center -> GetDollarCost(this -> stamina_points_to_buy); // reduce pokemon money
            cout << "** " << this -> name << " recovered " << num_recovered << " stamina point(s)! **" << endl;
            this -> state = IN_CENTER;
	        this -> ShowStatus();
            return true;
            break;
        }

        case EXHAUSTED: {
            this -> ShowStatus();
            return false;
        }

        // PA4 new cases
        case FAINTED: {
            this -> state = FAINTED;
            this -> ShowStatus();
            return false; // do nothing (not even print ShowStatus)
        }

        case MOVING_TO_ARENA: {
	  if (this -> IsExhausted() || !this -> IsAlive()) {
                cout << "This Pokemon is too exhausted to move or has fainted" << endl;
                this -> state = STOPPED; // change to stopped if the pokemon can no longer move
                this -> ShowStatus(); // call show status func with now stopped state
                return false;
                break;
            } else {
                if (this -> UpdateLocation()) {
                    // pokemon has arrived at destination arena
                    this -> state = IN_ARENA;
                    this -> is_in_arena = true;
                    this -> current_arena -> AddOnePokemon(); // add a pokemon to the gym we just entered
		            this -> ShowStatus();
                    return true;
                } else {
                    // pokemon did not arrive at gym yet
		            this -> ShowStatus();
                    return false;
                }
                break;
            }
        }

        case IN_ARENA: {
            this -> ShowStatus();
            return false;
            break;
        }

        case BATTLE: {
            this -> pokemon_dollars -= this -> current_arena -> GetDollarCost(); // subtract dollar cost for one battle
            this -> stamina = this -> stamina - this -> current_arena -> GetStaminaCost(); // subtract stamina cost for one battle

            if(!this -> StartBattle()) {
                // returns false if pokemon loses
                this -> state = FAINTED;
                this -> target -> IsAlive();
            } else {
                // pokemon won the battle
                this -> health = this -> store_health; // restore to max health after victory
                this -> state = IN_ARENA;
                this -> target -> IsAlive();
            }

            this -> ShowStatus();
            return true; // always return true for now to fit with my show status only on event occurence
            break;
        }

        default: {
            // default to stopped state to prevent possible NULL return error
            this -> state = STOPPED;
            return false;
            break;
        }        
    }
}

void Pokemon::ShowStatus()
{
    cout << this -> name << " status: ";
    GameObject::ShowStatus();

    // switch case based on current state for info printout
    switch (this -> state)
    {
        case STOPPED: {
            cout << " stopped" << endl;
            break;
        }
        
        case MOVING: {
            cout << " moving at a speed of " << this -> speed << " to destination " << 
                    this -> destination << " at each step of " << this -> delta << endl;
            break;
        }

        case MOVING_TO_CENTER: {
            cout << " heading to Pokemon Center " << this -> current_center -> GetId() << 
                    " at a speed of " << this -> speed << " at each step of " << this -> delta << endl;
            break;
        }

        case MOVING_TO_GYM: {
            cout << " heading to Pokemon Gym " << this -> current_gym -> GetId() << 
                    " at a speed of " << this -> speed << " at each step of " << this -> delta << endl;
            break;
        }

        case IN_CENTER: {
            cout << " inside Pokemon Center " << this -> current_center -> GetId() << endl;
            break;
        }

        case IN_GYM: {
            cout << " inside Pokemon Gym " << this -> current_gym -> GetId() << endl;
            break;
        }

        case TRAINING_IN_GYM: {
            cout << " training in Pokemon Gym " << this -> current_gym -> GetId() << endl;
            break;
        }

        case RECOVERING_STAMINA: {
            cout << " recovering stamina in Pokemon Center " << this -> current_center -> GetId() << endl;
            break;
        }

        case EXHAUSTED: {
            cout << " exhausted..." << endl;
            break;
        }

        // cases from PA4
        case MOVING_TO_ARENA: {
            cout << " heading to Battle Arena " << this -> current_arena -> GetId() << 
                    " at a speed of " << this -> speed << " at each step of " << this -> delta << endl;
            break;
        }

        case IN_ARENA: {
            cout << " inside Battle Arena " << this -> current_arena -> GetId() << endl;
            break;
        }

        case FAINTED: {
            cout << " fainted..." << endl;
            break;
        }

    }
    cout << "\tStamina: " << this -> stamina << endl << 
        "\tPokemon Dollars: " << this -> pokemon_dollars << endl << 
        "\tExperience Points: " << this -> experience_points << endl <<
        "\tHealth: " << this -> health << endl <<
        "\tPhysical Damage: " << this -> physical_damage << endl <<
        "\tMagical Damage: " << this -> magical_damage << endl <<
        "\tDefense: " << this -> defense << endl;
}

// protected member functions
bool Pokemon::UpdateLocation()
{
    this -> location = this -> location + this -> delta; // change location point with overloaded addition op
    this -> pokemon_dollars += GetRandomAmountOfPokemonDollars(); // increase money each step
    this -> stamina--; // subtract stamina with step

    if (fabs(this -> destination.x - this -> location.x) <= fabs(this -> delta.x) && fabs(this -> destination.y - this -> location.y) <= fabs(this -> delta.y)) {
        // The next step will land the pokemon at it's location
        this -> state = STOPPED; // stop from taking more steps
        this -> location = this -> destination; // set location to target building
        cout << this -> display_code << this -> id_num << ": I'm there!" << endl;
        return true;
    } else {
        // next step will not arrive at location
        cout << this -> display_code << this -> id_num << ": step..." << endl;
        return false;
    }
}       

void Pokemon::SetupDestination(Point2D dest)
{
    this -> destination = dest; // set destination member
    double dist = GetDistanceBetween(this -> destination, this -> location); // use non-member function
    this -> delta = (this -> destination - this -> location) * (this -> speed / dist); // set private member delta
}

// new PA4 public member functions
void Pokemon::StartMovingToArena(BattleArena* arena)
{
  Point2D dest = arena -> GetLocation(); // get protected location
  Point2D loc = this -> GetLocation();
  int dest_Id = arena -> GetId();
  if(loc.x == dest.x && loc.y == dest.y) {
    // x and y coordinates are the same as destination
    this -> state = IN_ARENA;
    cout << this -> display_code << this -> id_num << ": I am alreadt and the Battle Arena!" << endl;
  } else {
    // not at destination building
    this -> SetupDestination(dest);
    this -> state = MOVING_TO_ARENA;
    this -> current_arena = arena;

    cout << this -> display_code << this -> id_num << ": on my way to Arena " << dest_Id << endl;

    if (this -> is_in_center == true) {
      this -> is_in_center = false;
      this -> current_center -> RemoveOnePokemon();
    }
    if (this -> is_in_gym == true) {
      this -> is_in_gym = false;
      this -> current_gym -> RemoveOnePokemon();
    }
    if (this -> is_in_arena == true) {
      this -> is_in_arena = false;
      this -> current_arena -> RemoveOnePokemon();
    }
  }
}


bool Pokemon::IsAlive()
{
    if(this -> state == FAINTED) {
        // pokemon is fainted
        return false;
    } else {
        // pokemon not fainted
        return true;
    }
}

void Pokemon::TakeHit(double physical_damage, double magic_damage, double defense)
{
    int dmg_type = rand() & 1; // chooses 1 or 0 with equal probability
    double damage = 0.0; // damage to subtract from health
    if(dmg_type == 0) {
        // randomly selected magic damage
        damage = (100.0 - defense) / 100 * magic_damage;
        cout << this -> name << " was hit for " << damage <<
                " points of magic damage!" << endl;
    } else {
        damage = (100.0 - defense) / 100 * physical_damage;
        cout << this -> name << " was hit for " << damage <<
                " points of physical damage!" << endl;
    }

    this -> health -= damage; // subtract damage from health
    cout << "Health reduced to " << this -> health << endl;
    cout << "**********" << endl;
}

void Pokemon::ReadyBattle(Rival* in_target)
{
    if(!this -> is_in_arena) {
        cout << this -> display_code << this -> id_num << ": can only battle when in an arena!" << endl;
    } else if(!this -> current_arena -> IsAbleToFight(this -> pokemon_dollars, this -> stamina) || this -> state == FAINTED) {
        cout << this -> display_code << this -> id_num << ": can't afford to battle here!" << endl;
        this -> state = IN_ARENA;
    } else if(this -> current_arena -> IsBeaten() || !in_target -> IsAlive()) {
        cout << "Arena or Rival is already beaten!" << endl;
        this -> state = IN_ARENA;
    } else {
        this -> target = in_target;
        this -> state = BATTLE;
    }
}

bool Pokemon::StartBattle()
{
    // dummy variables to make my life have fewer arrows
    double rival_phys = this -> target -> get_phys_dmg();
    double rival_mag = this -> target -> get_magic_dmg();
    double rival_def = this -> target -> get_defense();

    double my_phys = this -> physical_damage;
    double my_mag = this -> magical_damage;
    double my_def = this -> defense;

    // loop until one of the two objects is beaten
    do {
        this -> TakeHit(rival_phys, rival_mag, my_def); // hitting pokemon (rival must hit first)
        if(this -> health <= 0) {
            // pokemon has fainted. return false
            cout << this -> target -> get_name() << " has won!" << endl;
            return false;
        } else {
            this -> target -> TakeHit(my_phys, my_mag, rival_def); // hitting rival
        }
    } while(this -> target -> get_health() > 0); // leave loop if the pokemon hits and reduces rival health to below zero
    this -> target -> get_arena() -> RemoveRival();
    // pokemon has one battle. return true
    cout << this -> name << " has won!" << endl;
    return true;
}

// my own member function for determining loss conditions more easily
bool Pokemon::IsBeaten() 
{
  if(this -> IsExhausted() || !this -> IsAlive()) {
    // return true if either loss condition is satisfied for this pokemon
    return true;
  } else {
    // pokemon is both alive and not exhausted
    return false;
  }
}
// static non member functions (from PA3)
double GetRandomAmountOfPokemonDollars()
{
    srand(time(NULL));
    return (rand() % 21) / 10.00;
}

char Pokemon::GetCode()
{
  return this -> display_code;
}

// destructor (doesn't do anything but print because model deletes all object pointers)
Pokemon::~Pokemon()
{
  cout << "Pokemon destructed" << endl;
}
