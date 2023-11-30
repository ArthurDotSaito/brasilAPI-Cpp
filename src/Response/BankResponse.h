#ifndef BANK_RESPONSE_H
#define BANK_RESPONSE_H

#include<string>
#include<optional> 
#include<vector>

class Bank {
public:
    std::string ispb;
    std::string name;
    std::optional<int> code;
    std::string fullname;
};

class BankResponse{
public:
    std::vector<Bank> banks;
};

#endif // BANK_RESPONSE_H