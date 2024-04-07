#pragma once

#include <stdlib.h>     /* int64_t */

/**
 * This class implements a weighted edge, with support for sorting.
 */
class Edge
{
public:
    int u;      ///< First node of the edge.
    int v;      ///< Second node of the edge.
    int64_t w;  ///< Weight of the edge.

    /**
     * Constructor. Initializes a sentinel Edge.
     */
    Edge() noexcept;

    /**
     * Constructor. Initializes an Edge with 0 weight.
     * @param[in] eu First node of the edge.
     * @param[in] ev Second node of the edge.
     */
    Edge(int eu, int ev) noexcept;

    /**
     * Constructor. Initializes an Edge.
     * @param[in] eu First node of the edge.
     * @param[in] ev Second node of the edge.
     * @param[in] ew Weight of the edge.
     */
    Edge(int eu, int ev, int64_t ew) noexcept;

    /**
     * Operator overload for >, to support sorting.
     * @param[in] b Second operand.
     */
    inline bool operator>(const Edge& b) const noexcept;
};

/**
 * This class implements algorithms for the Minimum Spanning Tree problem.
 */
class MinimumSpanningTree
{
private:
    int n;          ///< Number of nodes in the input graph.
    int m;          ///< Number of edges in the input graph.
    int ctr;        ///< Number of edges in the output forest.
    Edge* edges;    ///< List of input edges.
    Edge* mst;      ///< List of edges in the minimum spanning forest.

public:
    /**
     * Constructor.
     * @param[in] nodes Number of nodes in the input graph.
     */
    MinimumSpanningTree(int nodes) noexcept;

    /**
     * Destructor. Frees allocated memory if any.
     */
    ~MinimumSpanningTree();

    /**
     * Read the edges of the input graph from STDIN.
     * @param[in] num_edges Number of edges in the input graph.
     */
    void read(int num_edges);

    /**
     * Output the edges of the minimum spanning forest to STDOUT.
     */
    void print() const;

    /**
     * Execute the Kruskal's MST algorithm on the stored edge list.
     */
    void kruskal();
};
