#include <string>
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


int get_int ()
{
  int i;
  if (!(cin >> i)) {  // do the input, then check: is stream good?
    throw Invalid_Input("Was expecting an integer"); // throw an exception
  }
  return i;
}

char get_char()
{
  char com;
  if (!(cin >> com)) {
    throw Invalid_Input("Was expecting a character");
  }
  return com;
}
