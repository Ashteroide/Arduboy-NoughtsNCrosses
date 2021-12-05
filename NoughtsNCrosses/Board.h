#pragma once

struct Board
{
    uint8_t gridRows = 3;
    uint8_t gridColumns = 3;
    uint8_t gridWidth = 60;
    uint8_t gridHeight = 60;
    uint8_t gridPosX = 20;
    uint8_t gridPosY = ( (screen.height - this->gridHeight + this->gridColumns) / 2 ); // Center Grid

    void drawGrid()
    {
        for(size_t columns = 0; columns < this->gridColumns; ++columns)
        {
            for(size_t rows = 0; rows < this->gridRows; ++rows)
            {
                arduboy.drawRect( ((((this->gridWidth / this->gridRows) - 1) * rows) + this->gridPosX),
                ((((this->gridHeight / this->gridColumns) - 1) * columns) + this->gridPosY),
                (this->gridWidth / this->gridRows), 
                (this->gridHeight / this->gridColumns) );
            }
        }
    }

    const uint8_t infoBoxWidth = 20;
    const uint8_t infoBoxPosX = screen.width - this->infoBoxWidth - 10;
    const uint8_t infoBoxPosY = this->gridPosY + 8;

    void drawInfoBox()
    {
        arduboy.drawRect( this->infoBoxPosX, this->infoBoxPosY, this->infoBoxWidth, this->infoBoxWidth );

        arduboy.setCursor( textToMiddle( 4, this->infoBoxPosX, (this->infoBoxPosX + this->infoBoxWidth) ), (this->infoBoxPosY - 8) );
        arduboy.print(F("Turn"));
    }
};