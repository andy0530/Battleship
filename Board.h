//
// Created by Andy Lee on 2019-06-02.
//

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include <vector>
#include <string>
#include <map>

namespace BattleShip{
    class Board{
    public:
        //constructor for player board
        explicit Board(int rowNum, int colNum, std::map<char, int> ships, std::string name);
        void display() const;
        void firingDisplay() const;
        void set(int row, int col, char marker);
        bool isBlank(int row, int col) const;
        bool isShip(int row, int col) const;
        bool charCheck (char marker);
        bool placeCheck(std::string horzOrVert, int size, int row, int col, char marker);
        bool rowColInputCheck(std::string input, std::string horzOrVert, char marker, int size);
        const char& at(int row, int col) const;


    private:
        std::vector<std::string> boardState;
        const int rowNum;
        const int colNum;
        std::map<char, int> ships;
        std::string name;

    };
}
#endif //BATTLESHIP_BOARD_H
