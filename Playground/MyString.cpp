#pragma once
#include "pch.h"
#include "MyString.h"

void MyString::cleanUp()
{
    delete[] m_buf;
    m_size = 0;
}
MyString::MyString() : m_buf(nullptr), m_size(0) {};
MyString::MyString(const char* const buf) : MyString()
{
    if (!buf) return;
    m_size = strlen(buf);
    m_buf = new char[m_size + 1];
    strcpy_s(m_buf, m_size + 1, buf);
}
MyString::MyString(const MyString& str)
{
    m_size = str.m_size;
    m_buf = new char[m_size + 1];
    strcpy_s(m_buf, m_size + 1, str.m_buf);
}
MyString::MyString(MyString&& str) noexcept
{
    m_size = str.m_size;
    m_buf = str.m_buf;
    str.m_buf = nullptr;
    str.m_size = 0;
}
MyString::~MyString() { cleanUp(); }
unsigned int MyString::size() { return m_size; }

MyString& MyString::operator=(const MyString& str) noexcept
{
    if (&str == this) return *this;
    cleanUp();
    m_size = str.m_size;
    m_buf = new char[m_size + 1];
    strcpy_s(m_buf, m_size + 1, str.m_buf);
    return *this;
}

MyString& MyString::operator=(MyString&& str) noexcept
{
    if (&str == this) return *this;
    cleanUp();
    m_size = str.m_size;
    m_buf = str.m_buf;
    str.m_buf = nullptr;
    str.m_size = 0;
    return *this;
}

const MyString MyString::operator+(const MyString& str)
{
    MyString result;
    result = *this;
    result += str;
    return result;
}

MyString& MyString::operator+=(const MyString& str)
{
    if (m_size == 0)
    {
        *this = str;
    }
    else
    {
        unsigned int tSize = m_size + str.m_size;
        char* tBuf = new char[tSize + 1];
        strcpy_s(tBuf, m_size + 1, m_buf);
        strcpy_s(tBuf + m_size, str.m_size + 1, str.m_buf);
        cleanUp();
        m_size = tSize;
        m_buf = tBuf;
    }
    return *this;
}
std::ostream& operator<<(std::ostream& os, const MyString& str)
{
    if (str.m_size > 0)
        os << str.m_buf;
    return os;
}
bool MyString::operator==(const MyString& str)
{
    if (this == &str) return true;

    if (m_size != str.m_size) return false;
    if (!(m_buf) && !(str.m_buf)) return true;
    if (!m_buf) return false;
    if (!str.m_buf) return false;
    for (unsigned int i = 0; i < m_size; i++)
    {
        if (m_buf[i] != str.m_buf[i]) return false;
    }
    return true;
}
bool MyString::operator!=(const MyString& str)
{
    return !(*this == str);
}