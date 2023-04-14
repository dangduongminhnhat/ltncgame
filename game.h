#include "board.h"
#include<vector>
#include <cstdlib>
#include <ctime>
#include<conio.h>

enum direction {up, down};

class Player {
private:
    Point* p;
    int score;
    direction d;
public:
    Player(int, int);
    ~Player();
    void drawPlayer();
    void goUp();
    void goDown();
    void goRight();
    void goLeft();
    int getX();
    int getY();
    direction getDirection();
    void changeDirection();
};

class Game {
private:
    int remainTurn;
    Player* player;
    Board* board;
    std::vector<int> nonUse;
public:
    Game();
    ~Game();
    void makeRoads();
    void updateRoads();
    bool updatePlayer();
    void playGame();
};