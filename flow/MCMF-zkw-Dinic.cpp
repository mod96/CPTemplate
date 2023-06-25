#include <bits/stdc++.h>

#define range(i, s, e) for (i = s; i < e; i++)
#define irange(i, s, e) for (i = s; i > e; i--)
#define MAX 100'000'000

using namespace std;

class Edge
{
public:
    int nodeNext, capa, cost, flow;
    Edge *reverse;
    Edge() = default;
    Edge(int nodeNext, int capa, int cost) : nodeNext(nodeNext), capa(capa), cost(cost), flow(0) {}
    void setReverse(Edge *reverse)
    {
        this->reverse = reverse;
    }
    void updateFlow(int f)
    {
        flow += f;
        reverse->flow -= f;
    }
};

class MCMF
{
private:
    int nodes;
    vector<vector<Edge *>> graph;
    vector<int> dist, dfsIdx;
    vector<bool> lock;

    bool spfa(int st, int ed)
    { // but in this case, negative cycle doesn't exist.
        fill(dist.begin(), dist.end(), MAX);
        fill(lock.begin(), lock.end(), false);

        queue<int> q;
        q.push(st);
        dist[st] = 0;
        lock[st] = true;
        while (q.size() > 0)
        {
            int node = q.front();
            q.pop();
            lock[node] = false;
            for (Edge *edge : graph[node])
            {
                int nodeNext = edge->nodeNext;
                if (edge->capa > edge->flow && dist[nodeNext] > dist[node] + edge->cost)
                {
                    dist[nodeNext] = dist[node] + edge->cost;
                    if (!lock[nodeNext])
                    {
                        lock[nodeNext] = true;
                        q.push(nodeNext);
                    }
                }
            }
        }
        return dist[ed] != MAX;
    }

    int dfs(int node, int flow, int ed)
    {
        lock[node] = true;
        if (node == ed)
            return flow;
        for (int &i = dfsIdx[node]; i < graph[node].size(); i++)
        {
            Edge *edge = graph[node][i];
            int nodeNext = edge->nodeNext;
            if (!lock[nodeNext] && dist[nodeNext] == dist[node] + edge->cost && edge->capa > edge->flow)
            {
                int resultFlow = dfs(nodeNext, min(flow, edge->capa - edge->flow), ed);
                if (resultFlow)
                {
                    edge->updateFlow(resultFlow);
                    return resultFlow;
                }
            }
        }
        return 0;
    }

public:
    MCMF() = default;
    MCMF(int nodes) : nodes(nodes), graph(nodes), dist(nodes), dfsIdx(nodes), lock(nodes) {} // node: 1 ~ nodes (exclusive)
    void addEdge(int x, int y, int capa, int cost)
    {
        graph[x].push_back(new Edge(y, capa, cost));
        graph[y].push_back(new Edge(x, 0, -cost));
        graph[x].back()->setReverse(graph[y].back());
        graph[y].back()->setReverse(graph[x].back());
    }
    pair<int, int> run(int st, int ed)
    {
        int resCost = 0;
        int resFlow = 0;
        while (spfa(st, ed))
        {
            fill(dfsIdx.begin(), dfsIdx.end(), 0);
            fill(lock.begin(), lock.end(), false);
            while (int newFlow = dfs(st, MAX, ed))
            {
                resFlow += newFlow;
                resCost += dist[ed] * newFlow;
                fill(lock.begin(), lock.end(), false);
            }
        }
        return {resCost, resFlow};
    }
};