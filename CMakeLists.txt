cmake_minimum_required(VERSION 3.14)
project(BattleShip)

set(CMAKE_CXX_STANDARD 14)

add_executable(BattleShip
        main.cpp
        Utility.cpp Utility.h
        Player.cpp Player.h
        Board.cpp Board.h
        Setup.cpp Setup.h
        PlayMode1.cpp PlayMode1.h
        PlayMode2.cpp PlayMode2.h
        AiBoard.cpp AiBoard.h
        AiMove.cpp AiMove.h
        PlayMode3.cpp PlayMode3.h)
add_compile_options(BattleShip PRIVATE -Wall -Werror)