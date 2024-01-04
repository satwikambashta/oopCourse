#pragma once

#include <iostream>
#include <map>

class Wallet
{
private:
    std::map<std::string, double> currencies;

public:
    void insertCurrency(std::string type, double amount);
    bool removeCurrency(std::string type, double amount);
    bool containsCurrency(std::string type, double amount);
    std::string toString();
};