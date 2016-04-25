
#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Server s;

    return app.exec();
}
