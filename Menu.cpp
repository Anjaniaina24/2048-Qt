#include "Menu.hpp"

Menu::Menu(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(390, 570);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Menu
    menuWidget = new QWidget(this);
    menuWidget->setObjectName("menuWidget");
    QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);
    menuLayout->setAlignment(Qt::AlignCenter);
    menuLayout->setSpacing(30);

    titleLabel = new QLabel("2048", menuWidget);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);

    QPushButton *playButton = new QPushButton("Jouer", menuWidget);
    playButton->setObjectName("playButton");
    playButton->setFixedSize(220, 60);

    QPushButton *quitButton = new QPushButton("Quitter", menuWidget);
    quitButton->setObjectName("quitButton");
    quitButton->setFixedSize(220, 60);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 80));
    playButton->setGraphicsEffect(shadow);
    quitButton->setGraphicsEffect(shadow);

    menuLayout->addWidget(titleLabel);
    menuLayout->addWidget(playButton);
    menuLayout->addWidget(quitButton);

    // Jeu
    gameWidget = new Game2048(this);
    connect(gameWidget, &Game2048::goToMenu, this, &Menu::onGoToMenu);

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

void Menu::onGoToMenu()
{
    stackedWidget->setCurrentWidget(menuWidget);
    // gameWidget->newGame(); // optionnel
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

    connect(group, &QParallelAnimationGroup::finished, this, [this]() {
        stackedWidget->setCurrentWidget(gameWidget);
        menuWidget->move(0, 0);
        gameWidget->move(0, 0);
        gameWidget->setFocus();   // <--- FORCER LE FOCUS POUR LES TOUCHES
    });
    group->start(QAbstractAnimation::DeleteWhenStopped);
}