#include "BanksFacade.h"
#include <Utils/BrasilAPIException.h>

void BanksFacade::getAllBanks(std::function<void(const BankResponse&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/banks/v1");
    
    std::cout << "Iniciando a solicitação para: " << baseUrl + req->getPath() << std::endl;

    httpClient->sendRequest(req, [this, callback](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        std::cout << "Solicitação HTTP bem-sucedida, processando resposta..." << std::endl;
        std::cout << "Status code: " << response->getStatusCode() << std::endl;
        std::cout << "Response headers: " << std::endl;
         for (auto& header : response->headers()) {
            std::cout << header.first << ": " << header.second << std::endl;
        }
   
        Json::Reader reader;
        Json::Value jsonResponse;
        std::string responseBody = std::string(response->getBody());
        std::cout << "Response body: " << responseBody << std::endl;

        std::cout << "respostaBody" << responseBody;

        if (!reader.parse(responseBody, jsonResponse)) {
            std::cerr << "Falha ao analisar a resposta JSON: " << responseBody << std::endl;
            return;
        }

        std::cout << "Resposta JSON analisada com sucesso, construindo BankResponse..." << std::endl;

        BankResponse bankResponse;
        try {
            ensureSuccess(response, "/banks/v1");
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
            // Imprime o status code e o corpo da resposta para diagnóstico
            std::cerr << "Status code: " << response->getStatusCode() << std::endl;
            std::cerr << "Response body: " << response->getBody() << std::endl;
            return;
        }


        std::cout << "BankResponse construído, invocando callback..." << std::endl;
        callback(bankResponse);
    });
};


void BanksFacade::getBanksByCode(int code, std::function<void(const Json::Value&)> callback) {
    // TODO
};