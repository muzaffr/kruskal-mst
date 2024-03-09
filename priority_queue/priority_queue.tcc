#include <stdlib.h>     /* malloc, realloc, free, exit, NULL */
#include <string.h>     /* memcpy */
#include <stdexcept>    /* out_of_range, runtime_error */
#include "priority_queue.hpp"

template <class T>
inline void PriorityQueue<T>::swap(size_t idx1, size_t idx2)
{
    auto temp = heap[idx1];
    heap[idx1] = heap[idx2];
    heap[idx2] = temp;
}

template <class T>
void PriorityQueue<T>::expand()
{
    if (_from_range) {
        auto old_heap = heap;
        _from_range = false;
        heap = (T *) malloc(cap * sizeof(T));
        memcpy(heap, old_heap, cap * sizeof(T));
    }
    while (sz + 1 >= cap) {
        cap *= 2;
        heap = (T *) realloc(heap, cap * sizeof(T));
        if (heap == NULL) {
            throw std::runtime_error("null pointer exception");
        }
    }
}

template <class T>
void PriorityQueue<T>::sift(size_t idx)
{
    size_t l = left(idx), r = right(idx), mx = idx;
    if (l <= sz and heap[l] > heap[idx])
        mx = l;
    if (r <= sz and heap[r] > heap[mx])
        mx = r;
    if (mx != idx) {
        swap(idx, mx);
        sift(mx);
    }
}

template <class T>
inline void PriorityQueue<T>::build_heap()
{
    for (size_t i = sz / 2; i >= 1; --i) {
        sift(i);
    }
}

template <class T>
void PriorityQueue<T>::_sort()
{
    for (size_t i = sz; i >= 2; --i) {
        swap(1, i);
        --sz;
        sift(1);
    }
}


template <class T>
PriorityQueue<T>::PriorityQueue()
{
    _from_range = false;
    sz = 0;
    cap = 1;
    heap = (T *) malloc(cap * sizeof(T));
}

template <class T>
PriorityQueue<T>::PriorityQueue(T* begin, int size) noexcept
{
    _from_range = true;
    sz = size;
    cap = sz + 1;
    heap = begin;
    --heap;
    build_heap();
}

template <class T>
template <class RandomIt>
PriorityQueue<T>::PriorityQueue(RandomIt begin, RandomIt end) noexcept
{
    _from_range = true;
    sz = end - begin;
    cap = sz + 1;
    heap = begin.operator->();
    --heap;
    build_heap();
}

template <class T>
PriorityQueue<T>::~PriorityQueue() noexcept
{
    if (not _from_range)
        free(heap);
    heap = NULL;
}

template <class T>
inline bool PriorityQueue<T>::empty() const noexcept
{
    return sz == 0;
}

template <class T>
inline size_t PriorityQueue<T>::size() const noexcept
{
    return sz;
}

template <class T>
void PriorityQueue<T>::insert(T value)
{
    expand();
    sz += 1;
    auto idx = sz;
    heap[idx] = value;
    while (idx > 1 and heap[parent(idx)] < heap[idx]) {
        swap(idx, parent(idx));
        idx = parent(idx);
    }
}

template <class T>
T PriorityQueue<T>::peek() const
{
    if (sz == 0) {
        throw std::out_of_range("empty container");
    }
    return heap[1];
}

template <class T>
T PriorityQueue<T>::remove()
{
    T element = this->peek();
    heap[1] = heap[sz];
    sift(1);
    --sz;
    return element;
}

template <typename RandomIt>
void sort(RandomIt begin, RandomIt end)
{
    auto x = *begin;
    PriorityQueue<decltype(x)> pq(begin, end);
    // PriorityQueue<decltype(*begin)> pq(begin, end);
    pq._sort();
}

template <typename P>
void sort(P* begin, int size)
{
    PriorityQueue<P> pq(begin, size);
    pq._sort();
}
