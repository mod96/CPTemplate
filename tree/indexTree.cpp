#include <bits/stdc++.h>

using namespace std;

template <typename T>
class BaseIndexTree
{
protected:
    int limit;
    vector<T> tree;
    void _update(int i, T val)
    {
        while (i < limit)
        {
            tree[i] += val;
            i += i & -i;
        }
    }
    T _get(int i)
    {
        T res = 0;
        while (i > 0)
        {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }

public:
    BaseIndexTree() = default;
    BaseIndexTree(int limit) : limit(limit), tree(limit) {}
};

template <typename T>
class PointUpdateRangeQuery : public BaseIndexTree<T>
{
public:
    PointUpdateRangeQuery() = default;
    PointUpdateRangeQuery(int limit) : BaseIndexTree<T>(limit) {}
    void update(int i, T val)
    {
        this->_update(i, val);
    }
    T get(int i)
    {
        return this->_get(i);
    }
};

template <typename T>
class RangeUpdatePointQuery : public BaseIndexTree<T>
{
public:
    RangeUpdatePointQuery() = default;
    RangeUpdatePointQuery(int limit) : BaseIndexTree<T>(limit) {}
    void update(int i, int j, T val)
    {
        this->_update(i, val);
        this->_update(j + 1, -val);
    }
    T get(int i)
    {
        return this->_get(i);
    }
};

template <typename T>
class RangeUpdateRangeQuery
{
private:
    RangeUpdatePointQuery BIT1;
    PointUpdateRangeQuery BIT2;
    T _get(int i)
    {
        return BIT1.get(i) * i - BIT2.get(i);
    }

public:
    RangeUpdateRangeQuery() = default;
    RangeUpdateRangeQuery(int limit) : BIT1(limit), BIT2(limit) {}
    void update(int l, int r, T val)
    {
        BIT1.update(l, r, val);
        BIT2.update(l, (l - 1) * val);
        BIT2.update(r + 1, -r * val);
    }
    T get(int l, int r)
    {
        return _get(r) - _get(l - 1);
    }
};