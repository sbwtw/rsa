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
    BigNumber operator*(const BigNumber &what) const;
    BigNumber operator*=(const BigNumber &what);
    bool operator>(const BigNumber &what) const;
    bool operator==(const BigNumber &what) const;
    bool operator==(const string &what) const;

    friend QDebug operator<<(QDebug debug, const BigNumber &number);

private:
    void adjust();

private:
    bool m_positive = true;
    vector<int> m_data;
};

#endif // BIGNUMBER_H
