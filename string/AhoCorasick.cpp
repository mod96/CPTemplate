#include <bits/stdc++.h>

#define range(i, s, e) for (i = s; i < e; i++)
#define irange(i, s, e) for (i = s; i > e; i--)

using namespace std;

class AhoTrie
{ // all public functions are only for root.
private:
    map<char, AhoTrie *> next;
    AhoTrie *fail;
    bool isEnd = false;
    bool cannotGo(char &c)
    {
        return next.find(c) == next.end();
    }

public:
    AhoTrie() = default;

    void push(string &s)
    {
        int i, length = s.size();
        AhoTrie *node = this;
        range(i, 0, length)
        {
            if (node->next.find(s[i]) == node->next.end())
            {
                node->next[s[i]] = new AhoTrie();
            }
            node = node->next[s[i]];
        }
        node->isEnd = true;
    }

    void buildFailFunction()
    {
        this->fail = this; // root's fail returns to root.

        queue<AhoTrie *> q;
        q.push(this);
        while (q.size() > 0)
        {
            AhoTrie *node = q.front();
            q.pop();
            for (auto it = node->next.begin(); it != node->next.end(); it++)
            {
                char c = it->first;
                AhoTrie *nodeNext = it->second;
                if (node == this)
                {
                    nodeNext->fail = this;
                }
                else
                {
                    AhoTrie *dst = node->fail;
                    while (dst != this && dst->cannotGo(c))
                    {
                        dst = dst->fail;
                    }
                    if (!dst->cannotGo(c))
                        dst = dst->next[c];
                    nodeNext->fail = dst;
                }
                if (nodeNext->fail->isEnd)
                    nodeNext->isEnd = true;
                q.push(nodeNext);
            }
        }
    }

    bool oneOfUsIn(string &s)
    {
        int i, length = s.size();
        AhoTrie *node = this; // this is root
        range(i, 0, length)
        {
            while (node != this && node->cannotGo(s[i]))
            {
                node = node->fail;
            }
            if (!node->cannotGo(s[i]))
            {
                node = node->next[s[i]];
            }
            if (node->isEnd)
            {
                return true;
            }
        }
        return false;
    }
};
