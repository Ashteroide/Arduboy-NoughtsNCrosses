#pragma once

struct Board
{
    const uint8_t gridRows = 3;
    const uint8_t gridColumns = this->gridRows;
    const uint8_t gridWidth = 60;
    const uint8_t gridHeight = 60;
    const uint8_t gridPosX = 20;
    const uint8_t gridPosY = ( (screen.height - this->gridHeight + this->gridColumns) / 2 ); // Center Grid
    const uint8_t gridPixelSetback = 1; // Moves back 1 pixel so the rectangle edges are aligned to create a perfect grid

    void drawGrid()
    {
        for(size_t columns = 0; columns < this->gridColumns; ++columns)
        {
            for(size_t rows = 0; rows < this->gridRows; ++rows)
            {
                arduboy.drawRect( ((((this->gridWidth / this->gridRows) - this->gridPixelSetback) * rows) + this->gridPosX),
                ((((this->gridHeight / this->gridColumns) - this->gridPixelSetback) * columns) + this->gridPosY),
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