#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class HealthRecord {
public:
    int id;
    int age;
    std::string gender;
    int height;
    int weight;
    int ap_hi;
    int ap_lo;
    int cholesterol;
    int gluc;
    int smoke;
    int alco;
    int active;
    int cardio;

    HealthRecord(int _id, int _age, const std::string& _gender, int _height, int _weight,
                 int _ap_hi, int _ap_lo, int _cholesterol, int _gluc, int _smoke,
                 int _alco, int _active, int _cardio)
        : id(_id), age(_age), gender(_gender), height(_height), weight(_weight),
          ap_hi(_ap_hi), ap_lo(_ap_lo), cholesterol(_cholesterol), gluc(_gluc),
          smoke(_smoke), alco(_alco), active(_active), cardio(_cardio) {}
};

std::vector<std::string> tokenize(const std::string& csvLine, char separator) {
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end != std::string::npos);
    return tokens;
}

int main() {
    std::string csvFilename{"health_data.csv"};
    std::ifstream csvFile{csvFilename};
    std::string line;
    int validLines = 0;
    int totalAge = 0;
    int totalHeight = 0;

    if (csvFile.is_open()) {
        std::cout << "Opened file " << csvFilename << std::endl;

        std::vector<HealthRecord> healthRecords;

        while (std::getline(csvFile, line) ) {
            std::vector<std::string> tokens = tokenize(line, ',');

            try {
                HealthRecord record{
                    std::stoi(tokens[1]), std::stoi(tokens[2]), tokens[3], std::stoi(tokens[4]),
                    std::stoi(tokens[5]), std::stoi(tokens[6]), std::stoi(tokens[7]),
                    std::stoi(tokens[8]), std::stoi(tokens[9]), std::stoi(tokens[10]),
                    std::stoi(tokens[11]), std::stoi(tokens[12]), std::stoi(tokens[13])
                };

                healthRecords.push_back(record);
                totalAge += record.age;
                totalHeight += record.height;
                validLines++;
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
            //now to catch an exception
            //thannks
        }

        std::cout << "First 20 records:" << std::endl;
        int counter=0;
        for (const auto& record : healthRecords ) {
            std::string genders;
            if(record.gender =="0"){genders="male";}
            else{genders="female";}
            std::cout << "ID: " << record.id << ", Gender: " << genders
                      << ", Weight: " << record.weight << ", AP_HI: " << record.ap_hi
                      << ", AP_LO: " << record.ap_lo << ", Cholesterol: " << record.cholesterol << std::endl;
            counter++;
            if(counter>50)
                break;
        }

        double averageHeight = static_cast<double>(totalHeight) / healthRecords.size();
        double averageAge = static_cast<double>(totalAge) / healthRecords.size();
        std::cout << "Average Height: " << averageHeight << std::endl;
        std::cout << "Average Age: " << averageAge << std::endl;
        std::cout << "Total Number of Lines in the Dataset: " << validLines << std::endl;
    } else {
        std::cout << "Problem opening file " << csvFilename << std::endl;
    }

    csvFile.close();

    return 0;
}
