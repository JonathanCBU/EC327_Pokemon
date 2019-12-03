#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Point2D.h"
using namespace std;

class GameObject
{
    public:
    GameObject(char in_code);
    GameObject(Point2D in_loc, int in_id, char in_code);
    virtual ~GameObject();

    Point2D GetLocation();
    int GetId();
    char GetState();
    virtual void ShowStatus();
    virtual bool Update();
    virtual bool ShouldBeVisible();
    void DrawSelf(char* ptr);

    char GetCode();

    protected:
    Point2D location;
    int id_num;
    char display_code;
    char state;
};
#endif
