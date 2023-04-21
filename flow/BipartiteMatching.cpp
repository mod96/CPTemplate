#include <bits/stdc++.h>

#define range(i, s, e) for (i = s; i < e; i++)
#define irange(i, s, e) for (i = s; i > e; i--)

using namespace std;

class BipartiteMatching
{
private:
    int leftNums, rightNums; // node: 1 ~ Nums exclusive
    vector<vector<int>> l2r;
    vector<int> r2l;
    vector<bool> visited;
    bool recur(int l)
    {
        for (auto r : l2r[l])
        {
            if (r2l[r])
                continue;
            r2l[r] = l;
            return true;
        }
        for (auto r : l2r[l])
        {
            if (visited[r])
                continue;
            visited[r] = true;
            if (recur(r2l[r]))
            {
                r2l[r] = l;
                visited[r] = false;
                return true;
            }
        }
        return false;
    }

public:
    BipartiteMatching() = default;
    BipartiteMatching(int l, int r) : leftNums(l), rightNums(r), l2r(l), r2l(r), visited(r) {}
    int run()
    {
        int i, res = 0;
        range(i, 1, leftNums)
        {
            fill(visited.begin(), visited.end(), false);
            res += recur(i);
        }
        return res;
    }
    void addEdge(int l, int r)
    {
        l2r[l].push_back(r);
    }
};