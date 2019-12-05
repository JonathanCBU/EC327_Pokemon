#ifndef INVALID_INPUT_H
#define INVALID_INPUT_H
#include "Model.h"
using namespace std;

class Invalid_Input
{
public :
	Invalid_Input(string in_ptr) : msg_ptr (in_ptr) { }
	const string msg_ptr;
private :
Invalid_Input ();
    // no default construction
};

// verify that input is integer
int get_int()
{
  int i;
  if(!(cin >> i)) {
    cin.ignore(100, '\n');
    cin.clear();
    throw Invalid_Input("Was expecting an integer");
  } 
  return i;
}

// verify input as valid command for game
char get_command()
{
  char com;
  cin >> com;
  string valid = "mgcsrtvxqabn"; // string container of valid input commands
  for(int i = 0; i < valid.size(); i++) {
    if(com == valid[i]) {
      return com; // return input command if found to be valid
    }
  }
    throw Invalid_Input("Not a valid command character");
}

// verify that input is double
double get_dub()
{
  double i;
  if(!(cin >> i)) {
    cin.ignore(100, '\n');
    cin.clear();
    throw Invalid_Input("Was expecting a number");
  } 
  return i;
}

// verify pointer input (for GetPtr function)
void check_ptr_id(Model& m, char type, int id)
{
  switch(type)
    {
    case 'p': {
      // checking pokemon id number
      if(!m.GetPokemonPtr(id)) {
	// return zero. ID not found
	throw Invalid_Input("Invalid Pokemon ID");
      }
      break;
    }

    case 'c':
      {
	// checking pokemon center id number
	if(!m.GetPokemonCenterPtr(id)) {
	  // return zero. ID not found
	  throw Invalid_Input("Invalid Center ID");
	}
	break;
      }

    case 'g':
      {
	// checking pokemon gym id number
	if(!m.GetPokemonGymPtr(id)) {
	  // return zero. ID not found
	  throw Invalid_Input("Invalid Gym ID");
	}
	break;
      }

    case 'r':
      {
	// checking rival id number
	if(!m.GetRivalPtr(id)) {
	  // return zero. ID not found
	  throw Invalid_Input("Invalid Rival ID");
	}
	break;
      }

    case 'a':
      {
	// checking battle arena id number
	if(!m.GetBattleArenaPtr(id)) {
	  // return zero. ID not found
	  throw Invalid_Input("Invalid Battle Arena ID");
	}
	break;
      }
    }
}

unsigned int get_uint()
{
  unsigned int ammount;
  if(!(cin >> ammount)) {
    cin.ignore(100, '\n');
    cin.clear();
    throw Invalid_Input("Was expecting a number");
  } 
  return ammount;
}
  
char get_key()
{
  char key;
  cin >> key;
  string valid = "pgcr"; // string container of valid input commands
  for(int i = 0; i < valid.size(); i++) {
    if(key == valid[i]) {
      return key; // return input command if found to be valid
    }
  }
    throw Invalid_Input("Not a valid creaction key");
}

void check_new_id(Model& m, char type, int id)
{
  switch(type)
    {
    case 'p': {
      // checking pokemon id number
      if(m.GetPokemonPtr(id)) {
	// return zero. ID not found
	throw Invalid_Input("Pokemon ID already in use");
      }
      break;
    }

    case 'c':
      {
	// checking pokemon center id number
	if(m.GetPokemonCenterPtr(id)) {
	  // return non-zero. ID found
	  throw Invalid_Input("Center ID already in use");
	}
	break;
      }

    case 'g':
      {
	// checking pokemon gym id number
	if(m.GetPokemonGymPtr(id)) {
	  // return non-zero. ID found
	  throw Invalid_Input("Gym ID already in use");
	}
	break;
      }

    case 'r':
      {
	// checking rival id number
	if(m.GetRivalPtr(id)) {
	  // return non-zero. ID found
	  throw Invalid_Input("Rival ID already in use");
	}
	break;
      }
    }
}

void check_point(Point2D p)
{
  if(p.x > 20 || p.x < 0 || p.y > 20 || p.y < 0) {
    throw Invalid_Input("Point coordinates outside display area");
  }
}

#endif
