//
// Created by Andy Lee on 2019-06-13.
//

#include "PlayMode3.h"
#include <iostream>

BattleShip::PlayMode3::PlayMode3(int rowNum, int colNum, int shipNum, const std::map<char, int> &ships) :
rowNum(rowNum),
colNum(colNum),
shipNum(shipNum),
ships(ships),
player1(3),
player2(4),
choice1(askAichoice()),
choice2(askAichoice()),
player1Board(rowNum, colNum, ships, player1.getName()),
player2Board(rowNum, colNum, ships, player2.getName()),
Ai1(choice1, player1Board),
Ai2(choice2, player2Board){
    play();
}

void BattleShip::PlayMode3::play() {
    int i = -1;
    do{ //take turn playing
        i++;
        askMove(i%2+1); //i%2+1 = 1, 2, 1, 2, ... which is id
        std::cout << std::endl;
    }while(!checkWin(i%2+1)); //until someone wins
}


int BattleShip::PlayMode3::askAichoice() { //asks which type of ai
    std::string selection;
    int choiceSelection;
    do{
        std::cout << "What AI do you want?" << std::endl;
        std::cout << "1. Cheating AI" << std::endl;
        std::cout << "2. Random AI" << std::endl;
        std::cout << "3. Hunt Destroy AI" << std::endl;
        std::cout << "Your choice: ";
        std::getline(std::cin, selection);
        choiceSelection = std::stoi(selection);
    }while(!(choiceSelection > 0 && choiceSelection < 4)); //does while input is either 1, 2, or 3
    return choiceSelection; //1-> cheating, 2-> random, 3-> hunt and destroy
}

void BattleShip::PlayMode3::askMove(int id) { //ask move
    if (id == 1){
        std::pair<int, int> selection;
        do{
            selection = Ai1.makeMove(player2Board); //get move depending on choice
        }while(!aiPlayCheck(selection.first, selection.second, 1)); //check move and sets as hit or miss
    }
    if (id == 2){
        std::pair<int, int> selection;
        do{
            selection = Ai2.makeMove(player1Board); //get move depending on choice
        }while(!aiPlayCheck(selection.first, selection.second, 2)); //check move and sets as hit or miss
    }
}

bool BattleShip::PlayMode3::aiPlayCheck(int row, int col, int id) {
    if (!(row >= 0 && row < rowNum)){ //check if ai input is inbound
        return false;
    }
    else if (!(col >= 0 && col < colNum)){
        return false;
    }
    if (id == 1){
        if (player2Board.isShip(row, col)){ //if it is a hit
            char shipName = player2Board.at(row, col); //get ship name
            player2Board.set(row, col, 'X'); //mark as hit
            display(1);
            std::cout << player1.getName() << " hit " << player2.getName() << "'s " << shipName << "!" << std::endl;
            if (player2Board.charCheck(shipName)){ //if ship sunk
                std::cout << player1.getName() << " destroyed " << player2.getName() <<"'s " << shipName << "!" << std::endl;
            }
            return true;
        }
        else if (player2Board.isBlank(row, col)){ //if it is a miss
            player2Board.set(row, col, 'O'); //mark as miss
            display(1);
            std::cout << "Missed." << std::endl;
            return true;
        }
    }
    else if (id == 2){
        if (player1Board.isShip(row, col)){ //if it is a hit
            char shipName = player1Board.at(row, col); //get ship name
            player1Board.set(row, col, 'X'); //mark as hit
            display(2);
            std::cout << player2.getName() << " hit " << player1.getName() << "'s " << shipName << "!" << std::endl;
            if (player1Board.charCheck(shipName)){ //if ship sunk
                std::cout << player2.getName() << " destroyed " << player1.getName() <<"'s " << shipName << "!" << std::endl;
            }
            return true;
        }
        else if (player1Board.at(row, col) == '*'){ //if it is a miss
            player1Board.set(row, col, 'O'); //mark as miss
            display(2);
            std::cout << "Missed." << std::endl;
            return true;
        }
    }
    return false;
}

void BattleShip::PlayMode3::display(int id) { //display firing and placement board
    if (id == 1){
        std::cout << player1.getName() << "'s Firing Board" << std::endl;
        player2Board.firingDisplay();
        std::cout << std::endl << std::endl;
        std::cout << player1.getName() << "'s Placement Board" << std::endl;
        player1Board.display();
    }
    if (id == 2){
        std::cout << player2.getName() << "'s Firing Board" << std::endl;
        player1Board.firingDisplay();
        std::cout << std::endl << std::endl;
        std::cout << player2.getName() << "'s Placement Board" << std::endl;
        player2Board.display();
    }
}

bool BattleShip::PlayMode3::checkWin(int id) { //return true if won
    for (int i = 0; i < rowNum; i++){
        for (int j = 0; j < colNum; j++){
            if (id == 1){
                if (player2Board.isShip(i, j)){
                    return false; //return false if there is a ship
                }
            }
            if (id == 2){
                if (player1Board.isShip(i, j)){
                    return false; //return false if there is a ship
                }
            }
        }
    } //only reaches here if there is no more ship
    if (id == 1){
        std::cout << player1.getName() << " won the game!" << std::endl;
    }
    if (id == 2){
        std::cout << player2.getName() << " won the game!" << std::endl;
    }
    return true;
}
