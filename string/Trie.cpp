#include <bits/stdc++.h>

#define range(i, s, e) for (i = s; i < e; i++)
#define irange(i, s, e) for (i = s; i > e; i--)

using namespace std;

//--------------------------------------------------------------------------------//
#define BaseAlphabet 'a'

class ArrayTrie
{
protected:
    bool end;
    ArrayTrie *children[26];

    void setEnd()
    {
        end = true;
    }

public:
    void push(string s)
    {
        int i, length = s.length();
        ArrayTrie *node = this;
        range(i, 0, length)
        {
            int idx = s[i] - BaseAlphabet;
            if (node->children[idx] == nullptr)
            {
                node->children[idx] = new ArrayTrie();
            }
            node = node->children[idx];
        }
        node->setEnd();
    }
    void pushReverse(string s)
    {
        int i, length = s.length();
        ArrayTrie *node = this;
        irange(i, length - 1, -1)
        {
            int idx = s[i] - BaseAlphabet;
            if (node->children[idx] == nullptr)
            {
                node->children[idx] = new ArrayTrie();
            }
            node = node->children[idx];
        }
        node->setEnd();
    }
    ArrayTrie *nextNode(char c)
    {
        return children[c - BaseAlphabet];
    }
    bool isEnd()
    {
        return end;
    }
};

//--------------------------------------------------------------------------------//

class MapTrie
{
protected:
    bool end;
    map<char, MapTrie *> children;

    void setEnd()
    {
        end = true;
    }

public:
    void push(string &s)
    {
        int i, length = s.length();
        MapTrie *node = this;
        range(i, 0, length)
        {
            if (node->children.find(s[i]) == node->children.end())
            {
                node->children[s[i]] = new MapTrie();
            }
            node = node->children[s[i]];
        }
        node->setEnd();
    }
    void pushReverse(string &s)
    {
        int i, length = s.length();
        MapTrie *node = this;
        irange(i, length - 1, -1)
        {
            if (node->children.find(s[i]) == node->children.end())
            {
                node->children[s[i]] = new MapTrie();
            }
            node = node->children[s[i]];
        }
        node->setEnd();
    }
    MapTrie *nextNode(char &c)
    {
        return children[c];
    }
    bool isEnd()
    {
        return end;
    }
};