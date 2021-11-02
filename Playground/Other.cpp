#pragma once
#include "pch.h"
#include "Other.h"

using namespace Classes;
std::ostream& Classes::operator<<(std::ostream& os, const ErrorCode& err)
{

    switch (err)
    {
        case ErrorCode::insufficientBalance:
            os << "Error: Insufficient funds!";
            break;
        case ErrorCode::lessThanZero:
            os << "Error: Cannot have negative balance!";
            break;
        case ErrorCode::none:
            os << "Success!";
            break;
        default:
            os << "Unknown error!";
    }
    return os;
}

std::ostream& Classes::operator<<(std::ostream& os, const Account& a)
{
    os << "Name: " << a.GetName() << ", Balance: " << a.GetBalance();
    return os;
}

void Verify::IsTrue(bool a, const std::string& errMsg)
{
    std::cout << "IsTrue::";
    if (a)
        std::cout << "PASS"<< std::endl;
    else
        std::cout << "FAIL: "<< errMsg << std::endl;
}
void Verify::IsFalse(bool a, const std::string& errMsg)
{
    std::cout << "IsFalse::";
    if (!a)
        std::cout << "PASS" << std::endl;
    else
        std::cout << "FAIL: " << errMsg << std::endl;
}