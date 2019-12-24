# EC327_Pokemon
Pokemon Game for Introduction to Software Engineering Fall 2019

The purpose of this assignment was to teach students how to write and implement C++ classes, exception handling, and standard templates across a multitude of files.

The project is a Pokemon-themed game with various win and lose conditions.

Build instructions:
1. Clone this Repository
2. Access this repository on the command line
3. Run $ make -f MakeFile
4. Run $ ./PA3_Game
5. Have fun and sorry for any segfaults!

***********
Valid commands are as follows:

m ID1 X Y
 - starts moving Pokemon with ID1 to position X, Y

g ID1 ID2
 - starts moving Pokemon with ID1 to gym with ID2

c ID1 ID2
 - starts moving Pokemon with ID1 to center with ID2

s ID1
 - cancels and current action being performed by Pokemon with ID1

r ID1 x
 - instructs Pokemon with ID1 to recover x amount of stamina points

t ID1 x
 - instructs Pokemon with ID1 to train x amount of units

v
 - advance game time by one "tick"

x
 - advance game time until an event occurs or 5 "ticks" (whichever comes first)

q
 - quits game and triggers destructors

a ID1 ID2
 - starts moving Pokemon with ID1 to BattleArena with ID2

b ID1 ID2
 - instructs Pokemon with ID1 to battle the Rival with ID2

n ID1 Key X Y
 - creates new class instance with ID1 and position X, Y. Object type determined by Key
***********

