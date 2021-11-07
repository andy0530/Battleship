//
// Created by Andy Lee on 2019-06-12.
//

#ifndef BATTLESHIP_PLAYMODE1_H
#define BATTLESHIP_PLAYMODE1_H

#include <map>
#include "Player.h"
#include "Board.h"

namespace BattleShip{
    class PlayMode1{ //player vs player mode
    public:
        PlayMode1(int rowNum, int colNum, int shipNum, const std::map<char, int>& ships);
        void display(int id);
        void askMove(int id);
        bool checkMove (const std::string &input, int id);
        bool checkWin(int id);
        bool playCheck (int row, int col, int id);
        void play();


    private:
        int shipNum;
        int rowNum;
        int colNum;
        std::map<char, int> ships;
        Player player1;
        Board player1Board;
        Player player2;
        Board player2Board;
    };
}

#endif //BATTLESHIP_PLAYMODE1_H
