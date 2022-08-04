#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QPushButton>
#include <QGridLayout>
#include <QMouseEvent>

// class to output custom signals and whether
// the tile contains a bomb or not.
class Tile : public QPushButton
{
    Q_OBJECT;
public:
    bool bomb = false;
    int row;
    int col;

    Tile(int row, int col):QPushButton()
    {
        this->row = row;
        this->col = col;
        connect(this,SIGNAL(clicked()),SLOT(onClicked()));
    }
private slots:
    void mousePressEvent(QMouseEvent *e)
    {
        if(e->button()==Qt::RightButton)
                this->setText("?");
        if(e->button()==Qt::LeftButton)
                emit clicked();
    }
    void onClicked()
    {
        this->clearFocus();
        this->setDisabled(true);
        emit tileClicked(this->bomb,this->row,this->col);
    }
signals:
    // create a custom signal that emits the buttons position
    void tileClicked(bool isBomb, int row, int col);
};

// getter and setter class for tiles
class Board : public QGridLayout
{
public:
    Board(int sideLength, int numMines);
    void addTile(Tile * tile)
    {
       tiles.append(tile);
       this->addWidget(tile, tile->row,tile->col);
    }
    QList<Tile*> getTiles()
    {
        return tiles;
    }
    Tile * getTile(int row, int col)
    {
        return tiles[sideLength*row + col];
    }
    void setMines(int numMines);
    void clear();
    int checkNeighbours(int row, int col);
    QList<Tile*> getNeighbours(int row, int col);
    // function to check whether an index is within the bounds.
    bool isValid(int row, int col)
    {
        return (row >= 0) && (row < sideLength) &&
                (col >= 0) && (col < sideLength);
    }
    // stores all the tiles as a list
    QList<Tile*> tiles;

    int getMovesLeft();
private:
    // variable to help with iterating through the list of tiles (for getTile)
    int sideLength;
};

#endif // BOARD_H
