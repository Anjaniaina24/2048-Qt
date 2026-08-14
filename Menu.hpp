#ifndef MENU_HPP
#define MENU_HPP

#include "Game2048.hpp"
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QApplication>
#include <QStackedWidget>
#include <QMainWindow>
#include <QParallelAnimationGroup>
#include <QGraphicsDropShadowEffect>

class Menu : public QMainWindow
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);

private:
    QStackedWidget *stackedWidget;
    QWidget *menuWidget;
    Game2048 *gameWidget;
    QLabel *titleLabel;      
    void animateToGame();

private slots:
    void onPlayClicked();
    void onQuitClicked();
};

#endif