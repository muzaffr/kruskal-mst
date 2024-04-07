#pragma once

/**
 * This class implements a disjont-set/union-find structure. \n
 * This implementation employs the path compression optimization.
 */
class DSU
{
private:
    int parts;  ///< Number of parts or disjoint sets.
    int* rt;    ///< Array of parent sets or root sets.
    int* sz;    ///< Array of the size of the belonging set.

public:
    /**
     * Constructor. Initializes a DSU data structure for n sets.
     * @param[in] n (Initial) number of sets.
     */
    DSU(int n);

    /**
     * Destructor. Frees allocated memory.
     */
    ~DSU() noexcept;

    /**
     * Find the set/parent/root of the kth element
     * @param[in] k Index of the subject element.
     */
    int root(int k);

    /**
     * Merge the sets of u and v.
     * @param[in] u First element to merge.
     * @param[in] v Second element to merge.
     */
    void merge(int u, int v);
};
