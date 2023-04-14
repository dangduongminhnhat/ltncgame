#include "board.h"
// #include "main.h"

bool boardGame[100][15];

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


void gotoXY(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void resetBoardGame() {
    for(int i = 0; i < 100; i ++) 
        for(int j = 0; j < 15; j ++) 
            boardGame[i][j] = false;
}

bool getBoard(int x, int y) {
    return boardGame[x][y];
}

// class Point

Point::~Point() {
    this->x = this->y = 0;
}

void Point::changeX(int n) {
    this->x += n;
}

void Point::changeY(int n) {
    this->y += n;
}

void Point::draw() {
    gotoXY(this->x, this->y);
    boardGame[this->x - 11][this->y - 6] = true;
    printf("*");
}

void Point::create(char c) {
    gotoXY(this->x, this->y);
    boardGame[this->x - 11][this->y - 6] = true;
    printf("%c", int(c));
}

void Point::erase() {
    gotoXY(this->x, this->y);
    printf(" ");
}

int Point::getX() {
    return this->x;
}

int Point::getY() {
    return this->y;
}

// class Board

Board::Board() {
    this->boardRoads = new Road*[15];
    for(int i = 0; i < 15; i ++) this->boardRoads[i] = NULL;
}

void Board::drawBoard() {
    /**
     * Board: 
     * (11, 5) --> (110, 5) 
     * (11, 21) --> (110, 21)
     */
    gotoXY(11, 5);
    for(int i = 0; i < 100; i ++) printf("_");
    gotoXY(11, 21);
    for(int i = 0; i < 100; i ++) printf("_");
    for(int i = 6; i < 22; i ++) {
        gotoXY(10, i);
        printf("|");
    }
    for(int i = 6; i < 22; i ++) {
        gotoXY(111, i);
        printf("|");
    }
}

void Board::addRoad(int x, int y, int len) {
    Road* r = new Road(x, y, len);
    this->boardRoads[y - 6] = r;
}

void Board::drawRoads() {
    for(int i = 0; i < 15; i ++)
        if(this->boardRoads[i]) 
            this->boardRoads[i]->drawRoad();
}

void Board::shilfLeftRoads() {
    for(int i = 0; i < 15; i ++)
        if(this->boardRoads[i]) 
            this->boardRoads[i]->shilfLeft();
}

int Board::deleteEmptyRoads() {
    for(int i = 0; i < 15; i ++) {
        if(this->boardRoads[i] && this->boardRoads[i]->getLength() == 0) {
            delete boardRoads[i];
            boardRoads[i] = NULL;
            return i;
        }
    }
    return -1;
}

Board::~Board() {
    for(int i = 0; i < 15; i ++) {
        if(this->boardRoads[i]) {
            delete boardRoads[i];
            boardRoads[i] = NULL;
        }
    }
    delete[] boardRoads;
}

// class Road

Road::Road(int x, int y, int len) {
    this->head = new Point(x, y);
    this->length = len;
}

Road::~Road() {
    this->length = 0;
    delete head;
}

void Road::drawRoad() {
    head->draw();
    boardGame[this->head->getX() - 11][this->head->getY() - 6] = true;
    for(int i = 1; i < this->length; i ++) {
        if(this->head->getX() + i == 110) break;
        boardGame[this->head->getX() + i - 11][this->head->getY() - 6] = true;
        printf("-");
    }
}

int Road::getLength() {
    return this->length;
}

void Road::shilfLeft() {
    if(this->head->getX() > 11) head->changeX(-1);
    else this->length --;
}

int Road::getY() {
    return this->head->getY();
}