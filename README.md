This project was implemented as part of Assignment 2 of Advanced Data Structures and Algorithms (CS5800), 2024 at Indian Institute of Technology, Madras.

# Requirements

The C++ source requires g++, clang or an equivalent compiler and is platform independent. This project has been developed and tested on GNU Linux (5.15.133.1-microsoft-standard-WSL2) and the rest of this document assumes it is being run on a modern Linux distribution.

`cmake` is required to run `make`.

# Quick Start

Run `make kruskal` to generate the binary `./bin/kruskal`.

`kruskal` implements a solution to the problem given below using Kruskal's Minimum Spanning Tree algorithm.

# Problem Statement

The following problem statement has been used to demonstrate this project's implementation of Kruskal's MST algorithm.

## Minimum Spanning Tree

### Statement

Find the minimum spanning tree or forest of the given graph.

### Input Format

The first line of input contains two space-separated integers **n** and **m**, where **n** represents the number of nodes in the graph, or rather, the index of the maximum numbered node, and **m** represents the number of edges.

The following **m** lines each contain three space-separated integers **u_i, v_i, w_i** representing the i-th edge of the undirected graph.

### Output Format

On the first line, output a single integer **k** representing the number of edges in the minimum spanning tree / forest. Then, output **k** lines, with each line containing three space-separated integers **u_i, v_i, w_i** representing the i-th edge of the minimum spanning forest. Finally, output a single integer **W** representing the total weight of the minimum spanning forest.

### Constraints

0 ≤ **n, m** ≤ 10⁷

0 ≤ **u_i, v_i** ≤ **n**

-10⁹ ≤ **w_i** ≤ 10⁹

### Sample Input
```
4 5
1 2 10
2 3 15
1 3 5
4 2 2
4 3 40
```

### Sample Output
```
3
4 2 2
1 3 5
1 2 10
17
```

# Notes

This implementation uses a custom input/output library for better performance.
