#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w;
    QLabel("gef");
    w.show();
    return a.exec();
}
