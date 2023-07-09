#include <bits/stdc++.h>

using namespace std;

const double Pi = 3.14159265358979;
typedef complex<double> cpx;

void FFT(vector<cpx> &v, cpx w)
{
    int n = v.size(), n_2 = n >> 1;
    if (n == 1)
        return;
    vector<cpx> even(n_2), odd(n_2);
    for (int i = 0; i < n; i++)
    {
        if (i & 1)
        {
            odd[i >> 1] = v[i];
        }
        else
        {
            even[i >> 1] = v[i];
        }
    }
    FFT(even, w * w);
    FFT(odd, w * w);
    cpx z(1, 0);
    for (int i = 0; i < n_2; i++)
    {
        v[i] = even[i] + z * odd[i];
        v[i + n_2] = even[i] - z * odd[i];
        z *= w;
    }
}

vector<int> multiplyPolynomials(vector<int> &v, vector<int> &u)
{
    vector<int> res(v.size() + u.size() - 1);

    int n = 1;
    while (n < v.size() || n < u.size())
        n <<= 1;
    n <<= 1;

    vector<cpx> _v(n), _u(n);
    for (int i = 0; i < v.size(); i++)
        _v[i] = v[i];
    for (int i = 0; i < u.size(); i++)
        _u[i] = u[i];

    cpx w(cos(2 * Pi / n), sin(2 * Pi / n));
    FFT(_v, w);
    FFT(_u, w);

    for (int i = 0; i < n; i++)
        _v[i] *= _u[i];

    cpx w_i = cpx(1, 0) / w;
    FFT(_v, w_i);
    for (int i = 0; i < n; i++)
        _v[i] /= n;

    for (int i = 0; i < res.size(); i++)
        res[i] = round(_v[i].real());

    return res;
}