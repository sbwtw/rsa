#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <list>
#include <QDebug>
#include <string>

using namespace std;

class BigNumber
{
public:
    BigNumber();

    BigNumber operator=(const int number);
    BigNumber operator=(const string &number);
    BigNumber operator+(const BigNumber &what) const;
    BigNumber operator+=(const BigNumber &what);
    BigNumber operator-=(const BigNumber &what);
    bool operator>(const BigNumber &what);

    friend QDebug operator<<(QDebug debug, const BigNumber &number);

private:
    void adjust();

private:
    bool m_positive;
    vector<int> m_data;
};

#endif // BIGNUMBER_H
