#ifndef RSA_H
#define RSA_H

class RSA
{
public:
    RSA();

    static int gcd(const int a, const int b);
    static void gcdEx(const int a, const int b, int &x, int &y);
};

#endif // RSA_H
