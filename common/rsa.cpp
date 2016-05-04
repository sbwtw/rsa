#include "rsa.h"

RSA::RSA()
{

}

int RSA::gcd(const int a, const int b)
{
    return a ? gcd(b % a, a) : b;
}

void RSA::gcdEx(const int a, const int b, int &x, int &y)
{
    if (b)
    {
        gcdEx(b, a % b, y, x);
        y -= int(a / b) * x;
    } else {
        x = 1;
        y = 0;
    }
}
