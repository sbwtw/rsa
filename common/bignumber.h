#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <vector>
#include <string>
#include <ostream>

class BigNumber
{
public:
    BigNumber();

    BigNumber operator=(const int number);
    BigNumber operator=(const std::string &number);
    BigNumber operator+(const BigNumber &what) const;
    BigNumber operator+=(const BigNumber &what);
    BigNumber operator+=(const int what);
    BigNumber operator-() const;
    BigNumber operator-(const BigNumber &what) const;
    BigNumber operator-(const int what) const;
    BigNumber operator-=(const BigNumber &what);
    BigNumber operator*(const BigNumber &what) const;
    BigNumber operator*=(const BigNumber &what);
    BigNumber operator/(const BigNumber &what) const;
    BigNumber operator/=(const BigNumber &what);
    BigNumber operator%(const BigNumber &what) const;
    BigNumber operator%=(const BigNumber &what);
    bool operator>(const BigNumber &what) const;
    bool operator>=(const BigNumber &what) const;
    bool operator<(const BigNumber &what) const;
    bool operator==(const BigNumber &what) const;
    bool operator!=(const BigNumber &what) const;
    bool operator==(const std::string &what) const;

    bool isOdd() const;
    bool isZero() const;

    friend std::ostream& operator<<(std::ostream &out, const BigNumber &number);

    const std::string toStdString() const;

private:
    void adjust();
    void clear();

private:
    bool m_positive = true;
    std::vector<int> m_data;
};

#endif // BIGNUMBER_H
