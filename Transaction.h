#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    std::string date;
    std::string category;
    std::string note;
    double amount;

    Transaction(std::string d, std::string c, std::string n, double a);
    void display() const;
};

#endif
