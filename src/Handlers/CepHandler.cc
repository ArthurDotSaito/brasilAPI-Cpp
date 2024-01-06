#include "CepHandler.h"
#include <Utils/BrasilAPIException.h>

void CepHandler::getCep(int cep, std::function<void(const CepResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cep/v1/" + std::to_string(cep));
  std::string fullUrl = baseUrl + req->getPath();

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "api/cep/v1/{cep}");
      std::string responseBody = std::string(response->getBody());

      Json::Value jsonResponse;
      Json::Reader reader;
      CepResponse cepResponse;
      if (reader.parse(responseBody, jsonResponse)) {
        cepResponse.setCep(jsonResponse["cep"].asString());
        cepResponse.setState(jsonResponse["state"].asString());
        cepResponse.setCity(jsonResponse["city"].asString());
        cepResponse.setNeighborhood(jsonResponse["neighborhood"].asString());
        cepResponse.setStreet(jsonResponse["street"].asString());
        cepResponse.setService(jsonResponse["service"].asString());
        cepResponse.calledURL = fullUrl;
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }

      callback(cepResponse);
    } catch (const BrasilAPIException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}

void CepHandler::getCepV2(int cep, std::function<void(const CepResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cep/v2/" + std::to_string(cep));
  std::string fullUrl = baseUrl + req->getPath();

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "api/cep/v2/{cep}");
      std::string responseBody = std::string(response->getBody());

      Json::Value jsonResponse;
      Json::Reader reader;
      CepResponse cepResponse;
      if (reader.parse(responseBody, jsonResponse)) {
        cepResponse.setCep(jsonResponse["cep"].asString());
        cepResponse.setState(jsonResponse["state"].asString());
        cepResponse.setCity(jsonResponse["city"].asString());
        cepResponse.setNeighborhood(jsonResponse["neighborhood"].asString());
        cepResponse.setStreet(jsonResponse["street"].asString());
        cepResponse.setService(jsonResponse["service"].asString());

        Location loc;
        Json::Value jsonLocation = jsonResponse["location"];
        loc.type = jsonLocation["type"].asString();
        loc.coordinates.longitude = jsonLocation["coordinates"]["longitude"].asString();
        loc.coordinates.latitude = jsonLocation["coordinates"]["latitude"].asString();
        cepResponse.setLocation(loc);

        cepResponse.calledURL = fullUrl;
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }

      callback(cepResponse);
    } catch (const BrasilAPIException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}