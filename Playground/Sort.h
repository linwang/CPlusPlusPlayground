#pragma once
#include "pch.h"

std::map<std::string, void (*)(std::vector<int>&, bool(*)(int, int))> GetSortMethods();

/*
Insertion sort: Sort an array of items in place. Left side of the array is sorted and
right side is unsorted. Left side of the array starts with element 1. Right side starts with element 2
to the last item. Compare the first item of the rArray with the last item of the lArray. Swap them as
neccessary. Keep swapping until it is in the right place. lArray now has 2 items and rArray has 3 to
the last item. Keep doing this until rArray is empty. O(n^2)
*/
void InsertionSort(std::vector<int>& vec, bool(*compareValues)(int, int));

/* Merge sort: Dividend and conquer sort. Continue to divide array into sub-arrays until sub-array sizes reaches
* 1 or 0. Then, start to merge the sub-arrays back together until a sorted array is formed. O(n*log(n))
* To merge two unsorted arrays, start from the beginning of each subarray, compare the two numbers, pick one (depending
* on desired order) and place at the end of the sorted array. Finish when subarrays' sizes reach 0
*/
void MergeSort(std::vector<int>& vec, bool(*compareValues)(int, int));

template <std::size_t SIZE>
std::ostream& operator<<(std::ostream& os, const std::array<int, SIZE>& arr)
{
    os << "arr = { ";
    for (auto& v : arr)
    {
        os << v << " ";
    }
    os << "}";

    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& intVec);

std::ostream& operator<<(std::ostream& os, const std::deque<int>& deq);

class Heap
{
private:
    std::vector<int>& m_vec;
    int m_size;
    bool(*m_compareValues)(int, int);
    void swap(const int iA, const int iB);
    void buildHeap();
    void heapify(int i);
    std::optional<int> getParentIndex(const int iChild);
    std::optional<int> getLChildIndex(const int iParent);
    std::optional<int> getRChildIndex(const int iParent);
    std::optional<int> removeRoot();

public:
    Heap(std::vector<int>& vec, bool(*compareValues)(int, int)) : m_vec(vec), m_size(vec.size()), m_compareValues(compareValues)
    {
        buildHeap();
    }
    int getSize() { return m_size; }
    void sort();
    friend std::ostream& operator<<(std::ostream& os, const Heap& heap);
    bool operator==(const Heap& h2);
};
void HeapSort(std::vector<int>& vec, bool(*compareValues)(int, int));
void QuickSort(std::vector<int>& vec, bool(*compareValues)(int, int));

