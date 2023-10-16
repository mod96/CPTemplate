///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////VERSION 2//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
#include <bits/stdc++.h>

#define range(i, s, e) for (i = s; i < e; i++)
#define irange(i, s, e) for (i = s; i > e; i--)
using namespace std;

template <typename NODE, typename VALUE, typename RESULT, typename INPUT>
class LazyPropagation
{
    /// <summary>
    ///
    /// </summary>
    /// <typeparam name="NODE">need "bool lazy", "INPUT input"</typeparam>
    /// <typeparam name="VALUE"></typeparam>
    /// <typeparam name="RESULT"></typeparam>
    /// <typeparam name="INPUT"></typeparam>
protected:
    int size, mid;
    vector<NODE> tree;
    int getSize(int n)
    {
        int res = 0;
        while ((1 << res++) < n)
            ;
        return 1 << res;
    }
    virtual NODE valueToNode(VALUE value, int idx);
    virtual RESULT nodeToResult(NODE node);
    virtual RESULT emptyResult();
    virtual RESULT combine(RESULT a, RESULT b);
    virtual void makeNode(int idx);
    virtual void theOperation(int idx, INPUT v);

    void propagateLazy(int idx, int left, int right)
    {
        if (tree[idx].lazy)
        {
            theOperation(idx, tree[idx].input);
            if (left < size)
            {
                tree[left].lazy = !tree[left].lazy;
            }
            if (right < size)
            {
                tree[right].lazy = !tree[right].lazy;
            }
            tree[idx].lazy = false;
        }
    }
    void _update(int idx, int sl, int sr, int l, int r, INPUT v)
    {
        int left = idx << 1,
            right = left + 1;
        propagateLazy(idx, left, right);
        if (l <= sl && sr <= r)
        {
            theOperation(idx, v);
            if (left < size)
            {
                tree[left].lazy = !tree[left].lazy;
            }
            if (right < size)
            {
                tree[right].lazy = !tree[right].lazy;
            }
        }
        else if (sr < l || r < sl)
        {
        }
        else
        {
            int mid = (sl + sr) >> 1;
            _update(left, sl, mid, l, r, v);
            _update(right, mid + 1, sr, l, r, v);
            makeNode(idx);
        }
    }
    RESULT _get(int idx, int sl, int sr, int l, int r)
    {
        int leftIdx = idx << 1,
            rightIdx = (idx << 1) + 1;
        propagateLazy(idx, sl, sr);
        if (l <= sl && sr <= r)
        {
            return nodeToResult(tree[idx]);
        }
        else if (r < sl || sr < l)
        {
            return emptyResult();
        }
        else
        {
            int mid = (sl + sr) >> 1;
            return combine(_get(leftIdx, sl, mid, l, r), _get(rightIdx, mid + 1, sr, l, r));
        }
    }

public:
    LazyPropagation() = default;
    LazyPropagation(int n, vector<VALUE> arr)
    { // root: 1, elt: 0 ~ mid (exclusive)
        size = getSize(n);
        mid = size >> 1;
        tree.resize(size);
        int length = arr.size();
        for (int i = 0; i < length; i++)
        {
            tree[i + mid] = valueToNode(arr[i], i);
        }
        for (int i = mid - 1; i > 0; i--)
        {
            makeNode(i);
        }
    }
    void update(int l, int r, INPUT v)
    {
        _update(1, 0, mid - 1, l - 1, r - 1, v);
    }
    RESULT get(int l, int r)
    {
        return _get(1, 0, mid - 1, l - 1, r - 1);
    }
};

// example: https://www.facebook.com/codingcompetitions/hacker-cup/2023/round-1/problems/D
#define MAX 1'000'000'007

typedef long long lld;

typedef struct Node_
{
    lld min;
    int minIdx;
    lld max;
    int maxIdx;
    bool lazy;
    lld input;
} Node;

class SegTreeLazy : public LazyPropagation<Node, lld, lld, lld>
{
protected:
    Node valueToNode(lld value, int idx)
    {
        return {value, idx + 1, value, idx + 1, false, 0};
    }
    lld nodeToResult(Node node)
    {
        return node.minIdx;
    }
    lld emptyResult()
    {
        return 0;
    }
    lld combine(lld a, lld b)
    {
        return 0;
    }
    void makeNode(int idx)
    {
        int left = idx << 1,
            right = left + 1;
        if (right < size && tree[right].min > 0)
        {
            if (tree[left].min <= tree[right].min)
            {
                tree[idx].min = tree[left].min;
                tree[idx].minIdx = tree[left].minIdx;
            }
            else
            {
                tree[idx].min = tree[right].min;
                tree[idx].minIdx = tree[right].minIdx;
            }
            if (tree[left].max >= tree[right].max)
            {
                tree[idx].max = tree[left].max;
                tree[idx].maxIdx = tree[left].maxIdx;
            }
            else
            {
                tree[idx].max = tree[right].max;
                tree[idx].maxIdx = tree[right].maxIdx;
            }
        }
        else if (left < size && tree[left].min > 0)
        {
            tree[idx] = {tree[left].min, tree[left].minIdx, tree[left].max, tree[left].maxIdx, tree[idx].lazy};
        }
    }
    void theOperation(int idx, lld input)
    {
        if (tree[idx].min > 0)
        {
            lld mini = tree[idx].min,
                maxi = tree[idx].max;
            int miniIdx = tree[idx].minIdx,
                maxiIdx = tree[idx].maxIdx;
            tree[idx].min = MAX - maxi;
            tree[idx].minIdx = maxiIdx;
            tree[idx].max = MAX - mini;
            tree[idx].maxIdx = miniIdx;
        }
    }

public:
    SegTreeLazy() = default;
    SegTreeLazy(int n, vector<lld> arr)
    {
        init(n, arr);
    }
    void update(int l, int r)
    {
        _update(1, 0, mid - 1, l - 1, r - 1, 0);
    }
    lld get()
    {
        propagateLazy(1, 2, 3);
        return tree[1].maxIdx;
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        int N, Q, L, R;
        cin >> N;
        vector<lld> arr(N);
        for (int n = 0; n < N; n++)
        {
            cin >> arr[n];
        }
        SegTreeLazy tree(N, arr);
        cin >> Q;
        lld res = 0;
        for (int q = 0; q < Q; q++)
        {
            cin >> L >> R;
            tree.update(L, R);
            res += tree.get();
        }
        cout << "Case #" << t << ": " << res << "\n";
    }

    return 0;
}