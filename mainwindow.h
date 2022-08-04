#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// our stuff
#include "board.h"
#include "dialogs.h"

// Qt stuff
#include <QMainWindow>

// std stuff
#include <iostream>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setNewBoard(int sideLength, int numMines);
    void newGame();
    void chooseDifficulty();
    void quit();

public slots:
    void onTileClicked(bool isBomb, int row, int col);

private:
    Board * boardLayout;
    Ui::MainWindow *ui;
    bool gameOver = false;
    bool success = false;

    // 0 = easy, 1 = medium, 2 = hard
    int difficulty = 1;
    // 10 = easy, 16 = medium, 24 = hard
    int sideLength = 16;
    // 9 = easy, 40 = medium, 99 = hard
    int numMines = 40;


};



#endif // MAINWINDOW_H
