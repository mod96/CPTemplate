#include <bits/stdc++.h>

#pragma warning(disable : 4996)

#define range(i, s, e) for (i = s; i < e; i++)
#define irange(i, s, e) for (i = s; i > e; i--)

using namespace std;

class CombinationModP
{
private:
    int p;
    vector<vector<int>> dp;

public:
    CombinationModP() = default;
    CombinationModP(int p) : p(p)
    {
        dp.push_back(vector<int>(1, 1));
    }
    int nCr(int n, int r)
    { // n >= r
        if (n < r)
        {
            return 0;
        }
        while (n >= dp.size())
        { // mCk
            int m = dp.size();
            dp.push_back(vector<int>(m + 1));
            dp[m][0] = 1;
            for (int k = 1; k < m; k++)
            {
                dp[m][k] = (dp[m - 1][k - 1] + dp[m - 1][k]) % p;
            }
            dp[m][m] = 1;
        }
        return dp[n][r];
    }
};

class Lucas
{
private:
    int p;
    CombinationModP combTool;

public:
    Lucas() = default;
    Lucas(int p) : p(p), combTool(p) {}
    int nCrLucas(int n, int r)
    {
        if (r == 0)
            return 1;
        int ni = n % p,
            ri = r % p;
        return (nCrLucas(n / p, r / p) * combTool.nCr(ni, ri)) % p;
    }
};

int modInverse(int a, int m)
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    // Apply extended Euclid Algorithm
    while (a > 1)
    {
        q = a / m;

        t = m;
        m = a % m, a = t;

        t = x0;
        x0 = x1 - q * x0, x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

int chineseRemainder(int num[], int rem[], int k)
{
    int prod = 1;
    for (int i = 0; i < k; i++)
        prod *= num[i];

    // Initialize result
    int result = 0;

    for (int i = 0; i < k; i++)
    {
        int pp = prod / num[i];
        result = (result + ((((rem[i] * modInverse(pp, num[i])) % prod) * pp) % prod)) % prod;
    }

    return result;
}