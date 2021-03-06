
#include "bignumber.h"

#include <QtCore>

using namespace std;

BigNumber::BigNumber() :
    m_positive(true),
    m_data()
{

}

BigNumber BigNumber::operator=(const int number)
{
    m_data.clear();
    m_positive = number >= 0;

    int N = std::abs(number);
    while (N)
    {
        m_data.push_back(N % 10);
        N /= 10;
    }

    if (!m_data.size())
        clear();

    return *this;
}

BigNumber BigNumber::operator=(const string &number)
{
    m_data.clear();

    while (true)
    {
        if (number.empty())
        {
            m_positive = true;
            return *this;
        }

        size_t index(0);
        if (number[index] == '-')
        {
            m_positive = false;
            ++index;
        }

        while (index != number.size())
        {
            if (!isalnum(number[index]))
                break;

            m_data.insert(m_data.begin(), number[index] - '0');
            ++index;
        }

        return *this;
    }

    // parse fail
    clear();
    return *this;
}

BigNumber BigNumber::operator+(const BigNumber &what) const
{
    BigNumber number = *this;

    return number += what;
}

BigNumber BigNumber::operator+=(const BigNumber &what)
{
    if (what.m_data.empty()) {
        return *this;
    } else if (m_data.empty()) {
        m_data = what.m_data;
        return *this;
    }

    const int lenMine = m_data.size();
    const int lenWhat = what.m_data.size();
    const int lenMin = std::min(lenMine, lenWhat);

    for (int i(0); i != lenMin; ++i)
        m_data[i] += what.m_data[i];

    if (lenWhat > lenMine)
    {
        for (int i(lenMine); i != lenWhat; ++i)
            m_data.push_back(what.m_data[i]);
    }

    adjust();

    return *this;
}

BigNumber BigNumber::operator+=(const int what)
{
    Q_ASSERT(m_data.size());

    m_data.front() += what;

    adjust();

    return *this;
}

BigNumber BigNumber::operator-() const
{
    BigNumber number = *this;

    number.m_positive = !m_positive;

    return number;
}

BigNumber BigNumber::operator-(const BigNumber &what) const
{
    BigNumber number = *this;

    return number -= what;
}

BigNumber BigNumber::operator-(const int what) const
{
    BigNumber number = *this;
    BigNumber w;

    w = what;

    return number - w;
}

BigNumber BigNumber::operator-=(const BigNumber &what)
{
    if (*this == what)
    {
        *this = 0;
        m_positive = true;
        return *this;
    }

    // two positive number
    if (m_positive && what.m_positive)
    {
        if (*this > what)
        {
            for (size_t i(0); i != what.m_data.size(); ++i)
                m_data[i] -= what.m_data[i];
        } else {
            return -(what - *this);
        }
    // two inpositive number
    } else if (!m_positive && !what.m_positive) {
        return -((-*this) + (-what));
    // one positive and another inpositive
    } else {
        if (m_positive)
            return *this + (-what);
        else
            return -((-*this) + what);
    }

    adjust();

    return *this;
}

BigNumber BigNumber::operator*(const BigNumber &what) const
{
    BigNumber number = *this;

    return number *= what;
}

BigNumber BigNumber::operator*=(const BigNumber &what)
{
    const bool resultPositive = !(m_positive ^ what.m_positive);
    const BigNumber number = m_positive ? *this : -*this;

    m_data.clear();

    for (size_t i(0); i != what.m_data.size(); ++i)
    {
        BigNumber tmpNumber = number;

        for (size_t k(0); k != tmpNumber.m_data.size(); ++k)
            tmpNumber.m_data[k] *= what.m_data[i];

        for (size_t k(0); k != i; ++k)
            tmpNumber.m_data.insert(tmpNumber.m_data.begin(), 0);

        *this += tmpNumber;
    }

    m_positive = resultPositive;
    adjust();

    return *this;
}

BigNumber BigNumber::operator/(const BigNumber &what) const
{
    BigNumber number = *this;

    return number /= what;
}

