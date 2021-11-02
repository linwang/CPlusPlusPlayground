#pragma once
#include "pch.h"
#include "Sort.h"
#include "Other.h"
#include "MyString.h"
#include "MyBinaryTree.h"
#include "Exercises.h"

void Exercises::Concurrency::ThreadsBasic()
{
    auto cThreads = std::thread::hardware_concurrency();
    std::cout << "Threads available: " << cThreads <<std::endl;
    if (cThreads == 0) return;
    

    std::mutex mu;
    using namespace std::chrono_literals;
    auto work = [&mu]() {
        std::lock_guard<std::mutex> locker(mu);
        std::cout << "Current thread ID: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(100ms);
        return std::this_thread::get_id();
    };

    std::thread t1(work);
    t1.detach();
    Verify::IsFalse(t1.joinable(), "Threads cannot join once detached.");

    std::thread t2(work);
    Verify::IsTrue(t2.joinable(), "Threads can join after creation.");
    t2.join();
    Verify::IsTrue(t2.get_id() == std::thread::id(), "Thread exits after joining.");
}
void Exercises::Concurrency::ThreadsParams()
{
    std::mutex mu;
    auto work = [&mu](unsigned int index, std::promise<int> pm) {
        std::lock_guard locker(mu);
        std::cout << "Started Thread: " << index << std::endl;
        pm.set_value(index);//Use promise and future to capture function return
    };
    auto cThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(cThreads);
    std::vector<std::future<int>> futures;
    futures.reserve(cThreads);
    for (unsigned int i = 0; i < cThreads; i++)
    {
        std::promise<int> pm;
        futures.push_back(pm.get_future());
        threads.push_back(std::thread(work, i, std::move(pm)));
    }
    for (unsigned int i = 0; i < cThreads; i++)
    {
        threads[i].join();
        std::lock_guard locker(mu);
        std::cout << "Threads " << i << " returns " << futures[i].get() << std::endl;
    }
}
void Exercises::Concurrency::AsyncBasic() {
    using namespace Classes;
    //note async allows work function to return and also by reference parameter passing
    std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;
    Account myAccount("Lin", 100);
    std::future<ErrorCode> fn = std::async(std::launch::async | std::launch::deferred, &Account::Save, &myAccount, 100);
    auto err = fn.get();//waits for return value
    Verify::IsTrue(err == ErrorCode::none);
    std::future<ErrorCode> fn2 = std::async(std::launch::deferred, &Account::TakeOut, &myAccount, 100);
    //deferred executes worker on the main thread when future.get() is called
    auto err2 = fn2.get();
    Verify::IsTrue(err2 == ErrorCode::none);
    auto work = []() {
        std::cout << "I don't have a return value. My thread id is " << std::this_thread::get_id() << std::endl; 
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    };
    std::future<void> fn3 = std::async(std::launch::async, work);
    fn3.get();//waits for work to finish even if work is void =)
    std::cout << "Hello @_@" << std::endl;
}
void Exercises::Concurrency::PromiseAndFuture()
{
    //Provides a way for two threads to communicate asynchronously
    //promise can set the value, promise's future can wait and get the value
    std::promise<int> p;
    std::future<int> f = p.get_future();
    p.set_value(5);
    f.wait();
    if (f.valid())
    {
        std::cout << "Waited for future value " << f.get() <<std::endl;
    }
}
void Exercises::Concurrency::ConiditionVariables()
{
    int sharedCounter = 0;
    std::condition_variable cond;
    std::mutex mu;
    auto producer = [&sharedCounter, &cond, &mu]() {
        std::unique_lock locker(mu);
        std::cout <<"Producer id: " << std::this_thread::get_id() << std::endl; 
        sharedCounter++; 
        std::cout << "Producer increases counter to " << sharedCounter << std::endl;
        locker.unlock();
        cond.notify_one();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    };
    auto consumer = [&sharedCounter, &cond, &mu]() {
        std::unique_lock locker(mu);
        cond.wait(locker, [&sharedCounter]() {return sharedCounter > 0; });
        std::cout << "Consumer id: " << std::this_thread::get_id() << std::endl; 
        sharedCounter--; 
        std::cout << "Consumer decreases counter to " << sharedCounter << std::endl;
        locker.unlock();
    };

    std::thread t2(consumer);
    std::thread t1(producer);
    t2.join();
    t1.join();
}
void Exercises::DataStructures::Array(){
    std::array<int, 5> arr = { 3, 5, 2, 5, 1 };
    std::cout << arr << std::endl;
    int index = 0;
    std::cout << ".at(index): " << arr.at(index) << " is the same as [index]: " << arr[index] <<", except .at does bounds check"<< std::endl;
    std::cout << ".back(): " << arr.back() << "; .front(): " << arr.front() << std::endl;

    std::cout << "Iterate through the array: ";
    for (auto it = arr.begin(); it < arr.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Fill array via .fill(val) ";
    arr.fill(1);
    std::cout << arr << std::endl;
}
void Exercises::DataStructures::Deque()
{
    std::deque deq = { 1, 2, 3 };
    std::cout << "deq = " << deq << std::endl;
    deq.push_front(0);
    deq.push_back(4);
    std::cout << "Added to beg/end. deq = " << deq << std::endl;
    auto it = deq.erase(deq.begin());
    std::cout << *it << " is now the first of deq " << deq << std::endl;
}
void Exercises::DataStructures::String() {
    MyString s = "hi";
    MyString t = "oh";
    MyString a = NULL;
    std::cout << a << std::endl;
    a = a;
    a = std::move(a);
    a = s;
    a += t;
    s += t;
    if(a == s)
        std::cout << a << std::endl;
    if (t != s)
        std::cout << s << std::endl;
}
void Exercises::DataStructures::BinaryTree()
{
    auto aPtr = std::make_shared<Node<int>>(-1);
    auto bPtr = std::make_shared<Node<int>>(0);
    auto cPtr = std::make_shared<Node<int>>(1);
    aPtr->setLeftChild(bPtr);
    aPtr->setRightChild(cPtr);
    auto dPtr = aPtr;
    aPtr = dPtr->getLeftChild();
    if (aPtr->getLeftChild() == nullptr) 
        std::cout << "I don't have a left child." << std::endl;
    std::vector<int> vec = { 1, 2, 3, 4 };
    MyBinarySearchTree<int> tree = vec;
}
void Exercises::Misc()
{

    Classes::Point a = { 1, -1 };
    Classes::Point b = { -1, 1 };
    std::cout << a + b << std::endl;

    int x = 0;
    std::function<void()> tryMutable = [=]() mutable { x++;};
    //capture-by-value var is not changeable unless declared mutable
    //change stays inside lambda only
    tryMutable();
    std::cout << "x = " << x << std::endl;

    std::vector<int> vec = { 2, -2, 1, 2, 5, 3 };
    std::cout << vec << std::endl;
    auto sortMethods = GetSortMethods();
    auto compareValues = [](int a, int b) {return a < b; };
    for (auto const& sort : sortMethods)
    {
        std::vector<int> copy = vec;
        sort.second(copy, compareValues);
        std::cout << sort.first << ": " << copy << std::endl;
    }
}
void Exercises::CodingInterviews::IsUniqueString()
{
    //solution 1, compare each character
    std::string s = "Hi, I am a string.";
    bool isUnique = true;
    for (int i = 0; i < s.length() && isUnique; i++)
    {
        for (int j = i + 1; j < s.length(); j++)
        {
            if (s[i] == s[j])
            {
                isUnique = false;
                break;
            }
        }
    }
    //solution 2, sort the string and compare only adjacent
}
