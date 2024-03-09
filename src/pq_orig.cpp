#include <vector>

#include "io.hpp"
#include "priority_queue.hpp"

int main()
{
    Input in; Output out;
    int n, q;
    in >> n >> q;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i)
        in >> v[i];
    PriorityQueue<int> pq(v.begin(), v.end());
    while (q--) {
        char c;
        int x = 0;
        in >> c;
        if (c == 'i') {
            in >> x;
            pq.insert(x);
        } else if (c == 'r') {
            pq.remove();
        } else if (c == 'p') {
            out << pq.peek() << '\n';
        }
    }
    return 0;
}
