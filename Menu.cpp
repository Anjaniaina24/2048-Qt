#include "Menu.hpp"

Menu::Menu(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(390, 500);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    menuWidget = new QWidget(this);
    QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);
    menuLayout->setAlignment(Qt::AlignCenter);
    menuLayout->setSpacing(20);


    QPushButton *playButton = new QPushButton("Jouer", menuWidget);
    playButton->setFixedSize(200, 50);

    QPushButton *quitButton = new QPushButton("Quitter",  menuWidget);
    quitButton->setFixedSize(200, 50);

    menuLayout->addWidget(playButton);
    menuLayout->addWidget(quitButton);

    gameWidget = new Game2048(this);

    stackedWidget->addWidget(menuWidget);
    stackedWidget->addWidget(gameWidget);

    connect(playButton, &QPushButton::clicked, this, &Menu::onPlayClicked);
    connect(quitButton, &QPushButton::clicked, this, &Menu::onQuitClicked);
}

void Menu::onPlayClicked()
{
    animateToGame();
}

void Menu::onQuitClicked()
{
    QApplication::quit();
}

void Menu::animateToGame()
{
    int height = stackedWidget->height();

    menuWidget->move(0, 0);
    gameWidget->move(0, height);
    
    QPropertyAnimation *animMenu = new QPropertyAnimation(menuWidget, "pos");
    animMenu->setDuration(500);
    animMenu->setStartValue(menuWidget->pos());
    animMenu->setEndValue(QPoint(0, -height));

    QPropertyAnimation *animGame = new QPropertyAnimation(gameWidget, "pos");
    animGame->setDuration(500);
    animGame->setStartValue(gameWidget->pos());
    animGame->setEndValue(QPoint(0, 0));

    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    group->addAnimation(animMenu);
    group->addAnimation(animGame);

    connect(group, &QParallelAnimationGroup::finished, this, [this]() 
        {
            stackedWidget->setCurrentWidget(gameWidget);
            menuWidget->move(0, 0);
            gameWidget->move(0, 0);
        }
    );
    group->start(QAbstractAnimation::DeleteWhenStopped);
}