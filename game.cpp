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
    if(d == up) this->p->create(24);
    else this->p->create(25);
}

void Player::erasePlayer() {
    this->p->erase();
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

void Player::printScore() {
    gotoXY(90, 3);
    printf("Score: %d", this->score);
}

void Player::increaseScore(int n) {
    this->score += n;
}

int Player::getScore() {
    return this->score;
}

// class Game

Game::Game() {
    this->player = new Player(15, 19);
    this->board = new Board();
    this->board->addRoad(11, 20, 200);
    this->remainTurn = 0;
    this->nonUse = std::vector<int>(14, 0);
    for(int i = 0; i < 14; i ++) this->nonUse[i] = i;
}

Game::~Game() {
    delete this->player;
    delete this->board;
    this->remainTurn = 0;
}

void Game::makeRoads() {
    int num = rand() % nonUse.size(), len = rand() % 40 + 40;
    this->remainTurn = len >> 1;
    this->board->addRoad(109, nonUse[num] + 6, len);
    this->board->drawRoadIndex(nonUse[num]);
    this->nonUse.erase(nonUse.begin() + num);
}

void Game::updateRoads() {
    if(this->remainTurn == 0) this->makeRoads();
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
    int turn = 0;
    system("cls");
    resetBoardGame();
    this->board->drawBoard();
    this->board->drawRoads();
    int timeSleep = 50;
    while(true) {
        turn ++;
        if(turn % 10 == 0) player->increaseScore(1);
        this->updateRoads();
        if(kbhit()) {
            char c = getch();
            if(c == 'p' || c == 'P') {
                this->updatePlayer();
                gotoXY(40, 23);
                system("Pause");
                this->player->erasePlayer();
                gotoXY(40, 23);
                printf("                               ");
            }
            if(c == 'm' || c == 'M') this->player->changeDirection();
            if(c == 'q' || c == 'Q') break;
        }
        bool check = this->updatePlayer();
        this->player->printScore();
        if(timeSleep > 20 && turn % 50 == 0) timeSleep --;
        Sleep(timeSleep);
        if(check == false) break;
        this->player->erasePlayer();
    }
}

void Game::startGame() {
    system("cls");
    this->board->drawBoard();
    gotoXY(15, 7);
    printf("Author's Name: Dang Duong Minh Nhat");
    gotoXY(15, 8);
    printf("Student's Id: 2110416");
    gotoXY(45, 10);
    printf("-----WELCOME TO MY GAME!!------");
    gotoXY(15, 12);
    printf("Instructions:");
    gotoXY(17, 13);
    printf("Press s or S to start game.");
    gotoXY(17, 14);
    printf("When you are in game, press p or P to pause game.");
    gotoXY(17, 15);
    printf("When you are in game, press m or M to change your direction (up or down).");
    gotoXY(17, 16);
    printf("Press q or Q to quit game.");
    gotoXY(0, 23);
}

void Game::runGame() {
    int highscore = 0;
    while(true) {
        bool endGame = false;
        this->startGame();
        while(true) {
            if(kbhit()) {
                char c = getch();
                if(c == 's' || c == 'S') {
                    this->playGame();
                    break;
                } else if(c == 'q' || c == 'Q') {
                    endGame = true;
                    break;
                }
            }
        }
        system("cls");
        if(endGame) break;
        highscore = (highscore > player->getScore()) ? highscore : player->getScore();
        this->board->drawBoard();
        gotoXY(15, 7);
        printf("Author's Name: Dang Duong Minh Nhat");
        gotoXY(15, 8);
        printf("Student's Id: 2110416");
        gotoXY(55, 10);
        printf("Highscore: %d", highscore);
        gotoXY(55, 11);
        printf("Your Score: %d", player->getScore());
        gotoXY(15, 13);
        printf("Press c or C to continue.");
        while(true) {
            char c = getch();
            if(c == 'c' || c == 'C') {
                this->resetGame();
                break;
            }
        }
    }
}

void Game::resetGame() {
    delete this->player;
    delete this->board;
    this->player = new Player(15, 19);
    this->board = new Board();
    this->board->addRoad(11, 20, 200);
    this->remainTurn = 0;
    this->nonUse = std::vector<int>(14, 0);
    for(int i = 0; i < 14; i ++) this->nonUse[i] = i;
}