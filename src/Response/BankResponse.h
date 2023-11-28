#include<string>
#include<optional> 
#include<vector>

class Bank {
public:
    std::string ispb;
    std::string name;
    std::optional<int> code;
    std::string fullName;
};

class BankResponse: public BankResponse{
public:
    std::vector<Bank> banks;
};