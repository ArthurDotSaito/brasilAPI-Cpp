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

void BrasilAPIClient::getAllCorretoras(std::function<void(const CorretorasResponse&)> callback) {
    corretorasHandler.getAllCorretoras(callback);
}

void BrasilAPIClient::getCorretorasByCnpj(std::string cnpj, std::function<void(const Corretoras&)> callback) {
    corretorasHandler.getCorretorasByCnpj(cnpj, callback);
}

void BrasilAPIClient::listAllCities(std::function<void(const CptecCidadesResponse&)> callback) {
    cptecHandler.listAllCities(callback);
}

void BrasilAPIClient::searchByTerms(std::string cityName , std::function<void(const CptecCidadesResponse&)> callback) {
    cptecHandler.searchByTerms(cityName, callback);
}

void BrasilAPIClient::getCapitais(std::function<void(const CptecCapitaisResponse&)> callback) {
    cptecHandler.getCapitais(callback);
}

void BrasilAPIClient::getCondicoesAeroporto(std::string icao, std::function<void(const CptecAeroporto&)> callback) {
    cptecHandler.getCondicoesAeroporto(icao, callback);
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

std::future<std::string> BrasilAPIClient::getAllCorretorasAsync() {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    corretorasHandler.getAllCorretoras([this, promisePtr](const CorretorasResponse& corretorasResponse) {
        promisePtr->set_value(corretorasResponse.serialize());
    });
    return future;
}

std::future<std::string> BrasilAPIClient::getCorretorasByCnpjAsync(std::string cnpj) {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    corretorasHandler.getCorretorasByCnpj(cnpj, [this, promisePtr, cnpj](const Corretoras& corretora) {
        promisePtr->set_value(corretora.serialize());
    });
    return future;
}

std::future<std::string> BrasilAPIClient::listAllCitiesAsync() {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    cptecHandler.listAllCities([this, promisePtr](const CptecCidadesResponse& cidades) {
        promisePtr->set_value(cidades.serialize());
    });
    return future;
}

std::future<std::string> BrasilAPIClient::searchByTermsAsync(std::string cityName) {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    cptecHandler.searchByTerms(cityName, [this, promisePtr, cityName](const CptecCidadesResponse& cidades) {
        promisePtr->set_value(cidades.serialize());
    });
    return future;
}

std::future<std::string> BrasilAPIClient::getCapitaisAsync() {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    cptecHandler.getCapitais([this, promisePtr](const CptecCapitaisResponse& capitais) {
        promisePtr->set_value(capitais.serialize());
    });
    return future;
}

std::future<std::string> BrasilAPIClient::getCondicoesAeroportoAsync(std::string icao) {
    auto promisePtr = std::make_shared<std::promise<std::string>>();
    auto future = promisePtr->get_future();
    cptecHandler.getCondicoesAeroporto(icao, [this, promisePtr, icao](const CptecAeroporto& aeroporto) {
        promisePtr->set_value(aeroporto.serialize());
    });
    return future;
}
