#include <iostream>
#include <vector>
#include <algorithm>

enum class OrderBookType
{
    bid,
    ask
};

class OrderBookEntry
{
public:
    std::string timestamp;
    std::string symbol;
    OrderBookType orderType;
    double price;
    double quantity;
    static double getHighPrice(const std::vector<OrderBookEntry> &orders);
    static double getLowPrice(const std::vector<OrderBookEntry> &orders);
    static double getVWAP(const std::vector<OrderBookEntry> &orders);

    OrderBookEntry(std::string timestamp, std::string symbol, OrderBookType orderType, double price, double quantity)
        : timestamp(timestamp), symbol(symbol), orderType(orderType), price(price), quantity(quantity) {}
};

double computeAveragePrice(const std::vector<OrderBookEntry> &entries)
{
    double total = 0.0;
    for (const auto &entry : entries)
    {
        total += entry.price;
    }
    return entries.empty() ? 0.0 : total / entries.size();
}

double computeLowPrice(const std::vector<OrderBookEntry> &entries)
{
    double min = 0.0;
    if (entries.empty())
        return min;
    min = std::min_element(entries.begin(), entries.end(), [](const auto &a, const auto &b)
                           { return a.price < b.price; })
              ->price;
    return min;
}

double computeHighPrice(const std::vector<OrderBookEntry> &entries)
{
    double max = 0.0;
    if (entries.empty())
        return max;
    max = std::max_element(entries.begin(), entries.end(), [](const auto &a, const auto &b)
                           { return a.price < b.price; })
              ->price;
    return max;
}

double computePriceSpread(const std::vector<OrderBookEntry> &entries)
{
    double diff = 0.0;
    if (entries.empty())
        return diff;
    double lowPrice = computeLowPrice(entries);
    double highPrice = computeHighPrice(entries);
    diff = highPrice - lowPrice;
    return diff;
}

double OrderBookEntry::getVWAP(const std::vector<OrderBookEntry> &orders)
{
    double totalValue = 0.0;
    double totalVolume = 0.0;

    for (const auto &order : orders)
    {
        totalValue += order.price * order.quantity;
        totalVolume += order.quantity;
    }

    return (totalVolume != 0.0) ? totalValue / totalVolume : 0.0;
}

int main()
{
    std::vector<OrderBookEntry> orderBook = {
        {"2023/12/17 12:21:24.986793", "ETH/BTC", OrderBookType::bid, 0.02186299, 0.1},
        {"2023/12/17 07:04:54.684594", "ETH/BTC", OrderBookType::bid, 0.02568300, 0.2},
        {"2023/12/17 09:45:30.789012", "ETH/BTC", OrderBookType::ask, 0.02215476, 0.15},
        {"2023/12/17 15:32:10.123456", "ETH/BTC", OrderBookType::ask, 0.02450987, 0.18},
        {"2023/12/19 18:10:45.567890", "ETH/BTC", OrderBookType::ask, 0.02348765, 0.12},
        {"2023/12/19 11:15:40.987654", "ETH/BTC", OrderBookType::bid, 0.02234567, 0.25},
        {"2023/12/19 14:02:34.567890", "ETH/BTC", OrderBookType::bid, 0.02487654, 0.3},
        {"2023/12/19 17:30:15.432109", "ETH/BTC", OrderBookType::ask, 0.02345678, 0.22},
        {"2023/12/19 08:20:50.654321", "ETH/BTC", OrderBookType::bid, 0.02456789, 0.15},
        {"2023/12/19 13:40:55.876543", "ETH/BTC", OrderBookType::ask, 0.02298765, 0.2},
    };

    for (const auto &entry : orderBook)
    {
        std::cout << entry.timestamp << " " << entry.symbol << " " << static_cast<int>(entry.orderType)
                  << " " << entry.price << " " << entry.quantity << std::endl;
    }

    std::cout << "Average Price: " << computeAveragePrice(orderBook) << std::endl;
    std::cout << "Lowest Price: " << computeLowPrice(orderBook) << std::endl;
    std::cout << "Highest Price: " << computeHighPrice(orderBook) << std::endl;
    std::cout << "Price Spread: " << computePriceSpread(orderBook) << std::endl;
    std::cout << "VWAP: " << OrderBookEntry::getVWAP(orderBook) << std::endl;

    return 0;
}
