#pragma once
#include "pch.h"
#include "Sort.h"

std::map<std::string, void (*)(std::vector<int>&, bool(*)(int, int))> GetSortMethods()
{
    std::map<std::string, void(*)(std::vector<int>&, bool(*)(int, int))> sortMethods =
    {
        {"Insertion", InsertionSort},
        {"Heap", HeapSort},
        {"Merge", MergeSort},
        {"Quick", QuickSort},
    };
    return sortMethods;
}

void InsertionSort(std::vector<int>& vec, bool(*compareValues)(int, int))
{
    if (vec.size() < 2) return;

    //loop until no more unsorted array
    for (unsigned int ui = 1; ui < vec.size(); ui++)
    {
        //add unsorted item into sorted array
        for (unsigned int si = ui; si > 0; si--)
        {
            if (compareValues(vec[si - 1], vec[si]))
            {
                auto temp = vec[si];
                vec[si] = vec[si - 1];
                vec[si - 1] = temp;
            }
        }
    }
}

void MergeSort(std::vector<int>& vec, bool(*compareValues)(int, int))
{
    if (vec.size() < 2) return;

    const int mid = vec.size()/2;
    std::vector<int> vec1(mid); 
    std::copy(vec.begin(), vec.begin() + mid, vec1.begin());
    std::vector<int> vec2(vec.size() - mid);
    std::copy(vec.begin() + mid, vec.end(), vec2.begin());
    MergeSort(vec1, compareValues);
    MergeSort(vec2, compareValues);

    //merge two arrays
    auto cItr1 = vec1.begin();
    auto cItr2 = vec2.begin();
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        if ((cItr2 != vec2.end()) && 
            ((cItr1 == vec1.end()) || compareValues(vec1.front(), vec2.front())))
        {
            vec[i] = *cItr2;
            cItr2++;
        }

        else
        {
            vec[i] = *cItr1;
            cItr1++;
        }
    }
}
void Heap::swap(const int iA, const int iB)
{
    if (iA < 0) return;
    if (iB < 0) return;
    if (iA == iB) return;

    int temp = m_vec[iA];
    m_vec[iA] = m_vec[iB];
    m_vec[iB] = temp;
}
//for each item, add item to the end of the binary tree
//compare item to its parent, swap if it is bigger
//continue until no parent
void Heap::buildHeap()
{
    for (int i = 0; i < m_size; i++)
    {
        int iCurrent = i;
        std::optional<int> iParent = getParentIndex(iCurrent);
        while (iParent.has_value()) {

            if (m_compareValues(m_vec[iCurrent], m_vec[iParent.value()]))
            {
                swap(iCurrent, iParent.value());
                iCurrent = iParent.value();
                iParent = getParentIndex(iCurrent);
            }
            else
                break;
        }
    }
}
std::optional<int> Heap::getParentIndex(const int iChild)
{
    if (iChild < 1) return {};
    int iParent;
    if (iChild % 2 == 1)//LChild 
    {
        iParent = iChild / 2;
    }
    else //RChild
    {
        iParent = iChild / 2 - 1;
    }
    if (iParent > -1)
        return iParent;
    return {};
}
std::optional<int> Heap::getLChildIndex(const int iParent)
{
    if (iParent < 0) return {};
    int iLChild = iParent * 2 + 1;
    if (iLChild < m_size) return iLChild;
    return {};
}
std::optional<int> Heap::getRChildIndex(const int iParent)
{
    auto iLChild = getLChildIndex(iParent);
    if (iLChild.has_value())
    {
        int iRChild = iLChild.value() + 1;
        if (iRChild < m_size) return iRChild;
    }
    return {};
}

std::ostream& operator<<(std::ostream& os, const Heap& heap)
{
    os << "{ ";
    for (int i = 0; i < heap.m_size; i++)
    {
        os << heap.m_vec[i] << " ";
    }
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& intVec)
{
    os << "{ ";
    for (unsigned int i = 0; i < intVec.size(); i++)
    {
        os << intVec[i] << " ";
    }
    os << "}";
    return os;
}
std::ostream& operator<<(std::ostream& os, const std::deque<int>& deq)
{
    os << "{ ";
    for (auto& v : deq)
        os << v << " ";
    os << "}";

    return os;
}

