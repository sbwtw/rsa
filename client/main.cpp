
#include "clientwindow.h"
#include "bignumber.h"
#include "rsa.h"

#include <iostream>

#include <QApplication>

void bigNumber_test()
{
    BigNumber n1, n2;

    n1 = 1025;
    n2 = "1025";

    BigNumber n3 = n1 + n2;

    Q_ASSERT(n3 > n2);
    Q_ASSERT(n3 > n1);
    Q_ASSERT(n2 == n1);
    Q_ASSERT(-n2 == -n1);
    Q_ASSERT(-n2 == "-1025");
    Q_ASSERT(n1 - n2 == "0");

    n1 = 123456789;
    n2 = 321654987;
    Q_ASSERT(n1 * n2 == "39710491860856743");
    Q_ASSERT(n1 * n2 == n2 * n1);

    n1 = -3;
    n2 = 5;
    Q_ASSERT(n1 * n2 == "-15");

    n1 = 123;
    n2 = 156;
    Q_ASSERT(n2 - n1 == "33");
    Q_ASSERT(n1 - n2 == "-33");

    n1 = 17;
    n2 = 5;
    Q_ASSERT(n1 % n2 == "2");
    n1 = 150;
    n2 = 50;
    Q_ASSERT(n1 % n2 == "0");

    n1 = 10;
    Q_ASSERT((n1 += 1) == "11");

    n1 = 10;
    n2 = 5;
    Q_ASSERT((n1 / n2) == "2");

    n1 = 10;
    n2 = 3;
    Q_ASSERT((n1 / n2) == "3");

    n1 = 10;
    n2 = 30;
    Q_ASSERT((n1 / n2) == "0");

    // RSA-768
    n1 = "33478071698956898786044169848212690817704794983713768568912431388982883793878002287614711652531743087737814467999489";
    n2 = "36746043666799590428244633799627952632279158164343087642676032283815739666511279233373417143396810270092798736308917";
    Q_ASSERT(n1 * n2 == "123018668453011775513049495838496272077285356959533479219732245215172640050726"
                        "365751874520219978646938995647494277406384592519255732630345373154826850791702"
                        "6122142913461670429214311602221240479274737794080665351419597459856902143413");

    qDebug() << "Test finished.";
}

void rsa_test()
{
    BigNumber n1, n2, key;
    n1 = 61;
    n2 = 53;
    key = 2753;

    RSA rsa;
    rsa.setPublicKey(n1, n2);

    Q_ASSERT(rsa.test_key_d(key));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    rsa_test();
    bigNumber_test();

//    ClientWindow cw;
//    cw.show();

    return app.exec();
}
