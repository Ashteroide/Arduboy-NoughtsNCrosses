#pragma once

struct EndState
{
    void update()
    {
        if(arduboy.justPressed(A_BUTTON))
        {
            gamePlayState.resetWon();
            gamePlayState.resetBoard();

            gameState = GameState::Menu;
        }
    }

    void draw()
    {
        arduboy.setCursor(textToMiddle(14, 0, Arduboy2::width()), 28);

        if(gamePlayState.player1.won)
            arduboy.print(F("Player 1 Wins!"));
        else if(gamePlayState.player2.won)
            arduboy.print(F("Player 2 Wins!"));

        if(gamePlayState.gameDraw)
        {
            arduboy.setCursorX(textToMiddle(17, 0, Arduboy2::width()));
            arduboy.print(F("Draw! No one Won!"));
        }

        arduboy.setCursor(textToMiddle(15, 0, Arduboy2::width()), 36);
        arduboy.print(F("Press A to end!"));
    }
};