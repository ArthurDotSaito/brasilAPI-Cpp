#include "FipeHandler.h"
#include <Utils/BrasilAPIException.h>

void FipeHandler::getFipe(const std::optional<std::string> &tipoVeiculo, const std::optional<int> &tabela_referencia,
    std::function<void(const FipeResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  std::stringstream pathStream;
  std::stringstream queryStream;
  pathStream << "/api/fipe/marcas/v1";

  if (tipoVeiculo) {
    pathStream << "/" << *tipoVeiculo;
  };

  if (tabela_referencia) {
    queryStream << "?tabela_referencia=" << *tabela_referencia;
  };

  req->setPath(pathStream.str() + queryStream.str());
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    ensureSuccess(response, fullUrl);
    std::string responseBody = std::string(response->getBody());

    FipeResponse fipeResponse;
    fipeResponse.calledURL = fullUrl;
    fipeResponse.jsonResponse = responseBody;

    Json::Value jsonResponse;
    Json::Reader reader;
    if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
      for (const auto &jsonItem : jsonResponse) {
        Fipe fipe;
        fipe.nome = jsonItem["nome"].asString();
        fipe.valor = jsonItem["valor"].asString();
        fipeResponse.fipe.push_back(fipe);
      }
    }

    callback(fipeResponse);
  });
}