#include <bits/stdc++.h>

#define range(i, s, e) for (i = s; i < e; i++)
#define irange(i, s, e) for (i = s; i > e; i--)

using namespace std;

int arr[200'002];

int manacher(const string &s)
{
    int pr = 0, p = 0, size = s.size();
    for (int i = 0; i < size; i++)
    {
        int &a = arr[i];
        a = i <= pr ? min(pr - i, arr[2 * p - i]) : 0;
        while (i - a - 1 >= 0 && i + a + 1 < size && s[i - a - 1] == s[i + a + 1])
            a++;
        if (i + a > pr)
        {
            pr = i + a;
            p = i;
        }
    }
    int res = 0;
    for (int i = 0; i < size; i++)
        res = max(res, arr[i]);
    return res;
}

int main()
{ // boj 13275
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string st;
    string targ;
    cin >> st;
    int i;
    range(i, 0, st.size())
    {
        targ += '|';
        targ += st[i];
    }
    targ += '|';
    cout << manacher(targ);

    return 0;
}