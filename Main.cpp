#include "GameCommand.h"
#include "Input_Handling.h"

void printBanner(const char*);

int main ()
{

  // print intro message
  cout << endl;
  cout << "EC227 Introduction to Software Engineering" << endl;
  cout << "Fall 2019" << endl;
  cout << "Author: Jonathan Cook (jecook@bu.edu)" << endl;
  cout << "Programming Assignment 4" << endl;
  printBanner("Banner.txt");

 
  // model and view object for game
  Model m;
  View v;

  cout << endl;
  m.ShowStatus(); // initial status print
  m.Display(v); // first display print


  // input variables for game commands
  char command; // place holder for input;
  int pokemon_id = 0;
  int center_id = 0;
  int gym_id = 0;
  int arena_id;
  int rival_id;
  double x = 0.0;
  double y = 0.0;
  unsigned int stamina_amount;
  unsigned int unit_amount;
  int new_id = 0;
  char object_key;

  do {
    cout << "Enter a command character: ";
    try {
      cin >> command;
    cout << endl;
    switch(command) 
      {
      case 'm': {
	// move command
	cout << "Enter a Pokemon ID, and point coordinates to move to: ";
	cin >> pokemon_id >> x >> y;
	DoMoveCommand(m, pokemon_id, Point2D(x, y));
	break;
      }

      case 'g': {
	// move to gym
	cout << "Enter a Pokemon ID and Gym ID to move to: ";
	cin >> pokemon_id >> gym_id;
	DoMoveToGymCommand(m, pokemon_id, gym_id);
	break;
      }

      case 'c': {
	// move to center
	cout << "Enter a Pokemon ID and Center ID to move to: ";
	cin >> pokemon_id >> center_id;
	DoMoveToCenterCommand(m, pokemon_id, center_id);
	break;
      }

      case 's': {
	// stop pokemon
	cout << "Enter a Pokemon ID to stop: ";
	cin >> pokemon_id;
	DoStopCommand(m, pokemon_id);
	break;
      }

      case 'r' : {
	// recover in center
	cout << "Enter a Pokemon ID and a number of stamina points to recover: ";
	cin >> pokemon_id >> stamina_amount;
	DoRecoverInCenterCommand(m, pokemon_id, stamina_amount);
	break;
      }

      case 't': {
	// train in gym
	cout << "Enter a Pokemon ID and number of training units to complete: ";
	cin >> pokemon_id >> unit_amount;
	DoTrainInGymCommand(m, pokemon_id, unit_amount);
	break;
      }

      case 'v': {
	// go command to advance time by one tick
	DoGoCommand(m, v); // remember to populate go command
	break;
      }

      case 'x': {
	// run command to advance until an event OR 5 ticks occur
	DoRunCommand(m, v);
	  for(int i = 0; i < 5; i++) {
	    if(m.Update() || i == 3) {
	      break; // break when an update returns true or five 'ticks' pass
	    }
	  }
	  break;
      }      
      
      case 'q': {
            // quit command
            cout << "Terminating program" << endl << endl;
            return 0;
            break;
      }
       
      // PA4 cases
      case 'a': {
            // move to arena
            cout << "Enter a Pokemon ID and an Arena ID: ";
            cin >> pokemon_id >> arena_id;
            DoMoveToArenaCommand(m, pokemon_id, arena_id);
            break;
      }

      case 'b': {
            // battle with rival
            cout << "Enter and pokemon ID and a Rival ID: ";
            cin >> pokemon_id >> rival_id;
            DoBattleCommand(m, pokemon_id, rival_id);
            break;
      }

      case 'n': {
	// create new object
	cout << "Enter an object key, ID number, and x & y coordinates: ";
	cin >> object_key >> new_id >> x >> y;
	DoNewObjectCommand(m, object_key, new_id, Point2D(x, y));
	break;
      }

      }
    }
    catch (Invalid_Input& except) {
          cout << "Invalid input - " << except.msg_ptr << endl;
    }
    cout << endl;
    if(m.Update()) {
      // print status of all object when an event occurs
      m.ShowStatus();
    }
    m.Display(v); // print updated display
  } while(command != 'q');

  // exit program on command q
  cout << endl << "Terminating Program" << endl<< endl;
  return 0;
}

void printBanner(const char* fileName)
{
    // prints ascii file based on string file name input
    ifstream readFile;
    readFile.open(fileName);
    string line;
    while (getline(readFile, line)) {
        cout << line << endl;
    }
}
