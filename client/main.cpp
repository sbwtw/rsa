
#include "clientwindow.h"
#include "bignumber.h"

#include <QApplication>
#include <QDebug>

void bigNumber_test()
{
    BigNumber n1, n2;

    n1 = 1025;
    n2 = "1025";

    BigNumber n3 = n1 + n2;

    Q_ASSERT(n3 > n2);
    Q_ASSERT(n3 > n1);
    Q_ASSERT(n2 == n1);

    n1 = "36";
    n2 = 96;
    Q_ASSERT(n1 * n2 == "3456");
    Q_ASSERT(n1 * n2 == n2 * n1);

    n1 = 123456789;
    n2 = 321654987;
    Q_ASSERT(n1 * n2 == "39710491860856743");
    Q_ASSERT(n1 * n2 == n2 * n1);

    qDebug() << "Test finished.";
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    bigNumber_test();

//    ClientWindow cw;
//    cw.show();

    return app.exec();
}
