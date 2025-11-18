#include "expense.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

std::string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    auto timet = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timet), "%Y-%m-%d");
    return ss.str();
}

std::vector<Expense> loadExpenses(const std::string& filename) {
    std::vector<Expense> expenses;
    std::ifstream file(filename);
    if (!file.is_open()) return expenses;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Expense e;
        char delim;
        std::getline(ss, line, '|'); e.id = std::stoi(line);
        std::getline(ss, e.date, '|');
        std::getline(ss, e.description, '|');
        std::getline(ss, line, '|'); e.amount = std::stod(line);
        std::getline(ss, e.category, '|');
        expenses.push_back(e);
    }
    return expenses;
}

void saveExpenses(const std::vector<Expense>& expenses, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& e : expenses) {
        file << e.id << "|" 
             << e.date << "|" 
             << e.description << "|" 
             << std::fixed << std::setprecision(2) << e.amount << "|" 
             << e.category << "\n";
    }
}
