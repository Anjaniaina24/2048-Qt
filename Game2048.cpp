#include "Game2048.hpp"

Game2048::Game2048(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("2048");
    setFixedSize(390, 500);
    board.resize(4);
    prevBoard.resize(4);
    for(int i = 0; i < 4; i++)
    {
        board[i].resize(4);
        prevBoard[i].resize(4);
    }
    getData();
    initBoard();
    newGame();
}

bool Game2048::vide()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(board[i][j] != 0)
            {
                return false;
            }
        }
    }
    return true;
}

void Game2048::setData()
{
    std::ofstream file("Sauvegarde.txt");
    if(file)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                file << board[i][j] << " ";
            }
            file << std::endl;
        }
    }
    file.close();
    std::ofstream file1("Score.txt");
    if(file1)
    {
        file1 << score;
    }
    file1.close();
}

void Game2048::getData()
{
    std::ifstream file("Sauvegarde.txt");
    if(file)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                file >> board[i][j];
            }
        }
    }
    file.close();
    std::ifstream file1("Score.txt");
    if(file1)
    {
        file1 >> score;
    }
    file1.close();
}

void Game2048::setBestScore()
{
    std::ofstream file("BestScore.txt");
    if(file)
    {
        file << score;
    }
    file.close();
}

void Game2048::getBestScore()
{
    std::ifstream file("BestScore.txt");
    if(file)
    {
        file >> bestScore;
    }
    file.close();
}

void Game2048::initBoard()
{
    setObjectName("game");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    // Score
    QWidget *scoreWidget = new QWidget(this);
    QHBoxLayout *scoreLayout = new QHBoxLayout(scoreWidget);
    scoreLayout->setContentsMargins(10, 10, 10, 10);
    scoreLayout->setSpacing(10);

    scoreLabel = new QLabel("Score\n0", this);
    scoreLabel->setText(QString("Score\n%1").arg(score));
    scoreLabel->setFixedSize(170, 70);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setObjectName("scoreLabel");
    scoreLayout->addWidget(scoreLabel);

    bestScoreLabel = new QLabel("Best Score\n0", this);
    getBestScore();
    bestScoreLabel->setText(QString("Best Score\n%1").arg(bestScore));
    bestScoreLabel->setFixedSize(170, 70);
    bestScoreLabel->setAlignment(Qt::AlignCenter);
    bestScoreLabel->setObjectName("bestScoreLabel");
    scoreLayout->addWidget(bestScoreLabel);

    mainLayout->addWidget(scoreWidget);

    // Grille
    QWidget *gridWidget = new QWidget(this);
    gridWidget->setFixedSize(370, 370);
    gridWidget->setObjectName("gridWidget");
    gridLayout = new QGridLayout(gridWidget);
    gridLayout->setSpacing(tileSpacing);
    gridLayout->setContentsMargins(tileSpacing, tileSpacing, tileSpacing, tileSpacing);

    tiles.resize(4);
    for (int i = 0; i < 4; ++i) {
        tiles[i].resize(4);
        for (int j = 0; j < 4; ++j) {
            QLabel *label = new QLabel(gridWidget);
            label->setFixedSize(tileSize, tileSize);
            label->setAlignment(Qt::AlignCenter);
            label->setObjectName("case");
            gridLayout->addWidget(label, i, j);
            tiles[i][j] = label;
        }
    }

    mainLayout->addWidget(gridWidget);
}

void Game2048::newGame()
{
    updateScore(0);

    for (auto &row : board)
        std::fill(row.begin(), row.end(), 0);

    getData();

    if (!canMove()) {
        qDebug() << "Game Over!";
        board = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
        score = 0;
        setData();
        addRandomTile();
        addRandomTile();
        updateBoard();
    }

    if(vide())
    {
        addRandomTile();
        addRandomTile();
    }
   
    updateBoard();
}

void Game2048::updateScore(int points)
{
    score += points;
    if(score > bestScore)
    {
        bestScore = score;
        setBestScore();
    }
    scoreLabel->setText(QString("Score\n%1").arg(score));
    bestScoreLabel->setText(QString("Best Score\n%1").arg(bestScore));
}

