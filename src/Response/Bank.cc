#include "BankResponse.h"
#include <json/json.h>


Json::Value Bank::toJsonValue() const {
    Json::Value jsonValue;
    
    jsonValue["ispb"] = ispb;
    jsonValue["name"] = name;
    if (code.has_value()) {
        jsonValue["code"] = *code;  
    jsonValue["fullName"] = fullName;

    return jsonValue;
    };
}

Bank Bank::fromJsonValue(const Json::Value& jsonValue) {
    Bank bank;

    bank.ispb = jsonValue["ispb"].asString();
    bank.name = jsonValue["name"].asString();

    if (!jsonValue["code"].isNull()) {
        bank.code = jsonValue["code"].asInt();
    }

    bank.fullName = jsonValue["fullName"].asString();

    return bank;
}


BankResponse BankResponse::fromJsonValue(const Json::Value& jsonValue) {
    BankResponse bankResponse;

    if (jsonValue.isArray()) {
        for (const auto& bankJsonValue : jsonValue) {
            Bank bank;

            bank.ispb = bankJsonValue["ispb"].asString();
            bank.name = bankJsonValue["name"].asString();

            if (!bankJsonValue["code"].isNull()) {
                bank.code = bankJsonValue["code"].asInt();
            }

            bank.fullName = bankJsonValue["fullName"].asString();

            bankResponse.banks.push_back(bank);
        }
    }

    return bankResponse;
}
