#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setNewBoard(this->sideLength,this->numMines);
    connect(this->ui->actionNew_Game, &QAction::triggered,this, &MainWindow::newGame);
    connect(this->ui->actionQuit, &QAction::triggered,this, &MainWindow::quit);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quit()
{
    this->hide();
    std::exit(0);
}

void MainWindow::setNewBoard(int sideLength,int numMines)
{
    this->setFixedSize(0,0);
    boardLayout = new Board(sideLength, numMines);
    for (auto tile: boardLayout->tiles)
    {
        connect(tile, &Tile::tileClicked, this, &MainWindow::onTileClicked);
    }
    ui->centralwidget->setLayout(boardLayout);
    this->resize(boardLayout->minimumSize());
}
void MainWindow::onTileClicked(bool isBomb, int row, int col)
{
    if (isBomb)
    {
        gameOver = true;

        for (auto tile: boardLayout->tiles)
        {
            if (tile->bomb)
            {
                tile->setText("B");
            }
        }
        newGame();
        return;
    }

    int numBombs = boardLayout->checkNeighbours(row,col);
    if (numBombs)
    {
        boardLayout->getTile(row,col)->setText(to_string(numBombs).c_str());
    }
    else
    {
        // clear question marks if there were any set
        boardLayout->getTile(row,col)->setText("");

        QList<Tile*> neighbours = boardLayout->getNeighbours(row,col);
        for (auto neighbour:neighbours)
        {
            neighbour->click();
        }
    }
    if (boardLayout->getMovesLeft() == 0)
    {
        success = true;
        newGame();
    }
}
void MainWindow::newGame()
{
    this->chooseDifficulty();
    boardLayout->clear();
    delete boardLayout;
    this->setNewBoard(sideLength,numMines);
}

void MainWindow::chooseDifficulty()
{
    QStringList difficulties({"Easy","Medium","Hard"});
    QString message = "Please choose difficulty:";

    if (gameOver)
    {
        message = "Game Over! Would you like to try again?";
        gameOver = false;
    }
    if (success)
    {
        message = "Hurray! You finished the game. Would you like to play again?";
    }

    ChooserDialog dialog(difficulties, message);



    if (dialog.exec() == QDialog::Accepted)
    {
        QString choice = dialog.comboBox()->currentText();
        this->difficulty = difficulties.indexOf(choice);
        switch(this->difficulty)
        {
        case 0:
            this->sideLength = 9;
            this->numMines = 10;
            break;

        case 1:
            this->sideLength = 16;
            this->numMines = 40;
            break;

        case 2:
            this->sideLength = 24;
            this->numMines = 99;
            break;
        }

    }

}

