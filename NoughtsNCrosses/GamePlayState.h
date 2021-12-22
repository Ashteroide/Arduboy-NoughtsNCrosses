#pragma once

#include "Board.h"
Board board;

struct GamePlayState
{
    uint8_t player1[3][3]{
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0} };

    uint8_t player2[3][3]{
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0} };

    uint8_t cursorColumn = 0;
    uint8_t cursorRow = 0;

    bool player1Turn = true;
    bool player1Won = false;
    bool player2Won = false;

    bool gameDraw = false;

    uint8_t turns = 0;

    void player1WinCheck()
    {
        uint8_t player1Matches = 0;

        // Horizontal Rows
        for(size_t row = 0; row < board.gridRows; ++row)
        {
            for(size_t column = 0; column < board.gridColumns; ++column)
            {
                if(player1[row][column] == 1)
                    ++player1Matches;
            }

            if(player1Matches >= board.gridColumns)
                player1Won = true;
            else
                player1Matches = 0;
        }

        // Vertical Columns
        for(size_t row = 0; row < board.gridRows; ++row)
        {
            uint8_t player1Matches = 0;

            for(size_t column = 0; column < board.gridColumns; ++column)
            {
                if(player1[column][row] == 1)
                    ++player1Matches;
            }

            if(player1Matches >= board.gridColumns)
                player1Won = true;
            else
                player1Matches = 0;
        }

        //Downwards Diagonally
        for(size_t index = 0; index < 3; ++index)
        {
            if(this->player1[index][index] == 1)
                ++player1Matches;
        }

        if(player1Matches >= 3)
            this->player1Won = true;
        else
            player1Matches = 0;

        //Upwards Diagonally
        uint8_t rowIndex = 0;

        for(int index = (board.gridColumns - 1); index > -1; --index)
        {
            if(this->player1[rowIndex][index] == 1)
                ++player1Matches;

            ++rowIndex;
        }

        if(player1Matches >= board.gridColumns)
            this->player1Won = true;
        else
            player1Matches = 0;
    }

    void player2WinCheck()
    {
        uint8_t player2Matches = 0;

        // Horizontal Rows
        for(size_t row = 0; row < board.gridRows; ++row)
        {
            for(size_t column = 0; column < board.gridColumns; ++column)
            {
                if(this->player2[row][column] == 1)
                    ++player2Matches;
            }

            if(player2Matches >= board.gridColumns)
                this->player2Won = true;
            else
                player2Matches = 0;
        }

        // Vertical Columns
        for(size_t row = 0; row < board.gridRows; ++row)
        {
            uint8_t player2Matches = 0;

            for(size_t column = 0; column < board.gridColumns; ++column)
            {
                if(this->player2[column][row] == 1)
                    ++player2Matches;
            }

            if(player2Matches >= board.gridColumns)
                this->player2Won = true;
            else
                player2Matches = 0;
        }

        //Downwards Diagonally
        for(size_t index = 0; index < 3; ++index)
        {
            if(this->player2[index][index] == 1)
                ++player2Matches;
        }

        if(player2Matches >= board.gridColumns)
            this->player2Won = true;
        else
            player2Matches = 0;

        //Upwards Diagonally
        uint8_t rowIndex = 0;

        for(int index = (board.gridColumns - 1); index > -1; --index)
        {
            if(this->player2[rowIndex][index] == 1)
                ++player2Matches;

            ++rowIndex;
        }

        if(player2Matches >= board.gridColumns)
            this->player2Won = true;
        else
            player2Matches = 0;
    }

    void update()
    {
        if(arduboy.justPressed(UP_BUTTON) && this->cursorRow > 0)
            --this->cursorRow;
        else if(arduboy.justPressed(DOWN_BUTTON) && this->cursorRow < 2)
            ++this->cursorRow;

        if(arduboy.justPressed(LEFT_BUTTON) && this->cursorColumn > 0)
            --this->cursorColumn;
        else if(arduboy.justPressed(RIGHT_BUTTON) && this->cursorColumn < 2)
            ++this->cursorColumn;

        if(arduboy.justPressed(A_BUTTON))
        {
            if(this->player1[this->cursorRow][this->cursorColumn] != 1 && this->player2[this->cursorRow][this->cursorColumn] != 1)
            {
                if(!this->player1Turn)
                {
                    this->player2[this->cursorRow][this->cursorColumn] = 1;

                    this->player1Turn = !this->player1Turn;
                }
                else
                {
                    this->player1[this->cursorRow][this->cursorColumn] = 1;

                    this->player1Turn = !this->player1Turn;
                }

                ++this->turns;
            }
        }

        player1WinCheck();
        player2WinCheck();
    }

    void draw()
    {
        board.drawGrid();
        board.drawInfoBox();

        arduboy.setCursor(0, 0);
        arduboy.print((this->player1Won) ? F("P1") : F("!"));
        arduboy.print((this->player2Won) ? F("P2") : F("!"));

        arduboy.setCursor(0, 10);
        arduboy.print((this->gameDraw) ? F("Draw") : F("!Draw"));
    }

    uint8_t noughtPosX = (((board.gridWidth / board.gridRows) - board.gridPixelSetback));
    uint8_t noughtPosY = (((board.gridHeight / board.gridColumns) - board.gridPixelSetback));

    void drawCursor()
    {
        const uint8_t cursorBoxOffset = 2;
        const uint8_t cursorBoxWidth = ((board.gridWidth / board.gridRows) - (cursorBoxOffset * 2));

        uint8_t cursorPosX = ((this->cursorColumn * this->noughtPosX) + board.gridPosX + cursorBoxOffset);
        uint8_t cursorPosY = ((this->cursorRow * this->noughtPosY) + board.gridPosY + cursorBoxOffset);

        arduboy.drawRect(cursorPosX, cursorPosY, cursorBoxWidth, cursorBoxWidth);
    }

    const uint8_t noughtRadius = noughtPosX / 2;

    void drawNought()
    {
        for(size_t rows = 0; rows < 3; ++rows)
        {
            for(size_t columns = 0; columns < 3; ++columns)
            {
                if(this->player2[rows][columns] == 1)
                {
                    const uint8_t circlePosX = (this->noughtPosX * columns) + board.gridPosX + this->noughtRadius;
                    const uint8_t circlePosY = (this->noughtPosY * rows) + board.gridPosY + this->noughtRadius;

                    arduboy.drawCircle(circlePosX, circlePosY, noughtRadius);
                }

                if(!this->player1Turn)
                {
                    const uint8_t noughtsTurnPosX = (board.infoBoxPosX + (board.infoBoxWidth / 2));
                    const uint8_t noughtsTurnPosY = (board.infoBoxPosY + (board.infoBoxWidth / 2));
                    const uint8_t noughtsTurnRadius = ((board.infoBoxWidth / 2) - board.gridPixelSetback);

                    arduboy.drawCircle(noughtsTurnPosX, noughtsTurnPosY, noughtsTurnRadius);
                }
            }
        }
    }

    const uint8_t crossWidth = ((board.gridWidth / board.gridRows) - board.gridPixelSetback);

    void drawCross()
    {
        for(size_t rows = 0; rows < 3; ++rows)
        {
            for(size_t columns = 0; columns < 3; ++columns)
            {
                if(this->player1[rows][columns] == 1)
                {
                    const uint8_t crossPosX0 = ((this->crossWidth * columns) + board.gridPosX);
                    const uint8_t crossPosX1 = ((this->crossWidth * columns) + board.gridPosX + this->crossWidth);
                    const uint8_t crossPosY0 = ((this->crossWidth * rows) + board.gridPosY);
                    const uint8_t crossPosY1 = ((this->crossWidth * rows) + board.gridPosY + this->crossWidth);

                    arduboy.drawLine(crossPosX0, crossPosY0, crossPosX1, crossPosY1);

                    arduboy.drawLine(crossPosX1, crossPosY0, crossPosX0, crossPosY1);
                }

                if(this->player1Turn)
                {
                    const uint8_t crossesTurnPosX = (board.infoBoxPosX + (board.infoBoxWidth / 2));
                    const uint8_t crossesTurnPosY = (board.infoBoxPosY + (board.infoBoxWidth / 2));
                    const uint8_t crossesTurnRadius = ((board.infoBoxWidth / 2) - board.gridPixelSetback);

                    const uint8_t crossesTurnPosX0 = board.infoBoxPosX;
                    const uint8_t crossesTurnPosX1 = board.infoBoxPosX + board.infoBoxWidth;
                    const uint8_t crossesTurnPosY0 = board.infoBoxPosY;
                    const uint8_t crossesTurnPosY1 = board.infoBoxPosY + board.infoBoxWidth;

                    arduboy.drawLine(crossesTurnPosX0, crossesTurnPosY0, crossesTurnPosX1, crossesTurnPosY1);
                    arduboy.drawLine(crossesTurnPosX1, crossesTurnPosY0, crossesTurnPosX0, crossesTurnPosY1);
                }
            }
        }
    }
};