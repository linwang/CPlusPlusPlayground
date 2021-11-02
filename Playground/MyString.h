#pragma once
#include "pch.h"
/// <summary>
/// Write my own stl style string class. 
/// </summary>
class MyString
{
    char* m_buf;
    unsigned int m_size;
    void cleanUp();
public:
    MyString();
    MyString(const char* const buf);
    MyString(const MyString& str);
    MyString(MyString&& str) noexcept;
    ~MyString();
    unsigned int size();
    MyString& operator=(const MyString& str) noexcept;
    MyString& operator=(MyString&& str) noexcept;
    const MyString operator+(const MyString& str);
    MyString& operator+=(const MyString& str);
    bool operator==(const MyString& str);
    bool operator!=(const MyString& str);
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
};