bool Heap::operator==(const Heap& h2)
{
    if (m_size != h2.m_size) return false;
    for (int i = 0; i < m_size; i++)
    {
        if (m_vec[i] != h2.m_vec[i])
            return false;
    }
    return true;
}
void Heap::sort()
{
    while (m_size > 1)
    {
        removeRoot();
    }
}
void HeapSort(std::vector<int>& vec, bool(*compareValues)(int, int))
{
    //create a Heap structure, keep extracting the root item and heapify until last item
    Heap heap(vec, compareValues);
    heap.sort();
}

std::optional<int> Heap::removeRoot()
{
    if (m_size < 0) return {};
    int root = m_vec[0];
    swap(0, m_size - 1);
    m_size--;
    heapify(0);
    return root;
}
void Heap::heapify(int i)
{
    //compare vec[i] to its children, if no swap, return
    //if swap, compare swapped child to its children, if no swap, return
    //continue until child is invalid
    auto checkValue = [&](const std::optional<int>& iChild) {
        if (iChild.has_value())
        {
            if (!m_compareValues(m_vec[i], m_vec[iChild.value()]))
            {
                swap(i, iChild.value());
                heapify(iChild.value());
                return;
            }
        }
        else
            return;
        };
    checkValue(getLChildIndex(i));
    checkValue(getRChildIndex(i));
}

/// <summary>
/// Give an array of numbers. 
/// If 0 or 1 numbers in array, it's sorted, return.
/// If 2 numbers in array, swap if num1 > num2, return.
/// Other, do the following.
/// Choose a pivot. Swap the pivot with the last number in the array.
/// Start from the beginning of the array, go right, for each number, compare to the pivot. Stop when a
/// number > pivot is found. iGreaterThanPivot
/// Start from the item before the pivot, go left, for each number, compare to the pivot. Stop when a
/// number < pivot is found. iLessThanPivot
/// Swap the values at iGreaterThanPivot with iLessThanPivot.
/// Continue the compare and swap until iGreaterThanPivot > iLessThanPivot, swap value at iGreaterThanPivot
/// with the pivot. 
/// Now recursively sort array before pivot and after pivot.
/// </summary>
/// <param name="vec">a vector of integers</param>
void QuickSort(std::vector<int>& vec, bool(*compareValues)(int, int))
{
    auto swap = [&vec](const int iA, const int iB) {
        if (iA < 0) return;
        if ((unsigned int) iA >= vec.size()) return;
        if (iB < 0) return;
        if ((unsigned int) iB >= vec.size()) return;
        if (iA == iB) return;

        int temp = vec[iA];
        vec[iA] = vec[iB];
        vec[iB] = temp;
    };
    auto getPivotIndex = [&vec](const int iBeg, const int iEnd)
    {
        if (iBeg > iEnd) return iEnd;
        auto iMid = (iBeg + iEnd) / 2;
        auto isFirstMidValue = [](const int a, const int b, const int c)
        {
            if (((a <= b) and (a >= c)) or ((a >= b) and (a <= c)))
                return true;
            return false;
        };

        if (isFirstMidValue(vec[iBeg], vec[iMid], vec[iEnd])) return iBeg;
        if (isFirstMidValue(vec[iMid], vec[iBeg], vec[iEnd])) return iMid;
        return iEnd;
    };
    std::function<void(int, int)> quickSortCore = [&](const int iBeg, const int iEnd)
    {
        int size = iEnd - iBeg + 1;
        if (size < 2) return;
        if (size == 2)
        {
            if (compareValues(vec[iBeg], vec[iBeg + 1])) swap(iBeg, iBeg + 1);
            return;
        }
        int iPivot = getPivotIndex(iBeg, iEnd);
        int vPivot = vec[iPivot];
        swap(iPivot, iEnd);
        int iLeft = iBeg;
        int iRight = iEnd - 1;
        while (true)
        {
            while ((iLeft < iEnd) and (compareValues(vPivot, vec[iLeft]))) iLeft++;
            while ((iRight > iBeg) and (compareValues(vec[iRight], vPivot))) iRight--;
            if (iLeft > iRight) break; 
            swap(iLeft, iRight);
            iLeft++;
            iRight--;
        }
        swap(iLeft, iEnd);
        quickSortCore(iBeg, iLeft - 1);
        quickSortCore(iLeft + 1, iEnd);
    };
    quickSortCore(0, vec.size() - 1);
}
