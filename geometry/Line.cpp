#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Line
{
private:
    double a, b, c;
    double sqrta2b2;

public:
    Line() = default;
    Line(T a, T b, T c) : a(a), b(b), c(c)
    {
        sqrta2b2 = sqrt(a * a + b * b);
    }
    Line(pair<T, T> coord1, pair<T, T> coord2)
    {
        T x1 = coord1.first, y1 = coord1.second,
          x2 = coord2.first, y2 = coord2.second;
        a = y1 - y2;
        b = x2 - x1;
        c = (x1 - x2) * y1 - (y1 - y2) * x1;
        sqrta2b2 = sqrt(a * a + b * b);
    }
    double distanceWithPoint(pair<T, T> coord)
    {
        T x = coord.first, y = coord.second;
        return abs(a * x + b * y + c) / sqrta2b2;
    }
};