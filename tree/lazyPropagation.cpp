#include <bits/stdc++.h>

using namespace std;

template <typename T>
class LazyPropagation
{
protected:
    int size, mid;
    vector<T> tree;
    int getSize(int n)
    {
        int res = 0;
        while ((1 << res++) < n)
            ;
        return 1 << res;
    }

public:
    LazyPropagation() = default;
    LazyPropagation(int n)
    { // root: 1, elt: 0 ~ mid (exclusive)
        size = getSize(n);
        mid = size >> 1;
        tree.resize(size);
    }
};

typedef struct onOffElt_
{
    int val, lazy; // 1: on, 2: off
} onOffElt;

class OnOffLazyPropagation : public LazyPropagation<onOffElt>
{
private:
    void updateLazy(int idx, int sl, int sr)
    {
        if (tree[idx].lazy)
        {
            int leftIdx = idx << 1,
                rightIdx = (idx << 1) + 1;
            tree[idx].val = tree[idx].lazy == 1 ? sr - sl + 1 : 0;
            if (rightIdx < size)
            {
                tree[leftIdx].lazy = tree[idx].lazy;
                tree[rightIdx].lazy = tree[idx].lazy;
            }
            tree[idx].lazy = 0;
        }
    }
    int _update(int idx, int sl, int sr, int l, int r, bool onOff)
    {
        int leftIdx = idx << 1,
            rightIdx = (idx << 1) + 1;
        updateLazy(idx, sl, sr);
        if (l <= sl && sr <= r)
        {
            tree[idx].val = onOff ? sr - sl + 1 : 0;
            if (rightIdx < size)
            {
                tree[leftIdx].lazy = onOff ? 1 : 2;
                tree[rightIdx].lazy = onOff ? 1 : 2;
            }
        }
        else if (r < sl || sr < l)
        {
        }
        else
        {
            int mid = (sl + sr) >> 1;
            tree[idx].val = _update(leftIdx, sl, mid, l, r, onOff) + _update(rightIdx, mid + 1, sr, l, r, onOff);
        }
        return tree[idx].val;
    }
    int _get(int idx, int sl, int sr, int l, int r)
    {
        int leftIdx = idx << 1,
            rightIdx = (idx << 1) + 1;
        updateLazy(idx, sl, sr);
        if (l <= sl && sr <= r)
        {
            return tree[idx].val;
        }
        else if (r < sl || sr < l)
        {
            return 0;
        }
        else
        {
            int mid = (sl + sr) >> 1;
            return _get(leftIdx, sl, mid, l, r) + _get(rightIdx, mid + 1, sr, l, r);
        }
    }

public:
    OnOffLazyPropagation() = default;
    OnOffLazyPropagation(int n) : LazyPropagation(n) {}
    void update(int l, int r, bool onOff)
    { // 0 ~ n (exclusive)
        _update(1, 0, mid - 1, l, r, onOff);
    }
    int get(int l, int r)
    {
        return _get(1, 0, mid - 1, l, r);
    }
};