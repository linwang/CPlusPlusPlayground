#pragma once
#include "pch.h"

namespace Classes
{
    enum class ErrorCode
    {
        none, lessThanZero, insufficientBalance
    };
    std::ostream& operator<<(std::ostream& os, const ErrorCode& err);

    class Account
    {
    private:
        std::string name;
        double balance;
    public:
        friend std::ostream& operator<<(std::ostream& os, const Account& a);
        Account() = delete;
        Account(const std::string& name, double initBalance) :
            name(name), balance(initBalance)
        {
            std::cout << "created" << std::endl;
        }
        Account(Account& a)
        {
            std::cout << "copied" << std::endl;
            name = a.name;
            balance = a.balance;
        }
        Account(Account&& a) noexcept
        {
            std::cout << "moved" << std::endl;
            name = std::move(a.name);
            balance = a.balance;
        }
        ErrorCode Save(double amount)
        {
            if (amount < 0) return ErrorCode::lessThanZero;
            balance += amount;
            std::cout << std::this_thread::get_id() << std::endl;
            std::cout << "Save " << amount << ": " << *this << std::endl;
            return ErrorCode::none;
        }
        ErrorCode TakeOut(double amount)
        {
            if (amount < 0) return ErrorCode::lessThanZero;
            if (amount > balance) return ErrorCode::insufficientBalance;
            balance -= amount;
            std::cout << std::this_thread::get_id() << std::endl;
            std::cout << "Take out " << amount << ": " << *this << std::endl;
            return ErrorCode::none;
        }
        double GetBalance() const
        {
            return balance;
        }
        std::string GetName() const
        {
            return name;
        }
    };

    class Point
    {
        mutable int debug_counter;//allows variable to be changeable in a const function
        float m_x;
        float m_y;
    public:
        Point() = delete;
        Point(float x, float y) : m_x(x), m_y(y),debug_counter(0) {};
        float getX() const { debug_counter++; return m_x; }
        float getY() const { debug_counter++; return m_y; }
        Point operator+(const Point& b)
        {
            float x = m_x + b.getX();
            float y = m_y + b.getY();

            return { x, y };
        }
        friend std::ostream& operator<< (std::ostream& os, const Point& p)
        {
            os << "{ " << p.getX() << " , " << p.getY() << " }";
            return os;
        }
    };
}
namespace Verify
{
    void IsTrue(bool a, const std::string& errMsg = "");
    void IsFalse(bool a, const std::string& errMsg = "");
}
namespace Utility
{
    class Timer
    {
    private:
        std::chrono::time_point <std::chrono::steady_clock> start;
        std::string signature;
    public:
        Timer(const std::string& str)
        {
            std::cout << str << " starts." << std::endl;
            start = std::chrono::steady_clock::now();
            signature = str;
        }
        ~Timer()
        {
            auto end = std::chrono::steady_clock::now();
            auto duration = end - start;
            std::cout << signature << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()
                << " milliseconds." << std::endl;
        }
    };
}