#include "board.h"

Board::Board(int sideLength, int numMines)
{
    this->sideLength = sideLength;
    this->setSpacing(0);
    for (int row = 0; row < sideLength; row ++)
    {
        for (int col = 0; col < sideLength; col ++)
        {
            Tile *tile = new Tile(row,col);
            tile->setFixedSize(30,30);
            this->addTile(tile);
        }
    }
    this->setMines(numMines);
}

void Board::setMines(int numMines)    {

    // Continue until all random mines have been created.

    for (int i = 0; i < numMines; )
    {
        int random = rand() % (sideLength * sideLength);
        int x = random / sideLength;
        int y = random % sideLength;

        // Add the mine if no mine is placed at this
        // position on the board
        Tile * tile = this->getTile(x,y);
        if (tile->bomb == false)
        {
            tile->bomb = true;
            //QIcon icon ("bomb.png");
            tile->setIcon(QIcon::fromTheme("face-smile"));
            i++;
        }
    }

    return;
}

void Board::clear()
{
    for (auto tile : tiles)
    {
        tile->hide();
        tiles.pop_front();
        this->removeWidget(tile);
        delete tile;
    }
}

int Board::checkNeighbours(int row, int col)
{

    QList<Tile*> neighbours = getNeighbours(row,col);
    int numMines = 0;
    for (auto neighbour : neighbours)
    {
        if (neighbour->bomb)
        {
            numMines += 1;
        }
    }
    return numMines;
}

QList<Tile*> Board::getNeighbours(int row, int col)
{
    QList<Tile*> neighbours;
    int neighbourIdx[8][2] =
        {
            {row - 1, col},      //North
            {row + 1, col},      //South
            {row, col + 1},      //East
            {row, col - 1},	  //West
            {row - 1, col + 1},  //North-East
            {row - 1, col - 1},  //North-West
            {row + 1, col + 1},  //South-East
            {row + 1 , col - 1}, //South-West
        };
    for (auto idx : neighbourIdx)
    {
        if (isValid(idx[0],idx[1]))
        {
            neighbours.push_back(getTile(idx[0],idx[1]));
        }
    }
return neighbours;
}

int Board::getMovesLeft()
{
    int movesLeft = 0;
    for (auto tile : tiles)
    {
        if (tile->isEnabled())
        {
            if (!tile->bomb)
            {
                movesLeft += 1;
            }
        }

    }
    return movesLeft;
}
