#pragma once
#include "pch.h"
#include "Sort.h"
#include "Other.h"
#include "UnitTests.h"

void Tests::BuildHeap()
{
    Utility::Timer t(__func__);
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    auto compareValues = [](int a, int b) { return a < b; };
    Heap heap1(vec, compareValues);
    std::vector<int> vec2 = { 5, 4, 2, 1, 3 };
    Heap result(vec2, compareValues);
    Verify::IsTrue(heap1 == result, " heap was built incorrectly.");
}

void Tests::QuickSortTest()
{
    //ToDo
    Utility::Timer t(__func__);
    std::vector<int> vec = { 5, 4, 3, 2, 1 };
    std::cout << "Before sort: " << vec << std::endl;
    auto compareValues = [](int a, int b) { return a > b; };
    QuickSort(vec, compareValues);
    std::cout << "After sort: " << vec << std::endl;
}
