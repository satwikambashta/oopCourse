#include <iostream>
#include <map>

class Wallet {
private:
    std::map<std::string, double> currencies;

public:
    void insertCurrency(std::string type, double amount);
    bool removeCurrency(std::string type, double amount);
    bool containsCurrency(std::string type, double amount);
    std::string toString() const;
};

void Wallet::insertCurrency(std::string type, double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Amount must be non-negative.");
    }

    currencies[type] += amount;
}

bool Wallet::removeCurrency(std::string type, double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Amount must be non-negative.");
    }

    if (currencies[type] >= amount) {
        currencies[type] -= amount;
        return true;
    }

    return false;
}

bool Wallet::containsCurrency(std::string type, double amount) {
    bool ret = (currencies.find(type) != currencies.end() && currencies[type] >= amount);
    //area left for unit testing
    return ret;
}

std::string Wallet::toString() const {
    std::string result = "Wallet contents:\n";

    for (const auto& entry : currencies) {
        result += entry.first + ": " + std::to_string(entry.second) + "\n";
    }

    return result;
}

#include <iostream>

int main() {
    Wallet myWallet{};

    std::string currencyType;
    double amount;

    std::cout << "Enter currency type: ";
    std::cin >> currencyType;

    std::cout << "Enter amount to insert: ";
    std::cin >> amount;

    myWallet.insertCurrency(currencyType, amount);

    std::cout << myWallet.toString() << std::endl;

    std::cout << "Enter amount to remove: ";
    std::cin >> amount;

    if (myWallet.removeCurrency(currencyType, amount)) {
        std::cout << "Successfully removed " << amount << " " << currencyType << std::endl;
    } else {
        std::cout << "Failed to remove " << amount << " " << currencyType << std::endl;
    }

    std::cout << myWallet.toString() << std::endl;

    std::cout << "Enter amount to check in the wallet: ";
    std::cin >> amount;

    std::cout << "Checking if wallet contains at least " << amount << " " << currencyType << ": ";
    if (myWallet.containsCurrency(currencyType, amount)) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    return 0;
}
