#include "expense.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: expense-tracker <command> [args]\n";
        std::cerr << "Commands: add, list, summary, delete, update\n";
        return 1;
    }

    std::string command = argv[1];
    std::vector<Expense> expenses = loadExpenses("data/expenses.txt");
    const std::string filename = "data/expenses.txt";

    // Calculate next ID
    int nextId = 1;
    if (!expenses.empty()) {
        auto maxIt = std::max_element(expenses.begin(), expenses.end(),
            [](const Expense& a, const Expense& b) { return a.id < b.id; });
        nextId = maxIt->id + 1;
    }

    if (command == "add") {
        if (argc < 6) {
            std::cerr << "Usage: add --description \"text\" --amount <number> [--category \"cat\"]\n";
            return 1;
        }
        std::string desc = argv[3];
        double amount = std::stod(argv[5]);
        std::string cat = (argc > 7) ? argv[7] : "";

        Expense e{nextId++, getCurrentDate(), desc, amount, cat};
        expenses.push_back(e);
        saveExpenses(expenses, filename);
        std::cout << "Expense added! (ID: " << e.id << ")\n";

    } else if (command == "list") {
        std::cout << std::left
                  << std::setw(5)  << "ID"
                  << std::setw(12) << "Date"
                  << std::setw(25) << "Description"
                  << std::setw(10) << "Amount"
                  << std::setw(15) << "Category" << "\n";
        std::cout << std::string(70, '-') << "\n";
        for (const auto& e : expenses) {
            std::cout << std::left
                      << std::setw(5)  << e.id
                      << std::setw(12) << e.date
                      << std::setw(25) << e.description
                      << std::setw(10) << std::fixed << std::setprecision(2) << e.amount
                      << std::setw(15) << e.category << "\n";
        }

    } else if (command == "summary") {
        double total = 0.0;
        for (const auto& e : expenses) total += e.amount;
        std::cout << "Total expenses: $" << std::fixed << std::setprecision(2) << total << "\n";

        if (argc == 4 && std::string(argv[2]) == "--month") {
            int month = std::stoi(argv[3]);
            double monthly = 0.0;
            for (const auto& e : expenses) {
                if (std::stoi(e.date.substr(5,2)) == month)
                    monthly += e.amount;
            }
            std::cout << "Month " << month << ": $" << monthly << "\n";
        }

    } else if (command == "delete" && argc == 4) {
        int id = std::stoi(argv[3]);
        auto it = std::remove_if(expenses.begin(), expenses.end(),
            [id](const Expense& e) { return e.id == id; });
        if (it != expenses.end()) {
            expenses.erase(it, expenses.end());
            saveExpenses(expenses, filename);
            std::cout << "Expense " << id << " deleted.\n";
        } else {
            std::cout << "ID not found.\n";
        }

    } else if (command == "update") {
        // Simple update (you can extend this)
        std::cout << "Update command not fully implemented yet.\n";
    } else {
        std::cerr << "Unknown command: " << command << "\n";
        return 1;
    }

    return 0;
}
