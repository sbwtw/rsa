#ifndef RSA_H
#define RSA_H

#include "bignumber.h"

class RSA
{
public:
    RSA();

    static const BigNumber gcd(const BigNumber &a, const BigNumber &b);
    static void gcdEx(const BigNumber &a, const BigNumber &b, BigNumber &x, BigNumber &y);

    void setPublicKey(const BigNumber &p, const BigNumber &q);

private:
    BigNumber m_key_p;
    BigNumber m_key_q;
    BigNumber m_key_n;
    BigNumber m_key_fn;
    BigNumber m_key_e;
    BigNumber m_key_d;
};

#endif // RSA_H
