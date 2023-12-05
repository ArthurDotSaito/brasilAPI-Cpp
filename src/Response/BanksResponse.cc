#include "BankResponse.h"
#include <json/json.h>

Json::Value BankResponse::toJsonValue() const {
    Json::Value jsonValue;
    jsonValue["CalledURL"] = calledURL;
    jsonValue["JsonResponse"] = jsonResponse;
    for (const auto& bank : banks) {
        jsonValue["banks"].append(bank.toJsonValue());
    }
    return jsonValue;
}

BankResponse BankResponse::fromJsonValue(const Json::Value& jsonValue) {
    BankResponse response;
    response.calledURL = jsonValue["CalledURL"].asString();
    response.jsonResponse = jsonValue["JsonResponse"].asString();
    for (const auto& jsonBank : jsonValue["banks"]) {
        response.banks.push_back(Bank::fromJsonValue(jsonBank));
    }
    return response;
}
