#include <iostream>
#include <string>
#include "Setup.h"

int main(int argc, char**argv) {
    std::string path = argv[1]; //path to file configuration
    if (argc == 3){ //true if seed is given
        int seed = std::stoi(argv[2]);
        BattleShip::Setup game(path, seed); //setup game for with seed
        game.playGame(); //play game
    }
    else{
        BattleShip::Setup game(path); //setup game for without seed
        game.playGame(); //play game
    }
    return 0;
}