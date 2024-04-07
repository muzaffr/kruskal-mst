#include "io.hpp"
#include "mst.hpp"

int main()
{
    Input in;
    int nodes, edges;
    in >> nodes >> edges;
    MinimumSpanningTree mst(nodes);
    mst.read(edges);
    mst.kruskal();
    mst.print();
    return 0;
}
