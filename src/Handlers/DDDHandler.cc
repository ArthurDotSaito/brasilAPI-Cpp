#include "DDDHandler.h"
#include "Utils/BrasilAPIException.h"

void DDDHandler::listStateAndCities(int ddd, std::function<void(std::variant<DDDResponse, ErrorResponse>)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/ddd/v1/" + std::to_string(ddd));
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/ddd/v1/{ddd}");
      std::string responseBody = std::string(response->getBody());

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse)) {
        DDDResponse dddResponse;
        dddResponse.setState(jsonResponse["state"].asString());

        const Json::Value jsonCitiesArray = jsonResponse["cities"];
        for (const auto &jsonCity : jsonCitiesArray) {
          std::string city = jsonCity.asString();
          dddResponse.addCities(city);
        }
        callback(dddResponse);
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
