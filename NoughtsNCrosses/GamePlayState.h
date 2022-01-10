#pragma once

#include "Board.h"
Board board;

struct GamePlayState
{
    char playerBoard[3][3] =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    uint8_t cursorColumn = 0;
    uint8_t cursorRow = 0;

    struct Player
    {
        bool turn;
        bool won;
        uint8_t matches;
    };

    Player player1 = { true, false, 0 };
    Player player2 = { false, false, 0 };

    void resetMatches()
    {
        this->player1.matches = 0;
        this->player2.matches = 0;
    }

    bool gameDraw = false;

    uint8_t turns = 0;

    void resetWon()
    {
        this->player1.won = false;
        this->player2.won = false;

        this->player1.turn = true;
        this->player2.turn = false;

        this->gameDraw = false;
        this->turns = 0;
    }

    void resetBoard()
    {
        for(size_t row = 0; row < board.gridRows; ++row)
        {
            for(size_t column = 0; column < board.gridColumns; ++column)
            {
                this->playerBoard[row][column] = ' ';
            }
        }

        this->cursorRow = 0;
        this->cursorColumn = 0;
    }

    void playerWinCheck()
    {
        // Horizontal Rows
        for(size_t row = 0; row < board.gridRows; ++row)
        {
            for(size_t column = 0; column < board.gridColumns; ++column)
            {
                if(this->playerBoard[row][column] == 'X')
                    ++this->player1.matches;
                if(this->playerBoard[row][column] == 'O')
                    ++this->player2.matches;
            }

            if(player1.matches >= board.gridColumns)
                this->player1.won = true;
            else if(player2.matches >= board.gridColumns)
                this->player2.won = true;

            this->resetMatches();
        }

        // Vertical Rows
        for(size_t row = 0; row < board.gridRows; ++row)
        {
            for(size_t column = 0; column < board.gridColumns; ++column)
            {
                if(this->playerBoard[column][row] == 'X')
                    ++this->player1.matches;
                if(this->playerBoard[column][row] == 'O')
                    ++this->player2.matches;
            }

            if(player1.matches >= board.gridColumns)
                this->player1.won = true;
            else if(player2.matches >= board.gridColumns)
                this->player2.won = true;

            this->resetMatches();
        }

        //Downwards Diagonally
        for(size_t index = 0; index < 3; ++index)
        {
            if(this->playerBoard[index][index] == 'X')
                ++this->player1.matches;
            if(this->playerBoard[index][index] == 'O')
                ++this->player2.matches;
        }

        if(this->player1.matches >= board.gridColumns)
            this->player1.won = true;
        else if(this->player2.matches >= board.gridColumns)
            this->player2.won = true;
        
            this->resetMatches();

        //Upwards Diagonally
        uint8_t rowIndex = 0;

        for(int index = (board.gridColumns - 1); index > -1; --index)
        {
            if(this->playerBoard[rowIndex][index] == 'X')
                ++this->player1.matches;
            if(this->playerBoard[rowIndex][index] == 'O')
                ++this->player2.matches;

            ++rowIndex;
        }

        if(this->player1.matches >= board.gridColumns)
            this->player1.won = true;
        else if(this->player2.matches >= board.gridColumns)
            this->player2.won = true;
        
            this->resetMatches();
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
            if(this->playerBoard[this->cursorRow][this->cursorColumn] != 'X' && this->playerBoard[this->cursorRow][this->cursorColumn] != 'O')
            {
                if(this->player2.turn)
                {
                    this->playerBoard[this->cursorRow][this->cursorColumn] = 'O';

                    this->player2.turn = false;
                    this->player1.turn = true;
                }
                else
                {
                    this->playerBoard[this->cursorRow][this->cursorColumn] = 'X';

                    this->player1.turn = false;
                    this->player2.turn = true;
                }

                ++this->turns;
            }
        }

        playerWinCheck();

        if(this->turns >= 9)
            this->gameDraw = true;

        if(this->player1.won || this->player2.won || this->gameDraw)
            gameState = GameState::End;
    }

    void draw()
    {
        board.drawGrid();
        board.drawInfoBox();

        // Debugging!
        arduboy.setCursor(0, 0);
        arduboy.print((this->player1.won) ? F("P1") : F("!"));
        arduboy.print((this->player2.won) ? F("P2") : F("!"));

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
                if(this->playerBoard[rows][columns] == 'O')
                {
                    const uint8_t circlePosX = (this->noughtPosX * columns) + board.gridPosX + this->noughtRadius;
                    const uint8_t circlePosY = (this->noughtPosY * rows) + board.gridPosY + this->noughtRadius;

                    arduboy.drawCircle(circlePosX, circlePosY, noughtRadius);
                }

                if(!this->player1.turn)
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
                if(this->playerBoard[rows][columns] == 'X')
                {
                    const uint8_t crossPosX0 = ((this->crossWidth * columns) + board.gridPosX);
                    const uint8_t crossPosX1 = ((this->crossWidth * columns) + board.gridPosX + this->crossWidth);
                    const uint8_t crossPosY0 = ((this->crossWidth * rows) + board.gridPosY);
                    const uint8_t crossPosY1 = ((this->crossWidth * rows) + board.gridPosY + this->crossWidth);

                    arduboy.drawLine(crossPosX0, crossPosY0, crossPosX1, crossPosY1);

                    arduboy.drawLine(crossPosX1, crossPosY0, crossPosX0, crossPosY1);
                }

                if(this->player1.turn)
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