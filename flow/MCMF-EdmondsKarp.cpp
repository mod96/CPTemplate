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
    vector<int> before, dist;
    vector<bool> inQ;
    vector<Edge *> edgeBefore;

    bool SPFA(int st, int ed)
    { // but in this case, negative cycle doesn't exist.
        fill(before.begin(), before.end(), -1);
        fill(dist.begin(), dist.end(), MAX);
        fill(inQ.begin(), inQ.end(), false);

        queue<int> q;
        q.push(st);
        dist[st] = 0;
        inQ[st] = true;
        while (q.size() > 0)
        {
            int node = q.front();
            q.pop();
            inQ[node] = false;
            for (Edge *edge : graph[node])
            {
                int nodeNext = edge->nodeNext;
                if (edge->capa > edge->flow && dist[nodeNext] > dist[node] + edge->cost)
                {
                    dist[nodeNext] = dist[node] + edge->cost;
                    before[nodeNext] = node;
                    edgeBefore[nodeNext] = edge;
                    if (!inQ[nodeNext])
                    {
                        inQ[nodeNext] = true;
                        q.push(nodeNext);
                    }
                }
            }
        }
        return before[ed] != -1;
    }

public:
    MCMF() = default;
    MCMF(int nodes) : nodes(nodes), graph(nodes), before(nodes), dist(nodes), inQ(nodes), edgeBefore(nodes) {} // node: 1 ~ nodes (exclusive)
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
        while (true)
        {
            if (!SPFA(st, ed))
                break;

            int flow = MAX;
            for (int node = ed; node != st; node = before[node])
                flow = min(flow, edgeBefore[node]->capa - edgeBefore[node]->flow);
            for (int node = ed; node != st; node = before[node])
            {
                resCost += flow * edgeBefore[node]->cost;
                edgeBefore[node]->updateFlow(flow);
            }
            resFlow += flow;
        }
        return {resCost, resFlow};
    }
};