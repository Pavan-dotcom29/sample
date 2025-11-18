#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <vector>

struct Expense {
    int id;
    std::string date;
    std::string description;
    double amount;
    std::string category;
};

std::string getCurrentDate();
std::vector<Expense> loadExpenses(const std::string& filename);
void saveExpenses(const std::vector<Expense>& expenses, const std::string& filename);

#endif
