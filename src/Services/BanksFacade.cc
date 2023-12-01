#include "BanksFacade.h"
#include <Utils/BrasilAPIException.h>

void BanksFacade::getAllBanks(std::function<void(const BankResponse&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/banks/v1");
    
    std::cout << "Requesting: " << baseUrl + req->getPath() << std::endl;

    httpClient->sendRequest(req, [this, callback](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "/banks/v1");
        Json::Reader reader;
        Json::Value jsonResponse;
        std::string responseBody = std::string(response->getBody());

        if (!reader.parse(responseBody, jsonResponse)) {
            std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
            return;
        }

        BankResponse bankResponse;
        try {
            for (const auto& jsonBank : jsonResponse) {
                Bank bank;
                bank.ispb = jsonBank["ispb"].asString();
                bank.name = jsonBank["name"].asString();
                if (!jsonBank["code"].isNull()) {
                    bank.code = jsonBank["code"].asInt();
                }
                bank.fullname = jsonBank["fullName"].asString();
                bankResponse.banks.push_back(bank);
            }
        } catch (const BrasilAPIException& e) {
            std::cerr << "Erro ao acessar a BrasilAPI: " << e.what() << std::endl;
            std::cerr << "Status code: " << response->getStatusCode() << std::endl;
            std::cerr << "Response body: " << response->getBody() << std::endl;
            return;
        }

        callback(bankResponse);
    });
};


void BanksFacade::getBanksByCode(int code, std::function<void(const Json::Value&)> callback) {
    // TODO
};