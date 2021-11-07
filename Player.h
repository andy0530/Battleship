//
// Created by Andy Lee on 2019-06-02.
//

#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

#include <string>

namespace BattleShip{
    class Player{
    public:
        explicit Player(int id); //id represents player 1 or player 2
        bool nameCheck(const std::string& checkName); //check name is valid
        std::string getName(); //returns name


    private:
        std::string name;
    };
}
#endif //BATTLESHIP_PLAYER_H
