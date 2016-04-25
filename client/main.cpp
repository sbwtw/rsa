
#include "clientwindow.h"
#include "bignumber.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BigNumber n1, n2;

    n1 = 1025;
    n2 = "15156454565467895687";

    BigNumber n3 = n1 + n2;

    qDebug() << n1;
    qDebug() << n2;
    qDebug() << n3;

//    ClientWindow cw;
//    cw.show();

    return app.exec();
}
