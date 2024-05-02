#include <iostream>
using namespace std;

int getNumDigits(long num)
{
    return num > 0 ? (int)log10((double)num) + 1 : 1;
}

long karatsuba(long x, long y)
{
    if (x < 10 || y < 10)
    {
        return x * y;
    }

    int numDigits = max(getNumDigits(x), getNumDigits(y));
    int halfNumDigits = (numDigits + 1) / 2;

    long a = x / (long)pow(10, halfNumDigits);
    long b = x % (long)pow(10, halfNumDigits);
    long c = y / (long)pow(10, halfNumDigits);
    long d = y % (long)pow(10, halfNumDigits);

    long ac = karatsuba(a, c);
    long bd = karatsuba(b, d);
    long ad_bc = karatsuba(a + b, c + d) - ac - bd;

    return ac * ( long)pow(10, 2 * halfNumDigits) + ad_bc * ( long)pow(10, halfNumDigits) + bd;
}

int main()
{
    long x = 146123;
    long y = 352120;

    long result = karatsuba(x, y);

    cout << "Product of " << x << " and " << y << " : " << result << endl;

    return 0;
}
