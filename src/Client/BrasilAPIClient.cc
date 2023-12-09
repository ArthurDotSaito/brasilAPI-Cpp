#include "BrasilAPIClient.h"
#include <drogon/drogon.h>

BrasilAPIClient::BrasilAPIClient() : banksFacade() {
    startEventLoop();
}

BrasilAPIClient::~BrasilAPIClient() {
    if (eventLoopThread.joinable()) {
        drogon::app().quit();
        eventLoopThread.join();
    }
}

void BrasilAPIClient::setUserAgent(const std::string& ua) {
    userAgent = ua;
}

void BrasilAPIClient::getAllBanks(std::function<void(const BankResponse&)> callback) {
    banksFacade.getAllBanks(callback);
}

void BrasilAPIClient::getBanksByCode(int code, std::function<void(const Bank&)> callback) {
    banksFacade.getBanksByCode(code, callback);
}

std::future<std::string> BrasilAPIClient::getAllBanksAsync() {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    banksFacade.getAllBanks([this, promisePtr](const BankResponse& response) {
        promisePtr->set_value(response.serialize());
    });
    return future;
}

std::future<std::string> BrasilAPIClient::getBanksByCodeAsync(int code) {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    banksFacade.getBanksByCode(code, [this, promisePtr, code](const Bank& bank) {
        promisePtr->set_value(bank.serialize());
    });
    return future;
}