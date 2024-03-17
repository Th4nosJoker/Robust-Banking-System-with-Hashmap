#ifndef QUADRATICPROBING_H
#define QUADRATICPROBING_H

#include "BaseClass.h"
#include <iostream>

class QuadraticProbing : public BaseClass {
public:
    QuadraticProbing(){
        bankStorage1d= std::vector<Account>(capacity);
    }
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;

private:
    int size=0;
    int q=0;
    int capacity=200003;
    std::vector<int> topk;
    void insertown(int e,std::vector <int> &v);
    // Other data members and functions specific to Quadratic Probing
};

#endif // QUADRATICPROBING_H
