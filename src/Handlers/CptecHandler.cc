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
    req->setPath("/api/cptec/v1/cidade/" + cityName);
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

void CptecHandler::getCapitais(std::function<void(const CptecCapitaisResponse&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/cptec/v1/clima/capital");
    std::string fullUrl = baseUrl + req->getPath();
    std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;
    
    httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "/api/cptec/v1/clima/capital");
        std::string responseBody = std::string(response->getBody());

        CptecCapitaisResponse cptecCapitaisResponse;
        cptecCapitaisResponse.calledURL = fullUrl;
        cptecCapitaisResponse.jsonResponse = responseBody;

        Json::Value jsonResponse;
        Json::Reader reader;
        if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
            for (const auto& jsonCptec : jsonResponse) {
                CptecCapitais capitais;

                capitais.codigo_icao = jsonCptec["codigo_icao"].asString();
                capitais.atualizado_em = jsonCptec["atualizado_em"].asString();
                capitais.pressao_atmosferica = jsonCptec["pressao_atmosferica"].asString();
                capitais.visibilidade = jsonCptec["visibilidade"].asString();
                capitais.vento = jsonCptec["vento"].asInt();
                capitais.direcao_vento = jsonCptec["direcao_vento"].asInt();
                capitais.umidade = jsonCptec["umidade"].asInt();
                capitais.condicao = jsonCptec["condicao"].asString();
                capitais.condicao_Desc = jsonCptec["condicao_Desc"].asString();
                capitais.temp = jsonCptec["temp"].asInt();

                cptecCapitaisResponse.cptecCapitais.push_back(capitais);
            }
        }
        callback(cptecCapitaisResponse);
    });
}

void CptecHandler::getCondicoesAeroporto(std::string icao, std::function<void(const CptecCapitais&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/cptec/v1/clima/aeroporto/" + icao);
    std::string fullUrl = baseUrl + req->getPath();
    std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;
    
    httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "/api/cptec/v1/clima/aeroporto/{icaoCode}");
        std::string responseBody = std::string(response->getBody());

        Json::Value jsonResponse;
        Json::Reader reader;
        CptecCapitais cptecCapitais;
        if (reader.parse(responseBody, jsonResponse)) {
            cptecCapitais.codigo_icao = jsonResponse["codigo_icao"].asString();
            cptecCapitais.atualizado_em = jsonResponse["atualizado_em"].asString();
            cptecCapitais.pressao_atmosferica = jsonResponse["pressao_atmosferica"].asString();
            cptecCapitais.visibilidade = jsonResponse["visibilidade"].asString();
            cptecCapitais.vento = jsonResponse["vento"].asInt();
            cptecCapitais.direcao_vento = jsonResponse["direcao_vento"].asInt();
            cptecCapitais.umidade = jsonResponse["umidade"].asInt();
            cptecCapitais.condicao = jsonResponse["condicao"].asString();
            cptecCapitais.condicao_Desc = jsonResponse["condicao_Desc"].asString();
            cptecCapitais.temp = jsonResponse["temp"].asInt();

            cptecCapitais.calledURL = fullUrl;
            cptecCapitais.jsonResponse = responseBody;            
        }else {
            std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
            return;
        }
        callback(cptecCapitais);
    });
}