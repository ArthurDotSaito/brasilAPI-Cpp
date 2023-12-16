#include "CepHandler.h"
#include <Utils/BrasilAPIException.h>

void CepHandler::getCep(int cep, std::function<void(const CepResponse&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/cep/v1/" + std::to_string(cep));
    std::string fullUrl = baseUrl + req->getPath();

    httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        try{
            ensureSuccess(response, "api/cep/v1/{cep}");
            std::string responseBody = std::string(response->getBody());

            Json::Value jsonResponse;
            Json::Reader reader;
            CepResponse cepResponse;
            if (reader.parse(responseBody, jsonResponse)) {
                cepResponse.cep = jsonResponse["cep"].asString();
                cepResponse.state = jsonResponse["state"].asString();
                cepResponse.city = jsonResponse["city"].asString();
                cepResponse.neighborhood = jsonResponse["neighborhood"].asString();
                cepResponse.street = jsonResponse["street"].asString();
                cepResponse.service = jsonResponse["service"].asString();
                cepResponse.calledURL = fullUrl;
            } else {
                std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
                return;
            }

            callback(cepResponse);
        }catch(const BrasilAPIException& e){
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }
    });
}

void CepHandler::getCepV2(int cep, std::function<void(const CepResponse&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/cep/v2/" + std::to_string(cep));
    std::string fullUrl = baseUrl + req->getPath();

    httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        try{
            ensureSuccess(response, "api/cep/v2/{cep}");
            std::string responseBody = std::string(response->getBody());

            Json::Value jsonResponse;
            Json::Reader reader;
            CepResponse cepResponse;
            if (reader.parse(responseBody, jsonResponse)) {
                cepResponse.cep = jsonResponse["cep"].asString();
                cepResponse.state = jsonResponse["state"].asString();
                cepResponse.city = jsonResponse["city"].asString();
                cepResponse.neighborhood = jsonResponse["neighborhood"].asString();
                cepResponse.street = jsonResponse["street"].asString();
                cepResponse.service = jsonResponse["service"].asString();
                
                Json::Value jsonLocation = jsonResponse["location"];
                cepResponse.location.type = jsonResponse["type"].asString();
                cepResponse.location.coordinates.longitude = jsonLocation["coordinates"]["longitude"].asString();
                cepResponse.location.coordinates.latitude = jsonLocation["coordinates"]["latitude"].asString();

                cepResponse.calledURL = fullUrl;
            } else {
                std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
                return;
            }

            callback(cepResponse);
        }catch(const BrasilAPIException& e){
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }
    });
}