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

    std::string serialize() const {
        Json::Value jsonBank;
        jsonBank["ispb"] = ispb;
        jsonBank["name"] = name;
        jsonBank["code"] = code.has_value() ? code.value() : Json::Value(Json::nullValue);
        jsonBank["fullName"] = fullName;

        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "";  
        return Json::writeString(builder, jsonBank);
    }
};

class BankResponse : public BaseResponse {
public:
    std::vector<Bank> banks;

    std::string serialize() const {
        Json::Value jsonRoot;
        for (const auto& bank : banks) {
            Json::Value jsonBank;
            jsonBank["ispb"] = bank.ispb;
            jsonBank["name"] = bank.name;
            jsonBank["code"] = bank.code.has_value() ? bank.code.value() : Json::Value(Json::nullValue);
            jsonBank["fullName"] = bank.fullName;

            jsonRoot.append(jsonBank);
        }

        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = ""; 
        return Json::writeString(builder, jsonRoot);
    }
};

#endif // BANK_RESPONSE_H
