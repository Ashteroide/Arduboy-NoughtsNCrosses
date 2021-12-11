#pragma once

struct MenuState
{
    uint8_t menuCursor = 0;

    void update()
    {
        if(arduboy.justPressed(A_BUTTON))
        {
            if(this->menuCursor == 0)
                gameState = GameState::GamePlay;
            else if(this->menuCursor == 1)
            {
                arduboy.audio.toggle();
                sound.tone(500, 100);
            }
        }

        if(arduboy.justPressed(DOWN_BUTTON) && this->menuCursor < 1)
            ++this->menuCursor;
        else if(arduboy.justPressed(UP_BUTTON) && this->menuCursor > 0)
            --this->menuCursor;
    }

    void draw()
    {
        arduboy.setCursor( textToMiddle(7, 0, screen.width), 5 );
        arduboy.print(F("O & X's"));

        arduboy.setCursor( textToMiddle(4, 0, screen.width), 13 );
        arduboy.print(F("Play"));

        arduboy.setCursor( textToMiddle( ((arduboy.audio.enabled()) ? 8 : 9), 0, screen.width), 21 );
        arduboy.print(F("Sound:"));
        arduboy.print( (arduboy.audio.enabled()) ? F("On") : F("Off") );

        arduboy.setCursor( 30, ((this->menuCursor * 8) + 13) );
        arduboy.print(F(">"));
    }
};