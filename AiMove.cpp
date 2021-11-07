//
// Created by Andy Lee on 2019-06-12.
//

#include "AiMove.h"
#include "Player.h"
#include "Board.h"
#include "PlayMode2.h"
#include "Utility.h"

BattleShip::AiMove::AiMove(int choice, AiBoard board) :
choice(choice),
rowNum(board.getRowNum()),
colNum(board.getColNum())
{
    if (choice == 2 || choice == 3){ //make pair of every possible location on board
        for (int i = 0; i < rowNum; i++){
            for (int j = 0; j < colNum; j++){
                target.emplace_back(std::pair<int, int>(i,j));
            }
        }
    }
}

std::pair<int, int> BattleShip::AiMove::makeMove(const Board& oppBoard) { //calls functions depending on choice
    if (choice == 1){
        return cheatingAi(oppBoard);
    }
    else if (choice == 2){
        return randomAi();
    }
    else if (choice == 3){
        return huntDestroyAi(oppBoard);
    }
    return {0, 0};
}

std::pair<int, int> BattleShip::AiMove::makeMove(const AiBoard& oppBoard) { //calls functions depending on choice
    if (choice == 1){
        return cheatingAi(oppBoard);
    }
    else if (choice == 2){
        return randomAi();
    }
    else if (choice == 3){
        return huntDestroyAi(oppBoard);
    }
    return {0, 0};
}

std::pair<int, int> BattleShip::AiMove::cheatingAi(const Board& oppBoard) {
    //find the fist element in order of row, col that is a ship
    for (int i = 0; i < rowNum; i++){
        for (int j = 0; j < colNum; j++){
            char shoot = oppBoard.at(i,j);
            if (!(shoot == '*' || shoot == 'O' || shoot == 'X')){
                return {i,j};
            }
        }
    }
    return {0, 0};
}

std::pair<int, int> BattleShip::AiMove::cheatingAi(const AiBoard& oppBoard) {
    //find the fist element in order of row, col that is a ship
    for (int i = 0; i < rowNum; i++){
        for (int j = 0; j < colNum; j++){
            char shoot = oppBoard.at(i,j);
            if (!(shoot == '*' || shoot == 'O' || shoot == 'X')){
                return {i,j};
            }
        }
    }
    return {0, 0};
}


std::pair<int, int> BattleShip::AiMove::randomAi() { //use random number generator from aiBoard to pick one selection
    auto random = chooseRandom(target, BattleShip::AiBoard::randomNumberGenerator);
    std::pair<int, int> selection = {(*random).first, (*random).second};
    target.erase(random);
    return selection;
}

std::pair<int, int> BattleShip::AiMove::huntDestroyAi(const Board& oppBoard) { //ai selection for hunt and destroy mode
    std::pair<int, int> selection;
    if (nextTarget.empty()){ //if in hunt mode
        selection = randomAi(); //randomly pick one selection
        char shoot = oppBoard.at(selection.first,selection.second);
        if (!(shoot == '*' || shoot == 'O' || shoot == 'X')){ //if selection is a hit
            makeNextTarget(selection, oppBoard); //make left, up, right, down the next target
        }
    }
    else{ //if in destroy mode
        selection = nextTarget[0]; //do first move of the list
        char shoot = oppBoard.at(selection.first,selection.second); //if selection is a hit
        if (!(shoot == '*' || shoot == 'O' || shoot == 'X')){ //make left, up, right, down the next target
            makeNextTarget(selection, oppBoard);
        }
        nextTarget.erase(nextTarget.begin()); //erase the move from list
    }
    for (auto i = target.begin(); i != target.end(); i++){ //erase move from possible moves
        if(*i==selection){
            target.erase(i);
            break;
        }
    }
    return selection;
}

