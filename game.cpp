#include "game.h"
// #include "main.h"

// class Player

Player::Player(int x, int y) {
    this->d = down;
    this->score = 0;
    this->p = new Point(x, y);
}

Player::~Player() {
    delete this->p;
    this->score = 0;
}

void Player::drawPlayer() {
    this->p->create('O');
}

void Player::goUp() {
    this->p->changeY(-1);
}

void Player::goDown() {
    this->p->changeY(1);
}

void Player::goLeft() {
    this->p->changeX(-1);
}

void Player::goRight() {
    this->p->changeX(1);
}

int Player::getX() {
    return this->p->getX();
}

int Player::getY() {
    return this->p->getY();
}

direction Player::getDirection() {
    return this->d;
}

void Player::changeDirection() {
    int x = this->getX() - 11, y = this->getY() - 6;
    if(this->d == up && getBoard(x, y - 1) == true) this->d = down;
    else if(this->d == down && getBoard(x, y + 1) == true) this->d = up;
}

// class Game

Game::Game() {
    this->player = new Player(15, 19);
    this->board = new Board();
    this->board->addRoad(11, 20, 200);
    this->remainTurn = 0;
    nonUse = std::vector<int>(14, 0);
    for(int i = 0; i < 14; i ++) nonUse[i] = i;
}

Game::~Game() {
    delete player;
    delete board;
    remainTurn = 0;
}

void Game::makeRoads() {
    int num = rand() % nonUse.size(), len = rand() % 40 + 40;
    this->remainTurn = len >> 1;
    this->board->addRoad(109, nonUse[num] + 6, len);
    this->nonUse.erase(nonUse.begin() + num);
}

void Game::updateRoads() {
    if(this->remainTurn == 0) this->makeRoads();
    this->board->drawRoads();
    this->board->shilfLeftRoads();
    int num = this->board->deleteEmptyRoads();
    if(num != -1) nonUse.push_back(num);
    this->remainTurn --;
}

bool Game::updatePlayer() {
    int x = player->getX() - 11, y = player->getY() - 6;
    if(getBoard(x, y)) {
        if(x == 0) return false;
        x --;
        player->goLeft();
    } else if(x < 50 && getBoard(x + 1, y) == false) {
        x ++;
        player->goRight();
    }
    if(player->getDirection() == up) {
        if(getBoard(x, y - 1) == false) {
            if(y == 1) return false;
            player->goUp();
        }
    } else {
        if(getBoard(x, y + 1) == false) {
            if(y == 13) return false;
            player->goDown();
        }
    }
    player->drawPlayer();
    return true;
}

void Game::playGame() {
    srand(time(NULL)); 
    while(true) {
        resetBoardGame();
        system("cls");
        this->board->drawBoard();
        this->updateRoads();
        if(kbhit()) {
            char c = getch();
            if(c == 'p') break;
            if(c == 'm' || c == 'M') this->player->changeDirection();
        }
        bool check = this->updatePlayer();
        if(check == false) break;
    }
    printf("DOne1");
}