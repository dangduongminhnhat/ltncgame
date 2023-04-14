#include "game.h"

int main() {
    system("cls");
    Game* game = new Game();
    game->runGame();
    delete game;
    return 0;
}