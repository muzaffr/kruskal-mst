#include <algorithm>
#include <vector>

#include "io.hpp"

int main()
{
    Input in; Output out;
    int n;
    in >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i)
        in >> v[i];
    std::sort(v.begin(), v.end());
    for (int it : v)
        out << it << ' ';
    out << '\n';
    return 0;
}
