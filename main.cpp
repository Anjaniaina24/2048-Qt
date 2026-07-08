#include "Menu.hpp"

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    QFile file("style.qss");
    if(file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
    }

    Menu menu;
    menu.show();

    return app.exec();
}