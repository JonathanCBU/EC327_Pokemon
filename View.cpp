#include "View.h"

View::View()
{
  this -> size = 11;
  this -> scale = 2;
  this -> origin = Point2D();
}

void View::Clear()
{
  // loop through both layers of display
  for(int x = 0; x < this -> size; x++) {
    for(int y = 0; y < this -> size; y++) {
      this -> grid[x][y][0] = '.'; // set first layer
      this -> grid[x][y][1] = ' '; // set second layer
    }
  }
}

void View::Plot(GameObject* ptr)
{
  int x;
  int y; // x & y coordinates for plotting

  if(GetSubscripts(x, y, ptr -> GetLocation())) {
    // only proceed if object is in display
      if(this -> grid[x][y][0] != '.') {
	// there is an object already at location
	this -> grid[x][y][0] = '*';
	this -> grid[x][y][1] = ' ';
      } else {
	char* toShow;
	ptr -> DrawSelf(toShow); // get display instance
	this -> grid[x][y][0] = toShow[0];
	this -> grid[x][y][1] = toShow[1];
      }
   }
}

void View::Draw()
{
  for(int y = size-1; y >= 0; y--) {
    // loop from display size to 1 from top to bottom
    for(int x = -1; x < size; x++) {
      // loop through each item in the row
      if(x == -1) {
	// insert line counter at the far left
	if(y % 2 == 0) {
	  // even numbered line so print number marker
	  if(y*scale < 10) {
	    // single digit number so add whitespace after for formatting
	    cout << y*scale << " ";
	  } else {
	    // double digit number marker so no whitespace
	    cout << y*scale;
	  }
	} else {
	  // no line marker so add twio whitespaces for formatting
	  cout << "  ";
	}
      } else {
	// if x is not zero the we are somewhere else in the row
	cout << this -> grid[x][y][0] << this -> grid[x][y][1]; // print next two-piece element in grid
      }
    }
    // finished printing row loop
    cout << endl; // move to next row
  }

  // finished printing all but x markers
  cout << " "; // whitespace for formatting
  for(int x = -1; x < size; x++) {
    if(x % 2 == 0) {
      // even numbered column so print marker
      if(x*scale < 10) {
	// add whitespace after single digit markers
	cout << x*scale << " ";
      } else {
	// don't add whitespace after double digit marker
	cout << x*scale;
      }
    } else {
      // not a numbered column so print two whitespaces
      cout << "  ";
    }
  }
  cout << endl; // finished with x axis markers
}

bool View::GetSubscripts(int& out_x, int& out_y, Point2D location)
{
  Vector2D s = (location - this -> origin) / this -> scale; // variable with scaled distance from origin

  // check if object is within the display
  if(s.x >= this -> size * this -> scale || s.y >= this -> size * this -> scale) {
    cout << "An object is outside the display" << endl;
    return false;
  } else {
    // object is within bounds of display
    out_x = int(s.x);
    out_y = int(s.y); // truncate decimal point to int type
    return true; 
  }
}

