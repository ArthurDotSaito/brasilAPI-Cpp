#include "FeriadosHandler.h"
#include <Utils/BrasilAPIException.h>

void FeriadosHandler::getFeriados(int ano, std::function<void(const FeriadosResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/feriados/v1/" + std::to_string(ano));
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    ensureSuccess(response, "/api/feriados/v1/{ano}");
    std::string responseBody = std::string(response->getBody());

    FeriadosResponse feriadosResponse;
    feriadosResponse.calledURL = fullUrl;
    feriadosResponse.jsonResponse = responseBody;

    Json::Value jsonResponse;
    Json::Reader reader;
    if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
      for (const auto &jsonFeriado : jsonResponse) {
        Feriados feriados;
        feriados.date = jsonFeriado["date"].asString();
        feriados.name = jsonFeriado["name"].asString();
        feriados.type = jsonFeriado["type"].asString();
        feriadosResponse.feriados.push_back(feriados);
      }
    }

    callback(feriadosResponse);
  });
}