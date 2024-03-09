#include <functional>
#include <set>
#include <vector>

#include "io.hpp"

int main()
{
    Input in; Output out;
    int n, q;
    in >> n >> q;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i)
        in >> v[i];
    std::multiset<int, std::greater<>> pq(v.begin(), v.end());
    while (q--) {
        char c;
        int x = 0;
        in >> c;
        if (c == 'i') {
            in >> x;
            pq.insert(x);
        } else if (c == 'r') {
            pq.erase(pq.begin());
        } else if (c == 'p') {
            out << *pq.begin() << '\n';
        }
    }
    return 0;
}
