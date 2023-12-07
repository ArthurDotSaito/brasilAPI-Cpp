#ifndef BANK_RESPONSE_H
#define BANK_RESPONSE_H

#include <string>
#include <vector>
#include <json/json.h>
#include "BaseResponse.h"

class Bank : public BaseResponse {
public:
    std::string ispb;
    std::string name;
    std::optional<int> code;
    std::string fullName;
};

class BankResponse : public BaseResponse {
public:
    std::vector<Bank> banks;
};

#endif // BANK_RESPONSE_H
