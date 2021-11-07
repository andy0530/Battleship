//
// Created by Andy Lee on 2019-06-12.
//

#ifndef BATTLESHIP_AIMOVE_H
#define BATTLESHIP_AIMOVE_H

#include <vector>
#include "Player.h"
#include "AiBoard.h"
#include "Board.h"

namespace BattleShip{
    class AiMove{
    public:
        //constructor
        AiMove(int choice, AiBoard board);
        //need two versions of each function as opponent board may be player board or ai board
        std::pair<int, int> makeMove(const Board& oppBoard); //returns row, col of move
        std::pair<int, int> makeMove(const AiBoard& oppBoard); //returns row, col of move
        std::pair<int, int> cheatingAi(const Board& oppBoard); //return row, col of cheating ai mode
        std::pair<int, int> cheatingAi(const AiBoard& oppBoard); //return row, col of cheating ai mode
        std::pair<int, int> randomAi(); //return row, col of random ai mode
        std::pair<int, int> huntDestroyAi(const Board& oppBoard); //return row, col of hunt and destroy ai mode
        std::pair<int, int> huntDestroyAi(const AiBoard& oppBoard); //return row, col of hunt and destroy ai mode
        void makeNextTarget(std::pair<int, int> selection, const Board& oppBoard); //make list of next attacks for destroy mode
        void makeNextTarget(std::pair<int, int> selection, const AiBoard& oppBoard); //make list of next attacks for destroy mode

    protected:
        std::vector<std::pair<int, int>> nextTarget; //list of attacks for destroy mode
        std::vector<std::pair<int, int>> target; //possibly targets for random and hunt and destroy ai mode

    private:
        int choice; // 1-> cheating, 2->random, 3-> hunt and destroy
        int rowNum;
        int colNum;
    };
}

#endif //BATTLESHIP_AIMOVE_H
