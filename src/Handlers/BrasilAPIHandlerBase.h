#ifndef BRASIL_API_HANDLER_BASE_H
#define BRASIL_API_HANDLER_BASE_H

#include <drogon/HttpClient.h>

class BrasilAPIHandlerBase {
  protected:
  std::shared_ptr<drogon::HttpClient> httpClient;
  const std::string baseUrl = "https://brasilapi.com.br";

  public:
  BrasilAPIHandlerBase() {
    httpClient = drogon::HttpClient::newHttpClient(baseUrl);
  }
  void ensureSuccess(const drogon::HttpResponsePtr &response, const std::string &url);
};

#endif // BRASIL_API_HANDLER_BASE_H