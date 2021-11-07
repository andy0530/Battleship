//
// Created by Andy Lee on 2019-06-11.
//

#ifndef BATTLESHIP_SETUP_H
#define BATTLESHIP_SETUP_H

#include <string>
#include <map>

namespace BattleShip{
    class Setup{
    public:
        explicit Setup(const std::string &path, int seed); //initializer with seed
        explicit Setup(const std::string &path); //initializer without seed
        void playGame();
        int askChoice();

    private:
        int rowNum;
        int colNum;
        int shipNum;
        int choice;
        std::map<char, int> ships;
    };
}

#endif //BATTLESHIP_SETUP_H