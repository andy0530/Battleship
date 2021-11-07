//
// Created by Andy Lee on 2019-06-13.
//

#ifndef BATTLESHIP_PLAYMODE3_H
#define BATTLESHIP_PLAYMODE3_H

#include <map>
#include "Player.h"
#include "AiBoard.h"
#include "AiMove.h"

namespace BattleShip{
    class PlayMode3{ //ai vs ai mode
    public:
        PlayMode3(int rowNum, int colNum, int shipNum, const std::map<char, int>& ships);
        void play();
        int askAichoice();
        void askMove(int id);
        bool aiPlayCheck(int row, int col, int id);
        void display(int id);
        bool checkWin(int id);

    private:
        int rowNum;
        int colNum;
        int shipNum;
        std::map<char, int> ships;
        int choice1;
        Player player1;
        AiBoard player1Board;
        int choice2;
        Player player2;
        AiBoard player2Board;
        AiMove Ai1;
        AiMove Ai2;

    };
}
#endif //BATTLESHIP_PLAYMODE3_H
