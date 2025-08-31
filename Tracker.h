#ifndef TRACKER_H
#define TRACKER_H

#include "Transaction.h"
#include <vector>
#include <string>

class Tracker {
private:
    std::vector<Transaction> transactions;

public:
    void addTransaction(const Transaction& t);
    void viewAllTransactions() const;
    void showCategoryTotals() const;
    void showTopCategories(int topN = 3) const;
    void suggestMonthlyBudget() const;
    void detectSpendingAnomalies() const;
    void exportToFile(const std::string& filename = "transactions_export.txt") const;
};

#endif
