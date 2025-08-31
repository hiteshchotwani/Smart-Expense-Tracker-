#include <iostream>
#include "Transaction.h"
#include "Tracker.h"

void showMenu() {
    std::cout << "\n====== Smart Finance Tracker ======\n";
    std::cout << "1. Add Transaction\n";
    std::cout << "2. View All Transactions\n";
    std::cout << "3. View Category-wise Totals\n";
    std::cout << "4. View Top 3 Categories\n";
    std::cout << "5. Suggest Monthly Budget\n";
    std::cout << "6. Detect Spending Anomalies\n";
    std::cout << "7. Export to File\n";
    std::cout << "8. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Tracker tracker;
    int choice;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // flush newline

        if (choice == 1) {
            std::string date, category, note;
            double amount;

            std::cout << "Enter date (YYYY-MM-DD): ";
            std::getline(std::cin, date);

            std::cout << "Enter category (e.g., Food, Travel, Rent): ";
            std::getline(std::cin, category);

            std::cout << "Enter note (optional): ";
            std::getline(std::cin, note);

            std::cout << "Enter amount (Rs): ";
            while (!(std::cin >> amount) || amount <= 0) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << " Invalid amount. Enter again: ";
            }
            std::cin.ignore();

            Transaction t(date, category, note, amount);
            tracker.addTransaction(t);

            std::cout << " Transaction added!\n";
        } 
        else if (choice == 2) {
            tracker.viewAllTransactions();
        }
        else if (choice == 3) {
            tracker.showCategoryTotals();
        }
        else if (choice == 4) {
            tracker.showTopCategories();
        }
        else if (choice == 5) {
            tracker.suggestMonthlyBudget();
        }
        else if (choice == 6) {
            tracker.detectSpendingAnomalies();
        }
        else if (choice == 7) {
            tracker.exportToFile();
        }
        else if (choice == 8) {
            std::cout << " Exiting. Thank you!\n";
        }
        else {
            std::cout << " Invalid option. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}
