//
// Created by Andy Lee on 2019-06-12.
//

#ifndef BATTLESHIP_PLAYMODE2_H
#define BATTLESHIP_PLAYMODE2_H

#include <map>
#include "Player.h"
#include "Board.h"
#include "AiBoard.h"
#include "AiMove.h"

namespace BattleShip{
    class PlayMode2{ //player vs ai mode
    public:
        PlayMode2(int rowNum, int colNum, int shipNum, const std::map<char, int>& ships);
        void play();
        void askMove(int id);
        int askAichoice();
        void display(int id);
        bool checkMove(const std::string& input);
        bool playCheck(int row, int col);
        bool aiPlayCheck(int row, int col);
        bool checkWin(int id);



    private:
        int rowNum;
        int colNum;
        int shipNum;
        std::map<char, int> ships;
        Player player1;
        Board player1Board;
        int choice;
        Player player2;
        AiBoard player2Board;
        AiMove Ai;
    };
}
#endif //BATTLESHIP_PLAYMODE2_H
