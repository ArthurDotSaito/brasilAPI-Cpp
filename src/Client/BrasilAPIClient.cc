#include "BrasilAPIClient.h"
#include <drogon/drogon.h>

BrasilAPIClient::BrasilAPIClient() : banksHandler() {
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
    banksHandler.getAllBanks(callback);
}

void BrasilAPIClient::getBanksByCode(int code, std::function<void(const Bank&)> callback) {
    banksHandler.getBanksByCode(code, callback);
}

void BrasilAPIClient::getCep(int cep, std::function<void(const CepResponse&)> callback) {
    cepHandler.getCep(cep, callback);
}

void BrasilAPIClient::getCepV2(int cep, std::function<void(const CepResponse&)> callback) {
    cepHandler.getCepV2(cep, callback);
}

void BrasilAPIClient::getCNPJ(std::string cnpj, std::function<void(const CNPJResponse&)> callback) {
    cnpjHandler.getCNPJ(cnpj, callback);
}

std::future<std::string> BrasilAPIClient::getAllBanksAsync() {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    banksHandler.getAllBanks([this, promisePtr](const BankResponse& response) {
        promisePtr->set_value(response.serialize());
    });
    return future;
}

std::future<std::string> BrasilAPIClient::getBanksByCodeAsync(int code) {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    banksHandler.getBanksByCode(code, [this, promisePtr, code](const Bank& bank) {
        promisePtr->set_value(bank.serialize());
    });
    return future;
}

std::future<std::string> BrasilAPIClient::getCepAsync(int cep) {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    cepHandler.getCep(cep, [this, promisePtr, cep](const CepResponse& cepRespose) {
        promisePtr->set_value(cepRespose.serialize());
    });
    return future;
}

std::future<std::string> BrasilAPIClient::getCepV2Async(int cep) {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    cepHandler.getCepV2(cep, [this, promisePtr, cep](const CepResponse& cepRespose) {
        promisePtr->set_value(cepRespose.serialize());
    });
    return future;
}

std::future<std::string> BrasilAPIClient::getCNPJAsync(std::string cnpj) {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    cnpjHandler.getCNPJ(cnpj, [this, promisePtr, cnpj](const CNPJResponse& cnpjResponse) {
        promisePtr->set_value(cnpjResponse.serialize());
    });
    return future;
}