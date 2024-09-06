#include <iostream>
#include <random>
#include <chrono>

#include "game/GameHandler.h"
#include "game/ai/Ai.h"


// TODO add inputs for what NN to run
int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "Building Game" << std::endl;
    GameHandler game(false);
    std::cout << "Building AI" << std::endl;
    Ai ai = Ai(game.getFrame());

    while( game.isRunning() ) {
        ai.tick();
        game.tick();
    } 

    return 0;
}