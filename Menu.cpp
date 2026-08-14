#include "Menu.hpp"

Menu::Menu(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(390, 500);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // --- Widget du menu ---
    menuWidget = new QWidget(this);
    menuWidget->setObjectName("menuWidget"); // pour le style QSS

    QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);
    menuLayout->setAlignment(Qt::AlignCenter);
    menuLayout->setSpacing(30);

    // Titre "2048"
    titleLabel = new QLabel("2048", menuWidget);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);

    // Bouton Jouer
    QPushButton *playButton = new QPushButton("Jouer", menuWidget);
    playButton->setObjectName("playButton");
    playButton->setFixedSize(220, 60);

    // Bouton Quitter
    QPushButton *quitButton = new QPushButton("Quitter", menuWidget);
    quitButton->setObjectName("quitButton");
    quitButton->setFixedSize(220, 60);

    // Ajout d'une ombre portée sur les boutons (effet moderne)
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 80));
    playButton->setGraphicsEffect(shadow);
    quitButton->setGraphicsEffect(shadow);

    menuLayout->addWidget(titleLabel);
    menuLayout->addWidget(playButton);
    menuLayout->addWidget(quitButton);

    // --- Widget du jeu ---
    gameWidget = new Game2048(this);

    stackedWidget->addWidget(menuWidget);
    stackedWidget->addWidget(gameWidget);

    // Connexions
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

    connect(group, &QParallelAnimationGroup::finished, this, [this]() {
        stackedWidget->setCurrentWidget(gameWidget);
        menuWidget->move(0, 0);
        gameWidget->move(0, 0);
    });
    group->start(QAbstractAnimation::DeleteWhenStopped);
}