#include "IBGEHandler.h"
#include <Utils/BrasilAPIException.h>
#include <Utils/ValidateProviders.h>

void IBGEHandler::listMunicipios(const std::string &siglaUf, const std::optional<std::string> &providers,
    std::function<void(const IBGEMunicipiosResponse &)> callback) {
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
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}

void IBGEHandler::listRegioes(std::function<void(const IBGERegioesResponse &)> callback) {
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
          Regiao regiao;
          regiao.setId(jsonItem["id"].asString());
          regiao.setNome(jsonItem["nome"].asString());
          regiao.setSigla(jsonItem["sigla"].asString());
          ibgeRegioesResponse.regioes.push_back(regiao);
        }
        callback(ibgeRegioesResponse);
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }
    } catch (const BrasilAPIException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}