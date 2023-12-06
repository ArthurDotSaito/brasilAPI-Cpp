#include "BanksFacade.h"
#include <Utils/BrasilAPIException.h>

void BanksFacade::getAllBanks(std::function<void(const BankResponse&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/banks/v1");
    std::cout << "Iniciando a solicitação para: " << baseUrl + req->getPath() << std::endl;std::string baseUrl = "/api/banks/v1/";
    
    httpClient->sendRequest(req, [this, callback, baseUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "api/banks/v1");
        Json::Reader reader;
        Json::Value jsonResponse;
        std::string responseBody = std::string(response->getBody());

        if (!reader.parse(responseBody, jsonResponse)) {
            std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
            return;
        }

        BankResponse bankResponse = BankResponse::fromJsonValue(jsonResponse);
        bankResponse.calledURL = baseUrl;
        bankResponse.jsonResponse = responseBody;
        callback(bankResponse);
    });
}


void BanksFacade::getBanksByCode(int code, std::function<void(const Bank&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/banks/v1/" + std::to_string(code));
    std::string baseUrl = "/api/banks/v1/" + std::to_string(code);

    httpClient->sendRequest(req, [this, callback, baseUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "api/banks/v1/{code}");
        Json::Reader reader;
        Json::Value jsonResponse;
        std::string responseBody = std::string(response->getBody());

        if (!reader.parse(responseBody, jsonResponse)) {
            std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
            return;
        }

        Bank bankResponse = Bank::fromJsonValue(jsonResponse);
        bankResponse.calledURL = baseUrl;
        bankResponse.jsonResponse = responseBody;
        callback(bankResponse);
    });
};