#ifndef MENU_HPP
#define MENU_HPP

#include "Game2048.hpp"
#include <QPushButton>
#include <QPropertyAnimation>
#include <QApplication>
#include <QStackedWidget>
#include <QMainWindow>
#include <QParallelAnimationGroup>

class Menu : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Menu(QWidget *parent = nullptr);
    
    private:
        QStackedWidget *stackedWidget;
        QWidget *menuWidget;
        Game2048 *gameWidget;
        void animateToGame();
        void setupMenu();

    private slots:
        void onPlayClicked();
        void onQuitClicked();

};

#endif