#ifndef BANK_RESPONSE_H
#define BANK_RESPONSE_H

#include<string>
#include<optional> 
#include<vector>
#include <json/json.h>
#include "BaseResponse.h"

class Bank:public BaseResponse {
public:
    std::string ispb;
    std::string name;
    std::optional<int> code;
    std::string fullname;

    Json::Value toJsonValue() const;
    static Bank fromJsonValue(const Json::Value& jsonValue);
};

class BankResponse: public BaseResponse{
public:
    std::vector<Bank> banks;
    Json::Value toJsonValue() const;
    static BankResponse fromJsonValue(const Json::Value& jsonValue);
};


#endif // BANK_RESPONSE_H