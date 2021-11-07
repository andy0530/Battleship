//
// Created by Andy Lee on 2019-06-12.
//

#ifndef BATTLESHIP_AIBOARD_H
#define BATTLESHIP_AIBOARD_H

#include <vector>
#include <string>
#include <map>
#include <random>

namespace BattleShip{
    class AiBoard{
    public:
        //friend aiMove to use randomNumberGenerator
        friend class AiMove;
        //constructor for ai board
        explicit AiBoard(int rowNum, int colNum, const std::map<char, int>& ships, const std::string& name);
        static void seed_random_number_generator(int seed);
        bool placeCheck(int rowStart, int colStart, int rowEnd, int colEnd);
        void display() const;
        void firingDisplay() const;
        void placeShip(char marker,int rowStart, int colStart, int rowEnd, int colEnd);
        void set(int row, int col, char marker);
        bool isBlank(int row, int col) const;
        bool isShip(int row, int col) const;
        char at(int row, int col) const;
        bool charCheck(char marker);
        int getColNum();
        int getRowNum();

    protected:
        static std::mt19937 randomNumberGenerator;

    private:
        std::vector<std::string> boardState;
        const int colNum;
        const int rowNum;
        std::map<char, int> ships;
        std::string name;
    };
}

#endif //BATTLESHIP_AIBOARD_H
