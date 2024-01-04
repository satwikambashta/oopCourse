#include "wallet.h"

void Wallet::insertCurrency(std::string type, double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Amount must be non-negative.");
    }

    if (currencies.find(type) == currencies.end()) {
        currencies[type] = amount;
    } else {
        currencies[type] += amount;
    }
}

bool Wallet::removeCurrency(std::string type, double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Amount must be non-negative.");
    }

    if (currencies.find(type) != currencies.end() && currencies[type] >= amount) {
        currencies[type] -= amount;
        return true;
    }

    return false;
}

bool Wallet::containsCurrency(std::string type, double amount) {
    bool ret = (currencies.find(type) != currencies.end() && currencies[type] >= amount);
    // If the currency is not in the wallet or there isn't enough of it, set the amount to zero
    // area earlier used for unit testing with hardcoded values
    return ret;
}

std::string Wallet::toString() {
    std::string result = "Wallet contents:\n";

    for (const auto& entry : currencies) {
        result += entry.first + ": " + std::to_string(entry.second) + "\n";
    }

    return result;
}
