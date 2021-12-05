#pragma once

#include "Board.h"
Board board;

struct GamePlayState
{
    void update()
    {
        if(arduboy.justPressed(B_BUTTON))
            GameState gameState = GameState::Menu;
    }

    void draw()
    {
        board.drawGrid();
        board.drawInfoBox();
    }   
};