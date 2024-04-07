#include <stdlib.h>     /* malloc, realloc, free, exit, NULL */
#include <stdexcept>    /* out_of_range, runtime_error */

#include "io.hpp"
#include "dsu.hpp"
#include "mst.hpp"
#include "priority_queue.hpp"


Edge::Edge() noexcept
{
    this->u = 0;
    this->v = 0;
    this->w = 0;
}

Edge::Edge(int eu, int ev) noexcept
{
    this->u = eu;
    this->v = ev;
    this->w = 0;
}

Edge::Edge(int eu, int ev, int64_t ew) noexcept
{
    this->u = eu;
    this->v = ev;
    this->w = ew;
}

inline bool Edge::operator>(const Edge& b) const noexcept
{
    return w > b.w;
}


MinimumSpanningTree::MinimumSpanningTree(int nodes) noexcept
{
    n = nodes;
    ctr = 0;
}

MinimumSpanningTree::~MinimumSpanningTree()
{
    if (edges) {
        free(edges);
        edges = NULL;
    }
    if (mst) {
        free(mst);
        mst = NULL;
    }
}

void MinimumSpanningTree::read(int num_edges)
{
    Input in;
    m = num_edges;
    edges = (Edge *) malloc(m * sizeof(Edge));
    for (int i = 0; i < m; ++i) {
        auto& e = edges[i];
        in >> e.u >> e.v >> e.w;
    }
}

void MinimumSpanningTree::print() const
{
    Output out;
    if (mst == NULL) {
        throw std::runtime_error("null pointer exception");
    }
    out << ctr << '\n';
    int64_t w = 0;
    for (int i = 0; i < ctr; ++i) {
        Edge& e = mst[i];
        out << e.u << ' ' << e.v << ' ' << e.w << '\n';
        w += e.w;
    }
    out << w << '\n';
}

void MinimumSpanningTree::kruskal()
{
    if (edges == NULL or ctr != 0) {
        throw std::runtime_error("repeated execution");
    }
    DSU dsu(n);
    sort(edges, m);
    mst = (Edge *) malloc(n * sizeof(Edge));
    for (int i = 0; i < m; ++i) {
        Edge e = edges[i];
        if (dsu.root(e.u) != dsu.root(e.v)) {
            mst[ctr++] = e;
            dsu.merge(e.u, e.v);
        }
    }
}