void Game2048::addRandomTile()
{
    QVector<QPair<int,int>> emptyCells;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (board[i][j] == 0)
                emptyCells.append({i,j});

    if (emptyCells.isEmpty())
        return;

    int idx = QRandomGenerator::global()->bounded(emptyCells.size());
    board[emptyCells[idx].first][emptyCells[idx].second] = (QRandomGenerator::global()->bounded(10) < 9) ? 2 : 4;
}

void Game2048::updateBoard()
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int val = board[i][j];
            QLabel *label = tiles[i][j];
            if (val == 0) {
                label->setText("");
                label->setStyleSheet(QString("background: #838B8F; border-radius: 10px; font: bold 24px; color: white;"));
            } else {
                label->setText(QString::number(val));
                QString color;
                switch (val) {
                    case 2: color = "#C183CD"; break;
                    case 4: color = "#E02678"; break;
                    case 8: color = "#FFFF00"; break;
                    case 16: color = "#37F171"; break;
                    case 32: color = "#25D6E3"; break;
                    case 64: color = "#D72E89"; break;
                    case 128: color = "#ECAD39"; break;
                    case 256: color = "#39FFED"; break;
                    case 512: color = "#3241CB"; break;
                    case 1024: color = "#F71B1B"; break;
                    case 2048: color = "#723D8D"; break;
                    default: color = "#000000"; break;
                }
                label->setStyleSheet(QString("background: %1; border-radius: 10px; font: bold 24px; color: white;").arg(color));
            }
        }
    }
}

bool Game2048::canMove()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (board[i][j] == 0)
                return true;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == board[i][j+1])
                return true;

    for (int j = 0; j < 4; ++j)
        for (int i = 0; i < 3; ++i)
            if (board[i][j] == board[i+1][j])
                return true;

    return false;
}

void Game2048::keyPressEvent(QKeyEvent *event)
{
    bool moved = false;

    switch (event->key()) {
    case Qt::Key_Left:
        moved = moveLeft();
        break;
    case Qt::Key_Right:
        moved = moveRight();
        break;
    case Qt::Key_Up:
        moved = moveUp();
        break;
    case Qt::Key_Down:
        moved = moveDown();
        break;
    default:
        QWidget::keyPressEvent(event);
        return;
    }

    if (moved) {
        addRandomTile();
        updateBoard();
        setData();

        if (!canMove()) {
            qDebug() << "Game Over!";
            board = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
            score = 0;
            setData();
            addRandomTile();
            addRandomTile();
            updateBoard();
        }
    }
}

bool Game2048::compress()
{
    bool moved = false;
    for (int i = 0; i < 4; ++i) {
        QVector<int> newRow(4, 0);
        int pos = 0;

        for (int j = 0; j < 4; ++j) {
            if (board[i][j] != 0)
                newRow[pos++] = board[i][j];
        }

        for (int j = 0; j < 3; ++j) {
            if (newRow[j] != 0 && newRow[j] == newRow[j+1]) {
                newRow[j] *= 2;
                updateScore(newRow[j]);
                newRow[j+1] = 0;
                moved = true;
            }
        }

        QVector<int> finalRow(4, 0);
        pos = 0;
        for (int j = 0; j < 4; ++j) {
            if (newRow[j] != 0)
                finalRow[pos++] = newRow[j];
        }

        if (board[i] != finalRow) {
            board[i] = finalRow;
            moved = true;
        }
    }
    return moved;
}

void Game2048::reverse()
{
    for (auto &row : board)
        std::reverse(row.begin(), row.end());
}

void Game2048::transpose()
{
    QVector<QVector<int>> transposed(4, QVector<int>(4));
    for (int i=0; i<4; ++i)
        for (int j=0; j<4; ++j)
            transposed[i][j] = board[j][i];
    board = transposed;
}

bool Game2048::moveLeft()
{
    bool moved = false;
    moved = compress();
    return moved;
}

bool Game2048::moveRight()
{
    bool moved = false;
    reverse();
    moved = compress();
    reverse();
    return moved;
}

bool Game2048::moveUp()
{
    bool moved = false;
    transpose();
    moved = compress();
    transpose();
    return moved;
}

bool Game2048::moveDown()
{
    bool moved = false;
    transpose();
    reverse();
    moved = compress();
    reverse();
    transpose();
    return moved;
}