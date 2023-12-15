#include "CptecHandler.h"


void CptecHandler::listAllCities(std::function<void(const CptecCidadesResponse&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/cptec/v1/cidade");
    std::string fullUrl = baseUrl + req->getPath();
    std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;
    
    httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "/api/cptec/v1/cidade");
        std::string responseBody = std::string(response->getBody());

        CptecCidadesResponse cptecCidadesResponse;
        cptecCidadesResponse.calledURL = fullUrl;
        cptecCidadesResponse.jsonResponse = responseBody;

        Json::Value jsonResponse;
        Json::Reader reader;
        if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
            for (const auto& jsonCptec : jsonResponse) {
                CptecCidades cidade;
                cidade.nome = jsonCptec["nome"].asString();
                cidade.estado = jsonCptec["estado"].asString();
                cidade.id = jsonCptec["id"].asInt();
                cptecCidadesResponse.cptecCidades.push_back(cidade);
            }
        }

        callback(cptecCidadesResponse);
    });
}

void CptecHandler::searchByTerms(std::string cityName , std::function<void(const CptecCidadesResponse&)> callback){
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/cptec/v1/cidade" + cityName);
    std::string fullUrl = baseUrl + req->getPath();
    std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;
    
    httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "/api/cptec/v1/cidade/{cityName}");
        std::string responseBody = std::string(response->getBody());

        CptecCidadesResponse cptecCidadesResponse;
        cptecCidadesResponse.calledURL = fullUrl;
        cptecCidadesResponse.jsonResponse = responseBody;

        Json::Value jsonResponse;
        Json::Reader reader;
        if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
            for (const auto& jsonCptec : jsonResponse) {
                CptecCidades cidade;
                cidade.nome = jsonCptec["nome"].asString();
                cidade.estado = jsonCptec["estado"].asString();
                cidade.id = jsonCptec["id"].asInt();
                cptecCidadesResponse.cptecCidades.push_back(cidade);
            }
        }

        callback(cptecCidadesResponse);
    });
}