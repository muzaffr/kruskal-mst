#pragma once

#include <stddef.h>

/**
 * This class implements a priority queue using a heap as the data structure. \n
 * It supports empty initialization as well as initialization from a C-style
 * or a C++-style range. \n
 * It comes with friend functions for heapsort, utilizing the heap coroutines.
 */
template <class T>
class PriorityQueue {
private:
    T* heap;            ///< Pointer to just before the beginning of the heap.
    size_t sz;          ///< Current size of the heap (number of elements).
    size_t cap;         ///< Current capacity of the heap (memory allocated).
    bool _from_range;   ///< Whether @heap points to an externally allocated range.

    /**
     * Calculates the parent of the given node/index.
     * @param[in] idx Index of the element.
     * @return Index of parent of the element.
     */
    constexpr size_t parent(size_t idx) const noexcept { return idx >> 1; }

    /**
     * Calculates the left child of the given node/index.
     * @param[in] idx Index of the element.
     * @return Index of left child of the element.
     */
    constexpr size_t left(size_t idx) const noexcept { return idx << 1; }

    /**
     * Calculates the right child of the given node/index.
     * @param[in] idx Index of the element.
     * @return Index of right child of the element.
     */
    constexpr size_t right(size_t idx) const noexcept { return idx << 1 | 1; }

    /**
     * Swaps the contents of the given indices.
     * @param[in] idx1 Index of first element.
     * @param[in] idx2 Index of second element.
     */
    inline void swap(size_t idx1, size_t idx2);

    /**
     * Expands the memory allocated by the heap if necessary.
     */
    void expand();

    /**
     * Sifts down the element at the given index such that the heap property
     * is maintained. Also known as heapify().
     * @param[in] idx Index of the target element.
     */
    void sift(size_t idx);

    /**
     * Rearranges the first @sz elements pointed to by @heap as a heap.
     */
    inline void build_heap();

    /**
     * Sorts the first @sz elements pointed to by @heap.
     * The heap property is no longer maintained.
     */
    void _sort();

public:
    /**
     * Constructor. Creates an empty PriorityQueue.
     */
    PriorityQueue();

    /**
     * Constructor. Creates an PriorityQueue from a C-style range
     * (Pointer to the beginning of a range and number of elements).
     */
    PriorityQueue(T* begin, int size) noexcept;

    /**
     * Constructor. Creates an PriorityQueue from a C++-style range
     * (The beginning and past-the-end iterators).
     */
    template <class RandomIt>
    PriorityQueue(RandomIt begin, RandomIt end) noexcept;

    /**
     * Destructor. Frees allocated memory if any.
     */
    ~PriorityQueue() noexcept;

    /**
     * Indicates whether the PriorityQueue is empty (has no elements).
     * @return Whether the PriorityQueue is empty.
     */
    inline bool empty() const noexcept;

    /**
     * Gives the current size of the PriorityQueue (number of elements).
     * @return Current size of the PriorityQueue.
     */
    inline size_t size() const noexcept;

    /**
     * Inserts an element into the PriorityQueue.
     * @param[in] value The element to be inserted.
     */
    void insert(T value);

    /**
     * Gives the current top element of the PriorityQueue.
     * @return The top element of the PriorityQueue.
     */
    T peek() const;

    /**
     * Removes the current top element of the PriorityQueue.
     * @return The top element of the PriorityQueue.
     */
    T remove();

    /**
     * Sort the range using heap-sort [begin, end) (C++-style).
     */
    template <typename RandomIt>
    friend void sort(RandomIt begin, RandomIt end);

    /**
     * Sort the range using heap-sort [begin, begin + size) (C-style).
     */
    template <typename P>
    friend void sort(P* begin, int size);
};

#include "priority_queue.tcc"
