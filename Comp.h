#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    Comp(){
        CompHT1=std::vector <Account>(capacity);
        CompHT2=std::vector <Account>(capacity);

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
    int capacity=200003;
    std::vector<int> topk;
    std::vector<Account> CompHT1;
    std::vector<Account> CompHT2;
    int hash2(std::string id);
    bool fun(std::string id,int count, std::vector<Account> &HT1,std::vector<Account> &HT2,int value);
    void insertown(int e,std::vector <int> &v);
    // Other data members and functions specific to Your implementation
};

#endif // COMP_H
