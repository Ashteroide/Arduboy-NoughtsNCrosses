#include <Arduboy2.h>
#include <ArduboyTones.h>

Arduboy2 arduboy;

ArduboyTones sound(arduboy.audio.enabled);

struct Screen
{
    uint16_t width = Arduboy2::width();
    uint16_t height = Arduboy2::height();
};
Screen screen;

int textToMiddle(int charWidth, int x1, int x2)
{
    int textCentre = ( (charWidth * 6) / 2 );
    int xCentre = ( (x2 - x1) / 2 );

    return ( (xCentre - textCentre) + x1 );
}

#include "GameState.h"
GameState gameState = GameState::Menu;

#include "GamePlayState.h"
GamePlayState gamePlayState;

#include "MenuState.h"
MenuState menuState;

#include "EndState.h"
EndState endState;


void setup()
{
    arduboy.begin();
}

void loop()
{
    if(!arduboy.nextFrame())
        return;
    
    arduboy.pollButtons();

    arduboy.clear();

    switch(gameState)
    {
        case GameState::Menu:
            menuState.draw();
            menuState.update();
            break;

        case GameState::Game:
            gamePlayState.draw();
            gamePlayState.update();
            break;

        case GameState::End:
            endState.draw();
            endState.update();
            break;
    }

    arduboy.display();
}