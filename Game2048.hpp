#ifndef GAME2048_HPP
#define GAME2048_HPP

#include <fstream>
#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

class Game2048 : public QWidget
{
    Q_OBJECT

    private:
        QVector<QVector<int>> board;    
        QVector<QVector<int>> prevBoard;    
        QVector<QVector<QLabel*>> tiles; 
        QGridLayout *gridLayout;
        QLabel *scoreLabel;
        int score;
        QLabel *bestScoreLabel;
        int bestScore;
        const int tileSize = 80;
        const int tileSpacing = 10;


        bool vide();
        void setData();     
        void getData();
        void setBestScore();
        void getBestScore();
        void initBoard();
        void updateBoard();
        bool compress();
        void reverse();
        void transpose();
        bool moveLeft();
        bool moveRight();
        bool moveUp();
        bool moveDown();
        void addRandomTile();
        bool canMove();
        void updateScore(int points);

    public:
        explicit Game2048(QWidget *parent = nullptr);
        void newGame();

    protected:
        void keyPressEvent(QKeyEvent *event) override;

};

#endif