#include <bits/stdc++.h>

#define range(i, s, e) for (i = s; i < e; i++)
#define irange(i, s, e) for (i = s; i > e; i--)

using namespace std;

class LCP
{
protected:
    string &S;
    vector<int> sa;
    vector<int> isa;
    vector<int> lcp;
    int n, m;

private:
    vector<int> cnt;
    vector<int> res1;

    void sort(vector<int> &r, int d)
    {
        int i;
        fill(cnt.begin(), cnt.end(), 0);
        range(i, 0, n) cnt[r[i + d]]++;
        range(i, 1, m) cnt[i] += cnt[i - 1];
        irange(i, n - 1, -1) res1[--cnt[r[i + d]]] = i;

        fill(cnt.begin(), cnt.end(), 0);
        range(i, 0, n) cnt[r[i]]++;
        range(i, 1, m) cnt[i] += cnt[i - 1];
        irange(i, n - 1, -1)
        {
            int idx = res1[i];
            sa[--cnt[r[idx]]] = idx;
        }
    }

public:
    LCP() = default;
    LCP(string &S)
        : S(S), sa(S.size()), isa(S.size()), lcp(S.size()), n(S.size()), m(max((int)S.size() + 1, 256)), res1(S.size())
    {
        cnt.resize(m);
    }
    void buildSA()
    {
        vector<int> r(n << 1), nr(n << 1);
        int i;
        range(i, 0, n)
        {
            sa[i] = i, r[i] = S[i];
        }
        for (int d = 1; d < n; d <<= 1)
        {
            auto cmp = [&](int a, int b)
            {
                return r[a] < r[b] || (r[a] == r[b] && r[a + d] < r[b + d]);
            };
            sort(r, d);
            nr[sa[0]] = 1;
            range(i, 1, n) nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
            range(i, 0, n) r[i] = nr[i];
            if (r[sa[n - 1]] == n)
                break;
        }
    }
    void printSA()
    {
        int i;
        range(i, 0, n)
        {
            printf("%d ", sa[i]);
        }
        printf("\n");
    }
    int buildLCP()
    {
        int i, j, k = 0, k_max = 0;
        range(i, 0, n) isa[sa[i]] = i;
        range(i, 0, n)
        {
            if (isa[i])
            {
                j = sa[isa[i] - 1];
                while (i + k < n && j + k < n && S[i + k] == S[j + k])
                {
                    k++;
                }
                if (k > 0)
                {
                    lcp[isa[i]] = k;
                    (k > k_max) && (k_max = k);
                    k--;
                }
            }
        }
        return k_max;
    }
};
