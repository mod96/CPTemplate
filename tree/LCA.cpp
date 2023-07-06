#include <bits/stdc++.h>

using namespace std;

class LCA
{
private:
    int N, root;
    vector<vector<int>> graph;
    vector<int> rank; // node have rank[node] - 1 parents
    vector<vector<int>> parents;
    int getPIdx(int diff)
    {
        int res = -1;
        while ((1 << ++res) <= diff)
            ;
        return res - 1;
    }
    void _makeTree(int parent, int node, int r)
    {
        rank[node] = r;
        int numParents = getPIdx(r - 1);
        for (int i = 0; i <= numParents; i++)
        {
            parents[node].push_back(parent);
            if (i != numParents)
                parent = parents[parent][i];
        }
        for (int nodeNext : graph[node])
        {
            if (rank[nodeNext])
                continue;
            _makeTree(node, nodeNext, r + 1);
        }
    }

public:
    LCA() = default;
    LCA(int N) : N(N), graph(N), rank(N), parents(N) {}
    void addEdge(int a, int b)
    {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    void makeTree(int root)
    {
        this->root = root;
        _makeTree(0, root, 1);
    }
    int getLCA(int a, int b)
    {
        while (rank[a] > rank[b])
            a = parents[a][getPIdx(rank[a] - rank[b])];
        while (rank[a] < rank[b])
            b = parents[b][getPIdx(rank[b] - rank[a])];
        while (a != b)
        {
            if (parents[a][0] == parents[b][0])
            {
                return parents[a][0];
            }
            bool flag = true;
            for (int i = 1; i < parents[a].size(); i++)
            {
                if (parents[a][i] == parents[b][i])
                {
                    a = parents[a][i - 1];
                    b = parents[b][i - 1];
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                a = parents[a][parents[a].size() - 1];
                b = parents[b][parents[b].size() - 1];
            }
        }
        return a;
    }
    int getRank(int a)
    {
        return rank[a];
    }
};