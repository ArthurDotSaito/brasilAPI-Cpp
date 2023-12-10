#include "CepHandler.h"

void CepHandler::getCep(int cep, std::function<void(const CepResponse&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/cep/v1/" + std::to_string(cep));
    std::string fullUrl = baseUrl + req->getPath();

    httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "api/cep/v1/{cep}");
        std::string responseBody = std::string(response->getBody());

        Json::Value jsonResponse;
        Json::Reader reader;
        CepResponse cepResponse;
        if (reader.parse(responseBody, jsonResponse)) {
            cepResponse.cep = jsonResponse["cep"].asString();
            cepResponse.state = jsonResponse["state"].asString();
            cepResponse.neighborhood = jsonResponse["neighborhood"].asString();
            cepResponse.street = jsonResponse["street"].asString();
            cepResponse.service = jsonResponse["service"].asString();
        } else {
            std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
            return;
        }

        callback(cepResponse);
    });
}