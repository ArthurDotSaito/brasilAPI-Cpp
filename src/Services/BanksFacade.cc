#include "BanksFacade.h"
#include <Utils/BrasilAPIException.h>

void BanksFacade::getAllBanks(std::function<void(const BankResponse&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/banks/v1");

    httpClient->sendRequest(req, [this, callback](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "/banks/v1");
        Json::Reader reader;
        Json::Value jsonResponse;
        std::string responseBody = std::string(response->getBody());

        if (!reader.parse(responseBody, jsonResponse)) {
            std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
            return;
        }

        BankResponse bankResponse = BankResponse::fromJsonValue(jsonResponse);
        callback(bankResponse);
    });
}


void BanksFacade::getBanksByCode(int code, std::function<void(const Bank&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/banks/v1/" + std::to_string(code));

    httpClient->sendRequest(req, [this, callback](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "/banks/v1/{code}");
        Json::Reader reader;
        Json::Value jsonResponse;
        std::string responseBody = std::string(response->getBody());

        if (!reader.parse(responseBody, jsonResponse)) {
            std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
            return;
        }

        Bank bankResponse = Bank::fromJsonValue(jsonResponse);
        callback(bankResponse);
    });
};