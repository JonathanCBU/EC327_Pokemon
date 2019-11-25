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
    
}

void Pokemon::StartMovingToCenter(PokemonCenter* center)
{
    Point2D dest = center -> GetLocation(); // get protected location from pointer
    Point2D loc = this -> GetLocation();
    int dest_Id = center -> GetId(); // get protected id number from pointer
    if (loc.x == dest.x && loc.y == dest.y) {
      // make sure that pokemon state is set to in center
      this -> state = is_in_center;
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
    }
}

void Pokemon::StartMovingToGym(PokemonGym* gym)
{
    Point2D dest = gym -> GetLocation(); // get protected location from pointer
    Point2D loc = this -> GetLocation();
    int dest_Id = gym -> GetId(); // get protected id number from pointer
    if (loc.x == dest.x && loc.y == dest.y) {
        // x and y coordinates are the same as the destination
      this -> state = is_in_gym;
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
        return true;
    } else {
        return false;
    }
}

bool Pokemon::ShouldBeVisible()
{
    if (!this -> IsExhausted()) {
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
            if (this -> IsExhausted()) {
                cout << "This Pokemon is too exhausted to move" << endl;
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
            if (this -> IsExhausted()) {
                cout << "This Pokemon is too exhausted to move" << endl;
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
            if (this -> IsExhausted()) {
                cout << "This Pokemon is too exhausted to move" << endl;
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
    }
    cout << "\tStamina: " << this -> stamina << endl << 
        "\tPokemon Dollars: " << this -> pokemon_dollars << endl << 
        "\tExperience Points: " << this -> experience_points << endl;
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

// static non member functions
double GetRandomAmountOfPokemonDollars()
{
    srand(time(NULL));
    return (rand() % 21) / 10.00;
}

Pokemon::~Pokemon()
{
  cout << "Pokemon destructed" << endl;
}
