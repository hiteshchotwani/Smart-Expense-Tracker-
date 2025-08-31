#include "Tracker.h"
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <queue>
#include <utility>
#include <map>
#include <vector>
#include <fstream>

void Tracker::addTransaction(const Transaction& t) {
    transactions.push_back(t);
}

void Tracker::viewAllTransactions() const {
    std::cout << "\n All Transactions:\n";
    for (const auto& t : transactions) {
        t.display();
    }
}

void Tracker::showCategoryTotals() const {
    std::unordered_map<std::string, double> categorySums;

    for (const auto& t : transactions) {
        categorySums[t.category] += t.amount;
    }

    std::cout << "\n Category-wise Spending:\n";
    std::cout << std::fixed << std::setprecision(2);

    for (const auto& pair : categorySums) {
        std::cout << pair.first << ": Rs" << pair.second << std::endl;
    }
}

void Tracker::showTopCategories(int topN) const {
    std::unordered_map<std::string, double> categorySums;

    for (const auto& t : transactions) {
        categorySums[t.category] += t.amount;
    }

    std::priority_queue<std::pair<double, std::string>> maxHeap;

    for (const auto& entry : categorySums) {
        maxHeap.push({entry.second, entry.first});
    }

    std::cout << "\n Top " << topN << " Spending Categories:\n";

    for (int i = 0; i < topN && !maxHeap.empty(); ++i) {
        auto top = maxHeap.top();
        maxHeap.pop();
        std::cout << i + 1 << ". " << top.second << ": Rs" << top.first << "\n";
    }
}

void Tracker::suggestMonthlyBudget() const {
    std::unordered_map<std::string, double> monthTotals;

    for (const auto& t : transactions) {
        if (t.date.length() >= 7) {
            std::string month = t.date.substr(0, 7);  // YYYY-MM
            monthTotals[month] += t.amount;
        }
    }

    if (monthTotals.empty()) {
        std::cout << "\n Not enough data to suggest budget.\n";
        return;
    }

    double total = 0.0;
    for (const auto& entry : monthTotals) {
        total += entry.second;
    }

    double avg = total / monthTotals.size();
    double suggested = avg * 0.90;

    std::cout << "\n Monthly Budget Suggestion:\n";
    std::cout << "Average spending: Rs" << avg << "\n";
    std::cout << "Recommended max (10% buffer): Rs" << suggested << "\n";
}

void Tracker::detectSpendingAnomalies() const {
    std::map<std::string, double> dailyTotals;

    for (const auto& t : transactions) {
        dailyTotals[t.date] += t.amount;
    }

    if (dailyTotals.size() < 4) {
        std::cout << "\n Not enough data for anomaly detection.\n";
        return;
    }

    std::vector<std::pair<std::string, double>> dates(dailyTotals.begin(), dailyTotals.end());

    std::cout << "\n Spending Anomalies Detected:\n";

    for (size_t i = 3; i < dates.size(); ++i) {
        double avg = (dates[i - 1].second + dates[i - 2].second + dates[i - 3].second) / 3.0;
        if (dates[i].second > 2 * avg) {
            std::cout << " " << dates[i].first
                      << " → Rs" << dates[i].second
                      << " (Spike! 3-day avg = Rs" << avg << ")\n";
        }
    }
}

void Tracker::exportToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cout << " Error creating file.\n";
        return;
    }

    out << "Date,Category,Note,Amount\n";
    for (const auto& t : transactions) {
        out << t.date << "," << t.category << "," << t.note << "," << t.amount << "\n";
    }

    out.close();
    std::cout << " Transactions exported to '" << filename << "'\n";
}
