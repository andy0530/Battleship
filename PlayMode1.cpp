//
// Created by Andy Lee on 2019-06-12.
//

#include "PlayMode1.h"
#include <iostream>
#include <list>
#include <string>

BattleShip::PlayMode1::PlayMode1(int rowNum, int colNum, int shipNum, const std::map<char, int>& ships) :
rowNum(rowNum),
colNum(colNum),
shipNum(shipNum),
ships(ships),
player1(1),
player1Board(rowNum, colNum, ships, player1.getName()),
player2(2),
player2Board(rowNum, colNum, ships, player2.getName()){
    play();
}

void BattleShip::PlayMode1::play() {
    int i = -1;
    do{ //take turns playing
        i++;
        askMove(i%2+1); //i%2+1 = 1, 2, 1, 2, ... which is id
        std::cout << std::endl;
    }while(!checkWin(i%2+1)); //until someone wins

}

void BattleShip::PlayMode1::display(int id) { //display firing board and placement board
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

void BattleShip::PlayMode1::askMove(int id) { //asks user for where to fire
    std::string rowAndCol;
    if (id == 1){
        do{
            display(1);
            std::cout << player1.getName() << ", where would you like to fire?" <<std::endl;
            std::cout << "Enter your attack coordinate in the form row col: ";
            std::getline(std::cin, rowAndCol);
        }while(!checkMove(rowAndCol, id)); //does while input is valid
    }
    if (id == 2){
        do{
            display(2);
            std::cout << player2.getName() << ", where would you like to fire?" <<std::endl;
            std::cout << "Enter your attack coordinate in the form row col: ";
            std::getline(std::cin, rowAndCol);
        }while(!checkMove(rowAndCol, id)); //does while input is valid
    }
}

bool BattleShip::PlayMode1::checkMove(const std::string& input, int id) {
    std::list<std::string> rowAndCol;
    std::string word;
    for (auto frag:input){
        if (frag == ' '){
            rowAndCol.push_back(word);
            word = "";
        }
        else{
            word += frag;
        }
    }
    rowAndCol.push_back(word); //make a list of {row, col}
    if (rowAndCol.size() == 2){
        int row = std::stoi(rowAndCol.front());
        int col = std::stoi(rowAndCol.back());
        if (playCheck(row, col, id)){ //see if input is inbound and place if valid
            return true;
        }
    }
    return false;
}

bool BattleShip::PlayMode1::playCheck(int row, int col, int id) {
    if (!(row >= 0 && row < rowNum)){ //check if inbound
        return false;
    }
    else if (!(col >= 0 && col < colNum)){ //check if inbound
        return false;
    }
    if (id == 1){
        if (player2Board.isShip(row, col)){ //if it is a ship
            char shipName = player2Board.at(row, col); //get ship name
            player2Board.set(row, col, 'X'); //mark as hit
            display(1);
            std::cout << player1.getName() << " hit " << player2.getName() << "'s " << shipName << "!" << std::endl;
            if (player2Board.charCheck(shipName)){ //true if ship sunk
                std::cout << player1.getName() << " destroyed " << player2.getName() <<"'s " << shipName << "!" << std::endl;
            }
            return true;
        }
        else if (player2Board.isBlank(row, col)){ //if it is empty
            player2Board.set(row, col, 'O'); //mark as miss
            display(1);
            std::cout << "Missed." << std::endl;
            return true;
        }
    }
    if (id == 2){
        if (player1Board.isShip(row, col)){ //if it is a ship
            char shipName = player1Board.at(row, col); //get ship name
            player1Board.set(row, col, 'X'); //mark as hit
            display(2);
            std::cout << player2.getName() << " hit " << player1.getName() << "'s " << shipName << "!" << std::endl;
            if (player1Board.charCheck(shipName)){ //true if ship sunk
                std::cout << player2.getName() << " destroyed " << player1.getName() <<"'s " << shipName << "!" << std::endl;
            }
            return true;
        }
        else if (player1Board.isBlank(row, col)){ //if it is empty
            player1Board.set(row, col, 'O'); //mark as miss
            display(2);
            std::cout << "Missed." << std::endl;
            return true;
        }
    }
    return false; //return false if any other cases such as rehitting previous selection
}

bool BattleShip::PlayMode1::checkWin(int id) { //return true if game is won
    for (int i = 0; i < rowNum; i++){
        for (int j = 0; j < colNum; j++){
            if (id == 1){
                if (player2Board.isShip(i, j)){ //if there is a ship
                    return false;
                }
            }
            if (id == 2){
                if (player1Board.isShip(i, j)){ //if there is a ship
                    return false;
                }
            }
        }
    }
    //only comes here if all spots are empty
    if (id == 1){
        std::cout << player1.getName() << " won the game!" << std::endl;
    }
    if (id == 2){
        std::cout << player2.getName() << " won the game!" << std::endl;
    }
    return true;
}