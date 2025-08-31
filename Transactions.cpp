#include "Transaction.h"
#include <iostream>

Transaction::Transaction(std::string d, std::string c, std::string n, double a)
    : date(d), category(c), note(n), amount(a) {}

void Transaction::display() const {
    std::cout << date << " | " << category << " | " << note << " | Rs" << amount << std::endl;
}
