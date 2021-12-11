#pragma once

#include "Board.h"
Board board;

#include "BoardCombinations.h"

struct GamePlayState
{

    uint8_t player1[3][3]
    {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    uint8_t player2[3][3]
    {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    uint8_t cursorRow = 0;
    uint8_t cursorColumn = 0;

    bool player1Turn = true;
    bool player1Won = false;
    bool gameDraw = false;

    uint8_t turns = 0;

    void update()
    {
        if(arduboy.justPressed(UP_BUTTON) && this->cursorColumn > 0)
            --this->cursorColumn;
        else if(arduboy.justPressed(DOWN_BUTTON) && this->cursorColumn < 2)
            ++this->cursorColumn;

        if(arduboy.justPressed(LEFT_BUTTON) && this->cursorRow > 0)
            --this->cursorRow;
        else if(arduboy.justPressed(RIGHT_BUTTON) && this->cursorRow < 2)
            ++this->cursorRow;
        
        if(arduboy.justPressed(A_BUTTON))
        {
            if(this->player1[this->cursorColumn][this->cursorRow] != 1 && this->player2[this->cursorColumn][this->cursorRow] != 1)
            {
                if(!this->player1Turn)
                {
                    this->player2[this->cursorColumn][this->cursorRow] = 1;

                    this->player1Turn = !this->player1Turn;
                }
                else
                {
                    this->player1[this->cursorColumn][this->cursorRow] = 1;

                    this->player1Turn = !this->player1Turn;
                }

                ++this->turns;
            }
        }

        for(size_t columns = 0; columns < 3; ++columns)
        {
            for(size_t rows = 0; rows < 3; ++rows)
            {
                for(size_t set = 0; set < 8; ++set)
                {
                    if(this->player1[columns][rows] == combinations[set][columns][rows])
                        this->player1Won = true;
                    else if(this->player2[columns][rows] == combinations[set][columns][rows])
                        this->player1Won = false;
                }
            }
        }
    }

    void draw()
    {
        board.drawGrid();
        board.drawInfoBox();

        arduboy.setCursor(0, 0);
        arduboy.print( (this->player1Won) ? F("P1") : F("P2") );
    }

    uint8_t noughtPosX = ( ((board.gridWidth / board.gridRows) - board.gridPixelSetback) );
    uint8_t noughtPosY = ( ((board.gridHeight / board.gridColumns) - board.gridPixelSetback) );

    const uint8_t noughtRadius = noughtPosX / 2;

    void drawCursor()
    {
        const uint8_t cursorBoxOffset = 2;
        const uint8_t cursorBoxWidth = ( (board.gridWidth / board.gridRows) - (cursorBoxOffset * 2) );

        uint8_t cursorPosX = ( (this->cursorRow * this->noughtPosX) + board.gridPosX + cursorBoxOffset );
        uint8_t cursorPosY = ( (this->cursorColumn * this->noughtPosY) + board.gridPosY + cursorBoxOffset );

        arduboy.drawRect( cursorPosX, cursorPosY, cursorBoxWidth, cursorBoxWidth );
    }

    void drawNought()
    {
        for(size_t columns = 0; columns < 3; ++columns)
        {
            for(size_t rows = 0; rows < 3; ++rows)
            {
                if(this->player2[columns][rows] == 1)
                {
                    arduboy.drawCircle(
                        ( (this->noughtPosX * rows) + board.gridPosX + this->noughtRadius ),
                        ( (this->noughtPosY * columns) + board.gridPosY + this->noughtRadius ),
                        noughtRadius
                    );
                }

                if(!this->player1Turn)
                {
                    const uint8_t noughtsTurnPosX = ( board.infoBoxPosX + (board.infoBoxWidth / 2) );
                    const uint8_t noughtsTurnPosY = ( board.infoBoxPosY + (board.infoBoxWidth / 2) );
                    const uint8_t noughtsTurnRadius = ((board.infoBoxWidth / 2) - board.gridPixelSetback);

                    arduboy.drawCircle( noughtsTurnPosX, noughtsTurnPosY, noughtsTurnRadius );
                }
            }
        }
    }

    const uint8_t crossWidth = ( (board.gridWidth / board.gridRows) - board.gridPixelSetback );


    void drawCross()
    {
        for(size_t columns = 0; columns < 3; ++columns)
        {
            for(size_t rows = 0; rows < 3; ++rows)
            {
                if(this->player1[columns][rows] == 1)
                {
                    uint8_t crossPosX0 = ( (this->crossWidth * rows) + board.gridPosX );
                    uint8_t crossPosX1 = ( (this->crossWidth * rows) + board.gridPosX + this->crossWidth );
                    uint8_t crossPosY0 = ( (this->crossWidth * columns) + board.gridPosY );
                    uint8_t crossPosY1 = ( (this->crossWidth * columns) + board.gridPosY + this->crossWidth );

                    arduboy.drawLine( crossPosX0, crossPosY0, crossPosX1, crossPosY1 );
                    
                    arduboy.drawLine( crossPosX1, crossPosY0, crossPosX0, crossPosY1 );
                }

                if(this->player1Turn)
                {
                    const uint8_t crossesTurnPosX = ( board.infoBoxPosX + (board.infoBoxWidth / 2) );
                    const uint8_t crossesTurnPosY = ( board.infoBoxPosY + (board.infoBoxWidth / 2) );
                    const uint8_t crossesTurnRadius = ((board.infoBoxWidth / 2) - board.gridPixelSetback);

                    const uint8_t crossesTurnPosX0 = board.infoBoxPosX;
                    const uint8_t crossesTurnPosX1 = board.infoBoxPosX + board.infoBoxWidth;
                    const uint8_t crossesTurnPosY0 = board.infoBoxPosY;
                    const uint8_t crossesTurnPosY1 = board.infoBoxPosY + board.infoBoxWidth;

                    arduboy.drawLine( crossesTurnPosX0, crossesTurnPosY0, crossesTurnPosX1, crossesTurnPosY1 );
                    arduboy.drawLine( crossesTurnPosX1, crossesTurnPosY0, crossesTurnPosX0, crossesTurnPosY1 );
                }
            }
        }
    }
};