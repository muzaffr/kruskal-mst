#include <queue>
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
    std::priority_queue<int> pq(v.begin(), v.end());
    while (q--) {
        char c;
        int x = 0;
        in >> c;
        if (c == 'i') {
            in >> x;
            pq.push(x);
        } else if (c == 'r') {
            pq.pop();
        } else if (c == 'p') {
            out << pq.top() << '\n';
        }
    }
    return 0;
}
