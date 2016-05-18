#include "rsa.h"

#include <iostream>

RSA::RSA()
{

}

const BigNumber RSA::gcd(const BigNumber &a, const BigNumber &b)
{
    return a == "0" ? gcd(b % a, a) : b;
}

void RSA::gcdEx(const BigNumber &a, const BigNumber &b, BigNumber &x, BigNumber &y)
{
    if (b == "0" || b == "-0")
    {
        x = 1;
        y = 0;
    } else {
        gcdEx(b, a % b, x, y);
        BigNumber t = x;
        x = y;
        y = t - ((a / b) * x);

//        gcdEx(b, a % b, y, x);
//        y -= a / b * x;
    }
}

void RSA::setPublicKey(const BigNumber &p, const BigNumber &q)
{
    m_key_p = p;
    m_key_q = q;

    m_key_n = m_key_p * m_key_q;
    m_key_fn = (m_key_p - 1) * (m_key_q - 1);
    m_key_e = 65537;

    BigNumber a, b, x, y, zero;
    zero = 0;
    a = m_key_e;
    b = m_key_fn;
    gcdEx(a, b, x, y);

    if (x < zero)
        x = b - (-x);

    m_key_d = x;
}

bool RSA::test_key_d(const BigNumber &key_d) const
{
    return m_key_d == key_d;
}
