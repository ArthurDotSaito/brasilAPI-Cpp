#include "IBGEHandler.h"
#include <Utils/BrasilAPIException.h>
#include <Utils/ValidateProviders.h>

void IBGEHandler::listarMunicipios(const std::string &siglaUf, const std::optional<std::string> &providers,
    std::function<void(std::variant<IBGEMunicipiosResponse, ErrorResponse>)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  std::stringstream pathStream;
  std::stringstream queryStream;
  pathStream << "/api/ibge/municipios/v1/" + siglaUf;

  if (providers) {
    if (!validateProviders(providers)) {
      throw BrasilAPIException("Provedor inválido fornecido", 404, pathStream.str());
    }
    queryStream << "?providers=" << *providers;
  };

  req->setPath(pathStream.str() + queryStream.str());
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, fullUrl);
      std::string responseBody = std::string(response->getBody());

      IBGEMunicipiosResponse ibgeMunicipiosResponse;
      ibgeMunicipiosResponse.calledURL = fullUrl;
      ibgeMunicipiosResponse.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
        for (const auto &jsonItem : jsonResponse) {
          IBGEMunicipios ibgeMunicipios;
          ibgeMunicipios.setNome(jsonItem["nome"].asString());
          ibgeMunicipios.setCodigoIbge(jsonItem["codigo_ibge"].asString());
          ibgeMunicipiosResponse.ibgeMunicipios.push_back(ibgeMunicipios);
        }
        callback(ibgeMunicipiosResponse);
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }
    } catch (const BrasilAPIException &e) {
      ErrorResponse errorResponse;
      errorResponse.errorCode = e.getStatusCode();
      errorResponse.errorMessage = e.what();

      callback(errorResponse);
    }
  });
}

void IBGEHandler::listarRegioes(std::function<void(std::variant<IBGERegioesResponse, ErrorResponse>)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  std::stringstream pathStream;
  pathStream << "/api/ibge/uf/v1";

  req->setPath(pathStream.str());
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, fullUrl);
      std::string responseBody = std::string(response->getBody());

      IBGERegioesResponse ibgeRegioesResponse;
      ibgeRegioesResponse.calledURL = fullUrl;
      ibgeRegioesResponse.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
        for (const auto &jsonItem : jsonResponse) {
          Estado estado;
          estado.setId(jsonItem["id"].asString());
          estado.setNome(jsonItem["nome"].asString());
          estado.setSigla(jsonItem["sigla"].asString());
          Regiao regiao;
          regiao.setId(jsonItem["regiao"]["id"].asString());
          regiao.setNome(jsonItem["regiao"]["nome"].asString());
          regiao.setSigla(jsonItem["regiao"]["sigla"].asString());
          estado.setRegiao(regiao);
          ibgeRegioesResponse.estados.push_back(estado);
        }
        callback(ibgeRegioesResponse);
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }
    } catch (const BrasilAPIException &e) {
      ErrorResponse errorResponse;
      errorResponse.errorCode = e.getStatusCode();
      errorResponse.errorMessage = e.what();

      callback(errorResponse);
    }
  });
}

void IBGEHandler::getEstado(const std::string &uf, std::function<void(std::variant<Estado, ErrorResponse>)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  std::stringstream pathStream;
  pathStream << "/api/ibge/uf/v1/" + uf;

  req->setPath(pathStream.str());
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, fullUrl);
      std::string responseBody = std::string(response->getBody());

      Estado estado;
      estado.calledURL = fullUrl;
      estado.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse)) {
        estado.setId(jsonResponse["id"].asString());
        estado.setNome(jsonResponse["nome"].asString());
        estado.setSigla(jsonResponse["sigla"].asString());
        Regiao regiao;
        regiao.setId(jsonResponse["regiao"]["id"].asString());
        regiao.setNome(jsonResponse["regiao"]["nome"].asString());
        regiao.setSigla(jsonResponse["regiao"]["sigla"].asString());
        estado.setRegiao(regiao);
        callback(estado);
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }
    } catch (const BrasilAPIException &e) {
      ErrorResponse errorResponse;
      errorResponse.errorCode = e.getStatusCode();
      errorResponse.errorMessage = e.what();

      callback(errorResponse);
    }
  });
}