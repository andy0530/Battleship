//
// Created by Andy Lee on 2019-06-02.
//

#include "Player.h"
#include "Board.h"
#include <iostream>

BattleShip::Player::Player(int id) {
    //id 1 -> player 1
    //id 2 -> player 2
    //id 3 -> ai 1
    //id 4 -> ai 2
    if (id == 1 || id == 2){ //only asks name if its a player
        do{
            std::cout << "Player " << id << " please enter your name: ";
            std::getline(std::cin, name);
        }while(!nameCheck(name)); //asks while input is valid
    }
    else{ //if ai, name is already set
        if (id == 3){
            name = "AI 1";
        }
        if (id == 4){
            name = "AI 2";
        }
    }
}

bool BattleShip::Player::nameCheck(const std::string& checkName) {
    if (checkName.length() == 0){ //check if name exists
        return false;
    }
    for (char a: checkName){ //check if there is no whitespaces
        if (a == ' ' || a == '\n' || a == '\t'){
            return false;
        }
    }
    return true;
}

std::string BattleShip::Player::getName() { //returns name
    return name;
}


