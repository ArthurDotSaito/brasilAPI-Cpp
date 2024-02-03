#include "NCMHandler.h"
#include <Utils/BrasilAPIException.h>

void NCMHandler::listarTodosNCM(std::function<void(std::variant<NCMResponse, ErrorResponse>)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/ncm/v1");
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "api/banks/v1");
      std::string responseBody = std::string(response->getBody());

      NCMResponse ncmResponse;
      ncmResponse.calledURL = fullUrl;
      ncmResponse.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
        for (const auto &jsonBank : jsonResponse) {
          NCM ncm;
          ncm.setCodigo(jsonBank["codigo"].asString());
          ncm.setDescricao(jsonBank["descricao"].asString());
          ncm.setDataInicio(jsonBank["data_inicio"].asString());
          ncm.setDataFim(jsonBank["data_fim"].asString());
          ncm.setTipoAto(jsonBank["tipo_ato"].asString());
          ncm.setNumeroAto(jsonBank["numero_ato"].asString());
          ncm.setAnoAto(jsonBank["ano_ato"].asString());

          ncmResponse.ncm.push_back(ncm);
        }
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }

      callback(ncmResponse);
    } catch (const BrasilAPIException &e) {
      ErrorResponse errorResponse;
      errorResponse.errorCode = e.getStatusCode();
      errorResponse.errorMessage = e.what();

      callback(errorResponse);
    }
  });
}

void NCMHandler::listarPorCodigoNCM(std::string code, std::function<void(std::variant<NCMResponse, ErrorResponse>)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/ncm/v1");
  std::stringstream queryStream;
  queryStream << "?search=" << code;

  std::string fullUrl = baseUrl + req->getPath() + queryStream.str();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "api/banks/v1");
      std::string responseBody = std::string(response->getBody());

      NCMResponse ncmResponse;
      ncmResponse.calledURL = fullUrl;
      ncmResponse.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
        for (const auto &jsonBank : jsonResponse) {
          NCM ncm;
          ncm.setCodigo(jsonBank["codigo"].asString());
          ncm.setDescricao(jsonBank["descricao"].asString());
          ncm.setDataInicio(jsonBank["data_inicio"].asString());
          ncm.setDataFim(jsonBank["data_fim"].asString());
          ncm.setTipoAto(jsonBank["tipo_ato"].asString());
          ncm.setNumeroAto(jsonBank["numero_ato"].asString());
          ncm.setAnoAto(jsonBank["ano_ato"].asString());

          ncmResponse.ncm.push_back(ncm);
        }
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }

      callback(ncmResponse);
    } catch (const BrasilAPIException &e) {
      ErrorResponse errorResponse;
      errorResponse.errorCode = e.getStatusCode();
      errorResponse.errorMessage = e.what();

      callback(errorResponse);
    }
  });
}

void NCMHandler::getNCMInfo(std::string code, std::function<void(std::variant<NCM, ErrorResponse>)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/ncm/v1/" + code);

  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, fullUrl);
      std::string responseBody = std::string(response->getBody());

      NCM ncm;
      ncm.calledURL = fullUrl;
      ncm.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse)) {
        ncm.setCodigo(jsonResponse["codigo"].asString());
        ncm.setDescricao(jsonResponse["descricao"].asString());
        ncm.setDataInicio(jsonResponse["data_inicio"].asString());
        ncm.setDataFim(jsonResponse["data_fim"].asString());
        ncm.setTipoAto(jsonResponse["tipo_ato"].asString());
        ncm.setNumeroAto(jsonResponse["numero_ato"].asString());
        ncm.setAnoAto(jsonResponse["ano_ato"].asString());
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }

      callback(ncm);
    } catch (const BrasilAPIException &e) {
      ErrorResponse errorResponse;
      errorResponse.errorCode = e.getStatusCode();
      errorResponse.errorMessage = e.what();

      callback(errorResponse);
    }
  });
}