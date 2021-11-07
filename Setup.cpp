//
// Created by Andy Lee on 2019-06-11.
//

#include "Setup.h"
#include "PlayMode1.h"
#include "PlayMode2.h"
#include "PlayMode3.h"
#include "AiBoard.h"
#include <fstream>
#include <iostream>

BattleShip::Setup::Setup(const std::string &path, int seed) : //initializer with seed
        Setup(path){ //calls initializer without seed
    AiBoard::seed_random_number_generator(seed); //assign seed to random number generator
}

BattleShip::Setup::Setup(const std::string &path) : //initializer without seed
        choice(askChoice()){ //ask type of game mode 1-> player vs player, 2-> player vs ai, 3-> ai vs ai
    std::string line;
    std::ifstream inputFile(path);
    if (inputFile.is_open()) { //read game configuration file
        getline(inputFile, line);
        rowNum = std::stoi(line);
        getline(inputFile, line);
        colNum = std::stoi(line);
        getline(inputFile, line);
        shipNum = std::stoi(line);
        for (int i = 0; i < shipNum; i++) {
            getline(inputFile, line);
            ships[line[0]] = line[2] - '0'; //create a map of ships with <ship name, ship len>
        }
        inputFile.close();
    }
}

void BattleShip::Setup::playGame() { //plays a game depending on game mode choice
    if (choice == 1){
        PlayMode1 game(rowNum, colNum, shipNum, ships);
    }
    else if (choice == 2){
        PlayMode2 game(rowNum, colNum, shipNum, ships);
    }
    else if (choice == 3){
        PlayMode3 game(rowNum, colNum, shipNum, ships);
    }
}

int BattleShip::Setup::askChoice() { //ask choice for game mode
    int choiceSelection;
    std::string selection;
    do{
        std::cout << "What type of game do you want to play?" << std::endl;
        std::cout << "1. Human vs Human" << std::endl << "2. Human vs AI" << std::endl << "3. AI vs AI" << std::endl;
        std::cout << "Your choice: ";
        std::getline(std::cin, selection);
        choiceSelection = std::stoi(selection);
    }while (!(choiceSelection > 0 && choiceSelection < 4)); //does while choice is either 1, 2, or 3
    return choiceSelection;
}