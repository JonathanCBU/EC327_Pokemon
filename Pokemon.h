#ifndef POKEMON_H
#define POKEMON_H
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Rival.h"
#include "BattleArena.h"
using namespace std;

enum PokemonStates {
    STOPPED = 0,
    MOVING = 1,
    EXHAUSTED = 2,
    IN_GYM = 3,
    IN_CENTER = 4,
    MOVING_TO_GYM = 5,
    MOVING_TO_CENTER = 6,
    TRAINING_IN_GYM = 7,
    RECOVERING_STAMINA = 8,

    // new states added in PA4
    IN_ARENA = 9,
    MOVING_TO_ARENA = 10,
    BATTLE = 11,
    FAINTED = 12,
};

class Pokemon: public GameObject
{
    public:
    Pokemon();
    Pokemon(char in_code);
    Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
    Pokemon(string in_name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int in_id, char in_code, Point2D in_loc); // PA4 added constructor
    virtual ~Pokemon();

    void StartMoving(Point2D dest);
    void StartMovingToCenter(PokemonCenter* center);
    void StartMovingToGym(PokemonGym* gym);
    void StartTraining(unsigned int num_training_units);
    void StartRecoveringStamina(unsigned int num_stamina_points);
    void Stop();
    bool IsExhausted();
    bool ShouldBeVisible();
    bool Update();
    void ShowStatus();

    // new public member functions from PA4
    bool IsAlive();
    void TakeHit(double physical_damage, double magical_damage, double defense);
    void ReadyBattle(Rival* in_target);
    bool StartBattle();
    void StartMovingToArena(BattleArena* arena);

    protected:
    bool UpdateLocation();
    void SetupDestination(Point2D dest);

    // new protected members from PA4
    double health;
    double store_health;
    double physical_damage;
    double magical_damage;
    double defense;
    Rival* target;
    bool is_in_arena;
    BattleArena* current_arena;

    private:
    double speed;
    bool is_in_gym;
    bool is_in_center;
    unsigned int stamina;
    unsigned int experience_points;
    double pokemon_dollars;
    unsigned int training_units_to_buy;
    unsigned int stamina_points_to_buy;
    string name;
    PokemonCenter* current_center;
    PokemonGym* current_gym;
    Point2D destination;
    Vector2D delta;
};
static double GetRandomAmountOfPokemonDollars();
#endif
