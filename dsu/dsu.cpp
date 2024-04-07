#include <stdlib.h>     /* malloc, free, NULL */

#include "dsu.hpp"

DSU::DSU(int n)
{
    rt = (int *) malloc((n + 1) * sizeof(int));
    sz = (int *) malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; ++i) {
        rt[i] = i;
        sz[i] = 1;
    }
    parts = n;
}

DSU::~DSU() noexcept
{
    if (rt) {
        free(rt);
        rt = NULL;
    }
    if (sz) {
        free(sz);
        sz = NULL;
    }
}

int DSU::root(int k)
{
    while (k != rt[k])
        k = rt[k] = rt[rt[k]];
    return k;
}

void DSU::merge(int u, int v)
{
    int r1 = root(u), r2 = root(v);
    if (r1 == r2)
        return;
    parts--;
    if (sz[r1] > sz[r2]) {
        int t_ = r1;
        r1 = r2;
        r2 = t_;
    }
    sz[r2] += sz[r1];
    sz[r1] = 0;
    rt[r1] = rt[r2];
}
