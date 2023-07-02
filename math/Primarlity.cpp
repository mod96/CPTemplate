typedef unsigned long long lld;

lld testSets[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

lld power(lld x, lld y, lld p)
{ // x ^ y mod p
    lld res = 1;
    x %= p;
    while (y > 0)
    {
        if (y & 1)
        {
            res = (res * x) % p;
            y--;
        }
        x = (x * x) % p;
        y >>= 1;
    }
    return res;
}

bool millerRabinHelper(lld n, lld d, lld a)
{
    lld x = power(a, d, n);
    if (x == 1 || x == n - 1)
        return true; // then squaring always gives 1 mod n
    while (d != n - 1)
    {
        x = (x * x) % n;
        d <<= 1;
        if (x == 1)
            return false; // then, x = 1 or x = n - 1 must had happened before
        if (x == n - 1)
            return true; // ok that x = 1 didn't happened before
    }
    return false;
}

bool millerRabinPrimalityTest(lld n)
{ // n must be odd
    lld d = n - 1;
    while ((d & 1) == 0)
    {
        d >>= 1;
    }
    for (lld a : testSets)
    {
        if (a >= n)
            break;
        if (!millerRabinHelper(n, d, a))
            return false;
    }
    return true;
}