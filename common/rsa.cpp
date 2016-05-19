#include "rsa.h"

#include <iostream>

RSA::RSA()
{

}

const BigNumber RSA::gcd(const BigNumber &a, const BigNumber &b)
{
    return a == "0" ? gcd(b % a, a) : b;
}

const BigNumber RSA::power(const BigNumber &number, const int power)
{
    BigNumber result;
    result = number;

    for (int i(1); i != power; ++i)
        result *= number;

    return result;
}

const BigNumber RSA::fastPowerMod(const BigNumber &a, const BigNumber &b, const BigNumber &c)
{
    BigNumber ret, tmp, magic, const_num_2;
    ret = 1;
    tmp = a;
    magic = b;
    const_num_2 = 2;

    while (!magic.isZero())
    {
        if (magic.isOdd())
        {
            ret *= tmp;
            ret %= c;
        }
        tmp = tmp * tmp % c;

        magic /= const_num_2;
    }

    return ret;
}

void RSA::gcdEx(const BigNumber &a, const BigNumber &b, BigNumber &x, BigNumber &y)
{
    if (b == "0")
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
//    m_key_e = 17; //65537;
    m_key_e = 65537; //65537;

    BigNumber a, b, x, y, zero;
    zero = 0;
    a = m_key_e;
    b = m_key_fn;
    gcdEx(a, b, x, y);

    if (x < zero)
        x = b - (-x);

    m_key_d = x;
}

void RSA::dumpInfo() const
{
    std::cerr << "m_key_p: " << m_key_p << std::endl;
    std::cerr << "m_key_q: " << m_key_q << std::endl;
    std::cerr << "m_key_n: " << m_key_n << std::endl;
    std::cerr << "m_key_fn: " << m_key_fn << std::endl;
    std::cerr << "m_key_e: " << m_key_e << std::endl;
    std::cerr << "m_key_d: " << m_key_d << std::endl << std::endl;
}

bool RSA::test_key_d(const BigNumber &key_d) const
{
    return m_key_d == key_d;
}

BigNumber RSA::encode(const BigNumber &num) const
{
    return fastPowerMod(num, m_key_e, m_key_n);
}

BigNumber RSA::decode(const BigNumber &num) const
{
    return fastPowerMod(num, m_key_d, m_key_n);
}
