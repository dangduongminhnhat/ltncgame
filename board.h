#ifndef __BOARD_H__
#define __BOARD_H__

#include<iostream>
#include<Windows.h>

#define MAX_LENGTH_ROAD 80

void gotoXY(int, int); 
void resetBoardGame();
bool getBoard(int x, int y);
void setBoard(int x, int y, bool b);

class Point {
private:
    int x, y;
public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    ~Point();
    void changeX(int);
    void changeY(int);
    void draw();
    void create(char);
    void erase();
    int getX();
    int getY();
};

class Road {
private:
    int length;
    Point *head;
    Point* tail;
public:
    Road() : length(0), head(NULL), tail(NULL) {}
    Road(int, int, int);
    ~Road();
    void drawRoad();
    int getLength();
    void shilfLeft();
    int getY();
};

class Board {
private:
    Road** boardRoads;
public:
    Board();
    ~Board();
    void addRoad(int, int, int);
    void drawBoard();
    void drawRoads();
    void drawRoadIndex(int);
    void shilfLeftRoads();
    int deleteEmptyRoads();
};

#endif