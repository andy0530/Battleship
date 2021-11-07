//
// Created by Andy Lee on 2019-06-02.
//

#include "Board.h"
#include "Player.h"
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>


BattleShip::Board::Board(int rowNum, int colNum, std::map<char, int> ships, std::string name) :
    boardState(rowNum, std::string(colNum, '*')),
    rowNum(rowNum),
    colNum(colNum),
    ships(ships),
    name(name)
    {
    display();
    for (auto const& x : ships){ //for all ships place them
        std::string selection;
        std::string rowAndCol;
        do{
            do{
                std::cout<< name << ", do you want to place " << x.first << " horizontally or vertically?" << std::endl;
                std::cout << "Enter h for horizontal or v for vertical" << std::endl;
                std::cout << "Your choice: "; //asks if want to place horizontal or vertical
                std::getline(std::cin, selection);
                if (selection == "H"){ //if uppercase change to lowercase
                    selection = "h";
                }
                else if (selection == "V"){ //if uppercase change to lowercase
                    selection = "v";
                }
            }while(!(selection == "h" || selection == "v")); //do until right input
            std::cout<< name << ", enter the row and column you want to place " << x.first; //asks for row and col
            std::cout << ", which is " << x.second << " long, at with a space in between row and col: ";
            std::getline(std::cin, rowAndCol);
        }while(!rowColInputCheck(rowAndCol, selection, x.first, x.second)); //do until row and col is valid
        display(); //display board
    }
}

void BattleShip::Board::display() const { //display board
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

void BattleShip::Board::set(int row, int col, char marker) { //change element at point to marker
    boardState.at(row).at(col) = marker;
}

bool BattleShip::Board::isBlank(int row, int col) const { //return true if at point is blank
    return boardState.at(row).at(col) == '*';
}

const char &BattleShip::Board::at(int row, int col) const { //return char at point
    return boardState.at(row).at(col);
}

bool BattleShip::Board::placeCheck(std::string horzOrVert, int size, int row, int col, char marker) { //check if input is true
    if (!(row >= 0 && row < rowNum)){ //check if in bound
        return false;
    }
    else if (!(col >= 0 && col < colNum)){ //check if in bound
        return false;
    }
    else { //check if isblank for length of ship
        if (horzOrVert == "v"){
            for (int i = 0; i < size; i++){
                if (i+row >= rowNum){
                    return false;
                }
                else if (!(isBlank(i+row, col))){
                    return false;
                }
            }

        }
        if (horzOrVert == "h"){
            for (int i = 0; i < size; i++){
                if (i+col >= colNum){
                    return false;
                }
                else if (!(isBlank(row, i+col))){
                    return false;
                }
            }

        }
    }//returned false if invalid and if valid comes down until here
    if (horzOrVert == "h"){ //place the ships
        for (int i = 0; i < size; i++){
            set(row, i+col, marker);
        }
    }
    if (horzOrVert == "v"){ //place the ships
        for (int i = 0; i < size; i++){
            set(i+row, col, marker);
        }
    }
    return true;
}

bool BattleShip::Board::rowColInputCheck(std::string input, std::string horzOrVert, char marker, int size) {
    std::list<std::string> rowAndCol; //input check
    std::string word = "";
    for (auto frag:input){ //takes input and puts into list
        if (frag == ' '){
            rowAndCol.push_back(word);
            word = "";
        }
        else{
            word += frag;
        }
    }
    rowAndCol.push_back(word);
    if (rowAndCol.size() == 2){ //input is {row, col}
        int row = std::stoi(rowAndCol.front());
        int col = std::stoi(rowAndCol.back());
        if (placeCheck(horzOrVert, size, row, col, marker)){ //see if row, col input is empty and in bound
            return true;
        }
    }
    return false;
}

void BattleShip::Board::firingDisplay() const { //display only '*', 'O', or 'X'
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

bool BattleShip::Board::charCheck(char marker) { //see if there is no more marker left on board to see if ship sunk
    for (int i = 0; i < rowNum; i++){
        for (int j = 0; j < colNum; j++){
            if (at(i,j)== marker){
                return false;
            }
        }
    }
    return true;
}

bool BattleShip::Board::isShip(int row, int col) const { //return true if there is a ship
    return (at(row, col) != '*' && at(row, col) != 'O' && at(row, col) != 'X');
}