BigNumber BigNumber::operator/=(const BigNumber &what)
{
    BigNumber number, magic, extend;
    number = 0;

    if (*this < what)
    {
        *this = 0;
        return *this;
    }
    if (*this == what)
    {
        *this = 1;
        return *this;
    }

    magic = what;
    int flag = 1;
    extend = 1;

    while (magic == *this || magic < *this)
    {
        magic.m_data.insert(magic.m_data.begin(), 0);
        extend.m_data.insert(extend.m_data.begin(), 0);
        ++flag;
    }

    while (--flag)
    {
        magic.m_data.erase(magic.m_data.begin());
        extend.m_data.erase(extend.m_data.begin());

        // start
        while (*this == magic || *this > magic)
        {
            *this -= magic;
            number += extend;
        }
    }

    *this = number;

    return *this;
}

BigNumber BigNumber::operator%(const BigNumber &what) const
{
    BigNumber number = *this;

    return number %= what;
}

BigNumber BigNumber::operator%=(const BigNumber &what)
{
    BigNumber magic;
    magic = what;
    int flag = 1;

    while (*this > magic || *this == magic)
    {
        magic.m_data.insert(magic.m_data.begin(), 0);
        ++flag;
    }

    while (--flag)
    {
        magic.m_data.erase(magic.m_data.begin());

        while (*this == magic || *this > magic)
        {
            *this -= magic;
        }
    }

    return *this;
}

bool BigNumber::operator>(const BigNumber &what) const
{
    if (m_positive != what.m_positive)
        return m_positive;

    if (m_data.size() != what.m_data.size())
        return m_positive ? m_data.size() > what.m_data.size()
                          : m_data.size() < what.m_data.size();

    for (int i(m_data.size() - 1); i != -1; --i)
    {
        if (m_data[i] == what.m_data[i])
        {
            if (i)
                continue;
            else
                return false;
        }

        if (m_positive && m_data[i] < what.m_data[i])
            return false;
        if (!m_positive && m_data[i] > what.m_data[i])
            return false;

        break;
    }

    return true;
}

bool BigNumber::operator>=(const BigNumber &what) const
{
    return *this == what || *this > what;
}

bool BigNumber::operator<(const BigNumber &what) const
{
    return !(*this >= what);
}

bool BigNumber::operator==(const BigNumber &what) const
{
    if (m_positive != what.m_positive)
        return false;

    if (m_data.size() != what.m_data.size())
        return false;

    for (size_t i(0); i != m_data.size(); ++i)
        if (m_data[i] != what.m_data[i])
            return false;

    return true;
}

bool BigNumber::operator!=(const BigNumber &what) const
{
    return !(*this == what);
}

bool BigNumber::operator==(const string &what) const
{
    BigNumber number;
    number = what;

    return *this == number;
}

bool BigNumber::isOdd() const
{
    return m_data.front() & 0x1;
}

bool BigNumber::isZero() const
{
    return m_data.size() == 1 && m_data.front() == 0;
}

const string BigNumber::toStdString() const
{
    string str;
    if (!m_positive)
        str.push_back('-');

    for (auto i(m_data.rbegin()); i != m_data.rend(); ++i)
        str.push_back(*i + '0');

    return str;
}

void BigNumber::adjust()
{
    if (m_data.empty())
        m_data.push_back(0);

    if (m_data.size() == 1 && m_data[0] == 0)
    {
        m_positive = true;
        return;
    }

    for (size_t i(0); i != m_data.size(); ++i)
    {
        while (m_data[i] < 0)
        {
            m_data[i] += 10;
            m_data[i + 1] -= 1;
        }
    }

    while (m_data.size() > 1 && m_data.back() == 0)
        m_data.pop_back();

    const int lenMine = m_data.size();

    for (int i(0); i != lenMine - 1; ++i)
    {
        m_data[i + 1] += m_data[i] / 10;
        m_data[i] %= 10;
    }

    while (m_data.back() > 10)
    {
        m_data.push_back(m_data.back() / 10);
        m_data[m_data.size() - 2] %= 10;
    }
}

void BigNumber::clear()
{
    m_data.clear();
    m_data.push_back(0);
}

ostream& operator<<(ostream &out, const BigNumber &number)
{
    if (!number.m_positive)
        out << '-';

    for (auto i(number.m_data.rbegin()); i != number.m_data.rend(); ++i)
        out << *i;

    return out;
}
