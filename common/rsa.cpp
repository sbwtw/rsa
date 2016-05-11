#include "rsa.h"

RSA::RSA()
{

}

const BigNumber RSA::gcd(const BigNumber &a, const BigNumber &b)
{
    return a == "0" ? gcd(b % a, a) : b;
}

void RSA::gcdEx(const BigNumber &a, const BigNumber &b, BigNumber &x, BigNumber &y)
{
    if (b == "0")
    {
        x = 1;
        y = 0;
    } else {
        gcdEx(b, a % b, y, x);
        y -= a / b * x;
    }
}

void RSA::setPublicKey(const BigNumber &p, const BigNumber &q)
{
    m_key_p = p;
    m_key_q = q;

    m_key_n = m_key_p * m_key_q;
    m_key_fn = (m_key_p - 1) * (m_key_q - 1);
    m_key_e = 17;//65537;

    BigNumber a = m_key_e, b = m_key_fn, x, y;
    gcdEx(a, b, x, y);
}
