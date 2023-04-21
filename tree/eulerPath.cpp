#include <bits/stdc++.h>

using namespace std;

class EulerPath
{
private:
    int root;
    int numNodes; // exclusive
    vector<vector<int>> graph;
    vector<int> rank;

    vector<pair<int, int>> eulerRange;

    int eulerCnt = 0;

    void _makeTree(int node, int r)
    {
        rank[node] = r;
        eulerRange[node].first = ++eulerCnt;
        for (auto nextNode : graph[node])
        {
            if (rank[nextNode])
                continue;
            _makeTree(nextNode, r + 1);
        }
        eulerRange[node].second = eulerCnt;
    }

public:
    EulerPath() = default;
    EulerPath(int numNodes) : // node start with 1, end with numNodes - 1.
                              numNodes(numNodes), graph(numNodes), rank(numNodes), eulerRange(numNodes)
    {
    }
    void addEdge(int a, int b)
    {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    void makeTree(int root)
    {
        this->root = root;
        _makeTree(root, 1);
    }
    pair<int, int> getEulerRange(int node)
    {
        return eulerRange[node];
    }
    int getRank(int node)
    {
        return rank[node];
    }
};
