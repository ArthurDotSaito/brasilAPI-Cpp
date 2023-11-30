#include "BrasilAPIClient.h"

BrasilAPIClient::BrasilAPIClient() : banksFacade() {}

void BrasilAPIClient::setUserAgent(const std::string& ua) {
    userAgent = ua;
}

void BrasilAPIClient::getAllBanks(std::function<void(const BankResponse&)> callback) {
    banksFacade.getAllBanks(callback);
}

void BrasilAPIClient::getBanksByCode(int code, std::function<void(const Json::Value&)> callback) {
    banksFacade.getBanksByCode(code, callback);
}
