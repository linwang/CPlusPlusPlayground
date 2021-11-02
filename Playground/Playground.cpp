// Playground.cpp : This file contains the 'main' function. Program execution begins and ends there.
#pragma once
#include "pch.h"
#include "UnitTests.h"
#include "Exercises.h"


int main()
{
    //Tests::BuildHeap();
    //Tests::RemoveRoot();
    //Exercises::Concurrency::ThreadsBasic();
    //Exercises::Concurrency::ThreadsParams();
    //Exercises::Concurrency::AsyncBasic();
    //Exercises::Concurrency::PromiseAndFuture();
    //Exercises::Concurrency::ConiditionVariables();
    Exercises::DataStructures::Array();
    Exercises::DataStructures::Deque();
    Exercises::Misc();
    Exercises::DataStructures::String();
    Exercises::DataStructures::BinaryTree();
    Exercises::CodingInterviews::IsUniqueString();
    char name[256];
    std::cin.getline(name, 256);
}