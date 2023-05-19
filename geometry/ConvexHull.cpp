#include <bits/stdc++.h>

using namespace std;

template <typename T>
class ConvexHull
{
private:
    vector<pair<T, T>> original;
    T stdY = numeric_limits<T>::max(), stdX = numeric_limits<T>::max(), stdI;
    int size;
    bool arrowIsCounterClock(const pair<T, T> &A, const pair<T, T> &B, const pair<T, T> &C)
    {
        return (B.first - A.first) * (C.second - B.second) - (B.second - A.second) * (C.first - B.first) > 0;
    }
    vector<pair<T, T>> stackToVector(stack<pair<T, T>> &st)
    {
        vector<pair<T, T>> vec(st.size());
        int idx = st.size() - 1;
        while (idx > -1)
        {
            vec[idx] = st.top();
            st.pop();
            idx--;
        }
        return vec;
    }

public:
    ConvexHull() = default;
    ConvexHull(int size) : size(size) {}

    void push(T x, T y)
    {
        if (y < stdY || (y == stdY && x < stdX))
        {
            stdX = x;
            stdY = y;
            stdI = original.size();
        }
        original.push_back({x, y});
    }

    vector<pair<T, T>> graham()
    {
        original.erase(original.begin() + stdI);
        sort(original.begin(), original.end(),
             [this](const pair<T, T> &a, const pair<T, T> &b) -> bool
             {
                 T x1 = a.first - stdX, y1 = a.second - stdY,
                   x2 = b.first - stdX, y2 = b.second - stdY;
                 T ccw = x1 * y2 - x2 * y1;
                 if (ccw)
                     return ccw > 0;
                 return x1 * x1 + y1 * y1 - x2 * x2 - y2 * y2 < 0;
             });
        stack<pair<T, T>> result;
        result.push({stdX, stdY});
        result.push(original[0]);
        for (int i = 1; i < size - 1; i++)
        {
            pair<T, T> C = original[i];
            while (result.size() > 1)
            {
                pair<T, T> B = result.top();
                result.pop();
                pair<T, T> A = result.top();
                if (arrowIsCounterClock(A, B, C))
                {
                    result.push(B);
                    break;
                }
            }
            result.push(C);
        }
        return stackToVector(result);
    }
};