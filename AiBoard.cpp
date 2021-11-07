//
// Created by Andy Lee on 2019-06-12.
//

#include "AiBoard.h"
#include "Utility.h"
#include <ctime>
#include <iostream>

BattleShip::AiBoard::AiBoard(int rowNum, int colNum, const std::map<char, int>& ships, const std::string& name) :
boardState(rowNum, std::string(colNum, '*')),
rowNum(rowNum),
colNum(colNum),
ships(ships),
name(name) {
    std::vector<char> orientation_choice{'h', 'v'};
    int rowStart;
    int colStart;
    int rowEnd;
    int colEnd;
    for (auto const &x : ships) { //for all ships randomly place ships
        do {
            char orientation = *chooseRandom(orientation_choice, randomNumberGenerator); //random orientation choice
            if (orientation == 'h') {
                rowStart = getRandInt(0, rowNum - 1, randomNumberGenerator);
                colStart = getRandInt(0, colNum - x.second, randomNumberGenerator);
                rowEnd = rowStart;
                colEnd = colStart + x.second - 1;
            } else {
                rowStart = getRandInt(0, rowNum - x.second, randomNumberGenerator);
                colStart = getRandInt(0, colNum - 1, randomNumberGenerator);
                rowEnd = rowStart + x.second - 1;
                colEnd = colStart;
            }
        } while (!placeCheck(rowStart, colStart, rowEnd, colEnd)); //check if the ship is in bounds
        placeShip(x.first, rowStart, colStart, rowEnd, colEnd); //place the ship
        std::cout << name << "'s Board" << std::endl; //display the board
        display();
        std::cout << std::endl;
    }
}

std::mt19937 BattleShip::AiBoard::randomNumberGenerator((time(nullptr))); //random number generator for no seed

void BattleShip::AiBoard::seed_random_number_generator(int seed) { //random number generator for seed
    BattleShip::AiBoard::randomNumberGenerator.seed(seed);

}

bool BattleShip::AiBoard::placeCheck(int rowStart, int colStart, int rowEnd, int colEnd) { //check if the ship is in bound
    for (int i = rowStart; i < rowEnd+1; i++){
        for (int j = colStart; j < colEnd+1; j++){
            if (!isBlank(i,j)){
                return false;
            }
        }
    }
    return true;
}

bool BattleShip::AiBoard::isBlank(int row, int col) const { //return true if place is blank
    return boardState.at(row).at(col) == '*';
}

void BattleShip::AiBoard::display() const { //display player board
    std::cout << "  ";
    for (int i = 0; i < colNum; ++i) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    int rowIndex = 0;
    for (const auto& row : boardState) {
        std::cout << rowIndex << ' ';
        for(const auto& elem : row){
            std::cout << elem << ' ';
        }
        rowIndex++;
        std::cout << std::endl;
    }
}

void BattleShip::AiBoard::placeShip(char marker, int rowStart, int colStart, int rowEnd, int colEnd) { //places ship
    for (int i = rowStart; i < rowEnd + 1; i++) {
        for (int j = colStart; j < colEnd + 1; j++) {
            set(i, j, marker);
        }
    }
}

void BattleShip::AiBoard::set(int row, int col, char marker) { //set location to a certain marker
    boardState.at(row).at(col) = marker;
}

void BattleShip::AiBoard::firingDisplay() const { //display board with only '*', 'O', or 'X'
    std::cout << "  ";
    for (int i = 0; i < colNum; ++i) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    int rowIndex = 0;
    for (const auto& row : boardState) {
        std::cout << rowIndex << ' ';
        for(const auto& elem : row){
            if (elem != '*' && elem != 'O' && elem != 'X'){
                std::cout << '*' << ' ';
            }
            else{
                std::cout << elem << ' ';
            }
        }
        rowIndex++;
        std::cout << std::endl;
    }
}

char BattleShip::AiBoard::at(int row, int col) const { //return char at point
    return boardState.at(row).at(col);
}

bool BattleShip::AiBoard::charCheck(char marker) { //see if there is anymore char in board (to check if ship sunk)
    for (int i = 0; i < rowNum; i++){
        for (int j = 0; j < colNum; j++){
            if (at(i,j)== marker){
                return false;
            }
        }
    }
    return true;
}

int BattleShip::AiBoard::getColNum() { //return colNum
    return colNum;
}

int BattleShip::AiBoard::getRowNum() { //return rowNum
    return rowNum;
}

bool BattleShip::AiBoard::isShip(int row, int col) const { //return true if row, col is ship
    return (at(row, col) != '*' && at(row, col) != 'O' && at(row, col) != 'X');
}
