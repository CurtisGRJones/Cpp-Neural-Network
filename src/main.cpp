#include <random>
#include <chrono>

#include "game/GameHandler.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    GameHandler game;

    while( game.isRunning() ) {
        game.tick();
    } 

    return 0;
}