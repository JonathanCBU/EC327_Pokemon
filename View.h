#ifndef VIEW_H
#define VIEW_H
#include "Pokemon.h"
using namespace std;

const int view_maxsize = 20;

class View
{
 public:
  View();

  void Clear();
  void Plot(GameObject* ptr);
  void Draw();

 private:
  double size; // supposed to be declared as int, but was getting a strange error that changed it to 12781 when trying to populate the board
  double scale;
  Point2D origin;
  char grid[view_maxsize][view_maxsize][2];
  bool GetSubscripts(int& out_x, int& out_y, Point2D location);
};
#endif
