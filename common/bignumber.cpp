#include "bignumber.h"

BigNumber::BigNumber() :
    m_positive(true),
    m_data()
{

}

BigNumber BigNumber::operator=(const int number)
{
    m_data.clear();

    int N = number;
    while (N)
    {
        m_data.push_back(N % 10);
        N /= 10;
    }

    return *this;
}

BigNumber BigNumber::operator=(const string &number)
{
    m_data.clear();

    while (true)
    {
        for (int i : number)
        {
            if (!isalnum(i))
                break;

            m_data.insert(m_data.begin(), i - '0');
        }

        return *this;
    }

    // parse fail
    m_data.clear();
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

BigNumber BigNumber::operator*(const BigNumber &what) const
{
    BigNumber number = *this;

    return number *= what;
}

BigNumber BigNumber::operator*=(const BigNumber &what)
{
    const BigNumber number = *this;
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
    adjust();

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
            continue;

        if (m_positive && m_data[i] < what.m_data[i])
            return false;
        if (!m_positive && m_data[i] > what.m_data[i])
            return false;

        break;
    }

    if (*this == what)
        return false;

    return true;
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

bool BigNumber::operator==(const string &what) const
{
    BigNumber number;
    number = what;

    return *this == number;
}

void BigNumber::adjust()
{
    const int lenMine = m_data.size();

    for (int i(0); i != lenMine - 1; ++i)
    {
        m_data[i + 1] += m_data[i] / 10;
        m_data[i] %= 10;
    }

    while (m_data[m_data.size() - 1] > 10)
    {
        m_data.push_back(m_data[m_data.size() - 1] / 10);
        m_data[m_data.size() - 2] %= 10;
    }
}

QDebug operator<<(QDebug debug, const BigNumber &number)
{
    if (!number.m_positive)
        debug << '-';

    for (auto i(number.m_data.rbegin()); i != number.m_data.rend(); ++i)
        debug << *i;

    return debug;
}
