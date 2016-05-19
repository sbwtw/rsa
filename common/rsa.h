#ifndef RSA_H
#define RSA_H

#include "bignumber.h"

class RSA
{
public:
    RSA();

    static const BigNumber gcd(const BigNumber &a, const BigNumber &b);
    static const BigNumber power(const BigNumber &number, const int power);
    static const BigNumber fastPowerMod(const BigNumber &a, const BigNumber &b, const BigNumber &c);
    static void gcdEx(const BigNumber &a, const BigNumber &b, BigNumber &x, BigNumber &y);

    void setPublicKey(const BigNumber &p, const BigNumber &q);
    void dumpInfo() const;
    bool test_key_d(const BigNumber &key_d) const;

    BigNumber encode(const BigNumber &num) const;
    BigNumber decode(const BigNumber &num) const;

private:
    BigNumber m_key_p;
    BigNumber m_key_q;
    BigNumber m_key_n;
    BigNumber m_key_fn;
    BigNumber m_key_e;
    BigNumber m_key_d;
};

#endif // RSA_H