std::pair<int, int> BattleShip::AiMove::huntDestroyAi(const AiBoard& oppBoard) { //ai selection for hunt and destroy mode
    std::pair<int, int> selection;
    if (nextTarget.empty()){ //if in hunt mode
        selection = randomAi(); //randomly pick one selection
        char shoot = oppBoard.at(selection.first,selection.second);
        if (!(shoot == '*' || shoot == 'O' || shoot == 'X')){ //if selection is a hit
            makeNextTarget(selection, oppBoard); //make left, up, right, down the next target
        }
    }
    else{ //if in destroy mode
        selection = nextTarget[0]; //do first move of the list
        char shoot = oppBoard.at(selection.first,selection.second); //if selection is a hit
        if (!(shoot == '*' || shoot == 'O' || shoot == 'X')){ //make left, up, right, down the next target
            makeNextTarget(selection, oppBoard);
        }
        nextTarget.erase(nextTarget.begin()); //erase the move from list
    }
    for (auto i = target.begin(); i != target.end(); i++){ //erase move from possible moves
        if(*i==selection){
            target.erase(i);
            break;
        }
    }
    return selection;
}

void BattleShip::AiMove::makeNextTarget(std::pair<int, int> selection, const Board& oppBoard) {
    if (selection.second-1 >= 0 && selection.second-1<rowNum) { //check if left element is in bound
        if (!(oppBoard.at(selection.first, selection.second - 1) == 'O' || //check if left element has not been attacked
              oppBoard.at(selection.first, selection.second - 1) == 'X')) {
            nextTarget.emplace_back(std::pair<int, int>(selection.first, selection.second - 1)); //adds to next target
        }
    }
    if (selection.first-1 >= 0 && selection.first-1<rowNum) { //check if up element is in bound
        if (!(oppBoard.at(selection.first - 1, selection.second) == 'O' || //check if up element has not been attacked
              oppBoard.at(selection.first - 1, selection.second) == 'X')) {
            nextTarget.emplace_back(std::pair<int, int>(selection.first - 1, selection.second)); //adds to next target
        }
    }
    if (selection.second+1 >= 0 && selection.second+1<rowNum) { //check if right element is in bound
        if (!(oppBoard.at(selection.first, selection.second + 1) == 'O' || //check if right element has not been attacked
              oppBoard.at(selection.first, selection.second + 1) == 'X')) {
            nextTarget.emplace_back(std::pair<int, int>(selection.first, selection.second + 1)); //adds to next target
        }
    }
    if (selection.first+1 >= 0 && selection.first+1<rowNum) { //check if down element is in bound
        if (!(oppBoard.at(selection.first + 1, selection.second) == 'O' || //check if down element has not been attacked
              oppBoard.at(selection.first + 1, selection.second) == 'X')) {
            nextTarget.emplace_back(std::pair<int, int>(selection.first + 1, selection.second)); //adds to next target
        }
    }
}

void BattleShip::AiMove::makeNextTarget(std::pair<int, int> selection, const AiBoard& oppBoard) {
    if (selection.second-1 >= 0 && selection.second-1<rowNum) { //check if left element is in bound
        if (!(oppBoard.at(selection.first, selection.second - 1) == 'O' || //check if left element has not been attacked
              oppBoard.at(selection.first, selection.second - 1) == 'X')) {
            nextTarget.emplace_back(std::pair<int, int>(selection.first, selection.second - 1)); //adds to next target
        }
    }
    if (selection.first-1 >= 0 && selection.first-1<rowNum) { //check if up element is in bound
        if (!(oppBoard.at(selection.first - 1, selection.second) == 'O' || //check if up element has not been attacked
              oppBoard.at(selection.first - 1, selection.second) == 'X')) {
            nextTarget.emplace_back(std::pair<int, int>(selection.first - 1, selection.second)); //adds to next target
        }
    }
    if (selection.second+1 >= 0 && selection.second+1<rowNum) { //check if right element is in bound
        if (!(oppBoard.at(selection.first, selection.second + 1) == 'O' || //check if right element has not been attacked
              oppBoard.at(selection.first, selection.second + 1) == 'X')) {
            nextTarget.emplace_back(std::pair<int, int>(selection.first, selection.second + 1)); //adds to next target
        }
    }
    if (selection.first+1 >= 0 && selection.first+1<rowNum) { //check if down element is in bound
        if (!(oppBoard.at(selection.first + 1, selection.second) == 'O' || //check if down element has not been attacked
              oppBoard.at(selection.first + 1, selection.second) == 'X')) {
            nextTarget.emplace_back(std::pair<int, int>(selection.first + 1, selection.second)); //adds to next target
        }
    }
}


