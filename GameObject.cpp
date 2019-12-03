#include "GameObject.h"

GameObject::GameObject(char in_code)
{
    this -> display_code = in_code;
    this -> id_num = 1;
    this -> state = 0;
    cout << "Game Object Constructed" << endl;
}

GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
{
    this -> location = in_loc;
    this -> id_num = in_id;
    this -> display_code = in_code;
    this -> state = 0;
    cout << "Game Object Constructed" << endl;
}

Point2D GameObject::GetLocation()
{
    return this -> location;
}

int GameObject::GetId()
{
    return this -> id_num;
}

char GameObject::GetState() 
{
    return this -> state;
}

void GameObject::ShowStatus()
{
    cout << this -> display_code << this -> id_num << " at " << this -> location;
}

bool GameObject::Update()
{
  return false; // virtual so any game object just calls its own Update()
}

bool GameObject::ShouldBeVisible()
{
  return true; // virtual
}

void GameObject::DrawSelf(char* ptr)
{
  if(this -> ShouldBeVisible()) {
    *ptr = this -> display_code; // this line is causing the segfault on my device
    *(ptr + 1) = '0' + this -> id_num;
  } else {
    *ptr = '.';
    *(ptr + 1) = ' ';
  }
}

char GameObject::GetCode()
{
  return this -> display_code;
}

GameObject::~GameObject()
{
  cout << "GameObject destructed" << endl;
}
