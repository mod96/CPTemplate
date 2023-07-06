#include <bits/stdc++.h>

using namespace std;

template <typename T, typename R>
class MoAlgorithm
{
    friend struct Query;

protected:
    int N, sqrtN, Q;
    struct Query
    {
        MoAlgorithm<T, R> *parent;
        int idx, s, e;
        bool operator<(Query &x)
        {
            if (s / parent->sqrtN != x.s / parent->sqrtN)
                return s / parent->sqrtN < x.s / parent->sqrtN;
            return e < x.e;
        }
    };
    vector<T> arr;       // to use from index 1, need to append any value first.
    vector<R> res;       // 0 ~ Q (exclusive)
    vector<Query> query; // 0 ~ Q (exclusive)
    virtual void addElt(int idx) = 0;
    virtual void deleteElt(int idx) = 0;
    virtual R getResNow(int qIdx) = 0;

public:
    MoAlgorithm() = default;
    void setN(int N)
    {
        this->N = N;
        this->sqrtN = sqrt(N);
        this->arr.resize(N); // 0 ~ N (exclusive)
    }
    void setQ(int Q)
    {
        this->Q = Q;
        this->res.resize(Q);
        this->query.resize(Q);
    }
    void appendArr(int idx, T a)
    {
        arr[idx] = a;
    }
    void appendQuery(int idx, int s, int e)
    {
        query[idx] = {this, idx, s, e};
    }
    void run()
    {
        sort(query.begin(), query.end());
        Query q = query[0];
        int s = q.s, e = q.e;
        for (int i = s; i <= e; i++)
        {
            addElt(i);
        }
        res[q.idx] = getResNow(0);
        for (int j = 1; j < Q; j++)
        {
            q = query[j];
            while (s < q.s)
                deleteElt(s++);
            while (q.s < s)
                addElt(--s);
            while (e < q.e)
                addElt(++e);
            while (q.e < e)
                deleteElt(e--);
            res[q.idx] = getResNow(j);
        }
    }
};

class Sample2912 : public MoAlgorithm<int, pair<bool, int>>
{
private:
    int n;
    vector<int> cnt;
    void addElt(int idx)
    {
        cnt[arr[idx]]++;
    }
    void deleteElt(int idx)
    {
        cnt[arr[idx]]--;
    }
    pair<bool, int> getResNow(int qIdx)
    {
        int maxCnt = 0, maxIdx;
        for (int i = 1; i < cnt.size(); i++)
        {
            if (cnt[i] > maxCnt)
            {
                maxCnt = cnt[i];
                maxIdx = i;
            }
        }
        int half = (query[qIdx].e - query[qIdx].s + 1) >> 1;
        if (maxCnt > half)
            return {true, maxIdx};
        return {false, 0};
    }

public:
    Sample2912() = default;
    Sample2912(int elts, int c) : n(elts), cnt(c)
    {
        setN(elts);
    }
    vector<pair<bool, int>> &getRes()
    {
        return res;
    }
};