#include "game.h"

int main() {
    system("cls");
    Game* game = new Game();
    game->playGame();

    delete game;
    return 0;
}