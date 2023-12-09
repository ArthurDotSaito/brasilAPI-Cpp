#include "BrasilAPIClient.h"
#include <drogon/drogon.h>

BrasilAPIClient::BrasilAPIClient() : banksFacade() {}

void BrasilAPIClient::setUserAgent(const std::string& ua) {
    userAgent = ua;
}

void BrasilAPIClient::getAllBanks(std::function<void(const BankResponse&)> callback) {
    banksFacade.getAllBanks(callback);
}

void BrasilAPIClient::getBanksByCode(int code, std::function<void(const Bank&)> callback) {
    banksFacade.getBanksByCode(code, callback);
}

std::string BrasilAPIClient::getAllBanks() {
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();

    banksFacade.getAllBanks([this, &promise](const BankResponse& response) {
        std::string serializedData = response.serialize();
        std::cout << serializedData << std::endl;
        promise.set_value(serializedData);
    });

    std::thread([this]() {
        drogon::app().run();
    }).detach();

    return future.get(); 
}

std::string BrasilAPIClient::getBanksByCode(int code) {
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();

    banksFacade.getBanksByCode(code, [this, &promise, code](const Bank& bank) {
        std::string serializedData = bank.serialize();
        std::cout << serializedData << std::endl;
        promise.set_value(serializedData); 
    });

    std::thread([this]() {
        drogon::app().run();
    }).detach();

    return future.get(); 
}