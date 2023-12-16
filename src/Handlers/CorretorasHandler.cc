#include "CorretorasHandler.h"
#include <Utils/BrasilAPIException.h>

void CorretorasHandler::getAllCorretoras(std::function<void(const CorretorasResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cvm/corretoras/v1");
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cvm/corretoras/v1");
      std::string responseBody = std::string(response->getBody());

      CorretorasResponse corretorasResponse;
      corretorasResponse.calledURL = fullUrl;
      corretorasResponse.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
        for (const auto &jsonCorretoras : jsonResponse) {
          Corretoras corretora;
          corretora.bairro = jsonCorretoras["bairro"].asString();
          corretora.cep = jsonCorretoras["cep"].asString();
          corretora.cnpj = jsonCorretoras["cnpj"].asString();
          corretora.codigo_cvm = jsonCorretoras["codigo_cvm"].asString();
          corretora.complemento = jsonCorretoras["complemento"].asString();
          corretora.data_inicio_situacao = jsonCorretoras["data_inicio_situacao"].asString();
          corretora.data_patrimonio_liquido = jsonCorretoras["data_patrimonio_liquido"].asString();
          corretora.data_registro = jsonCorretoras["data_registro"].asString();
          corretora.email = jsonCorretoras["email"].asString();
          corretora.logradouro = jsonCorretoras["logradouro"].asString();
          corretora.municipio = jsonCorretoras["municipio"].asString();
          corretora.nome_social = jsonCorretoras["nome_social"].asString();
          corretora.nome_comercial = jsonCorretoras["nome_comercial"].asString();
          corretora.pais = jsonCorretoras["pais"].asString();
          corretora.status = jsonCorretoras["status"].asString();
          corretora.telefone = jsonCorretoras["telefone"].asString();
          corretora.type = jsonCorretoras["type"].asString();
          corretora.uf = jsonCorretoras["uf"].asString();
          corretora.valor_patrimonio_liquido = jsonCorretoras["valor_patrimonio_liquido"].asString();

          corretorasResponse.corretoras.push_back(corretora);
        }
      }
      callback(corretorasResponse);
    } catch (const BrasilAPIException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}

void CorretorasHandler::getCorretorasByCnpj(std::string cnpj, std::function<void(const Corretoras &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cvm/corretoras/v1/" + cnpj);
  std::string fullUrl = baseUrl + req->getPath();

  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cvm/corretoras/v1/{cnpj}");
      std::string responseBody = std::string(response->getBody());

      std::cout << "ResponseBody: " << responseBody << std::endl;

      Json::Value jsonResponse;
      Json::Reader reader;
      Corretoras corretoras;
      if (reader.parse(responseBody, jsonResponse)) {
        corretoras.bairro = jsonResponse["bairro"].asString();
        corretoras.cep = jsonResponse["cep"].asString();
        corretoras.cnpj = jsonResponse["cnpj"].asString();
        corretoras.codigo_cvm = jsonResponse["codigo_cvm"].asString();
        corretoras.complemento = jsonResponse["complemento"].asString();
        corretoras.data_inicio_situacao = jsonResponse["data_inicio_situacao"].asString();
        corretoras.data_patrimonio_liquido = jsonResponse["data_patrimonio_liquido"].asString();
        corretoras.email = jsonResponse["email"].asString();
        corretoras.logradouro = jsonResponse["logradouro"].asString();
        corretoras.municipio = jsonResponse["municipio"].asString();
        corretoras.nome_social = jsonResponse["nome_social"].asString();
        corretoras.nome_comercial = jsonResponse["nome_comercial"].asString();
        corretoras.pais = jsonResponse["pais"].asString();
        corretoras.status = jsonResponse["status"].asString();
        corretoras.telefone = jsonResponse["telefone"].asString();
        corretoras.type = jsonResponse["type"].asString();
        corretoras.uf = jsonResponse["uf"].asString();
        corretoras.valor_patrimonio_liquido = jsonResponse["valor_patrimonio_liquido"].asString();
        corretoras.data_registro = jsonResponse["data_registro"].asString();
        corretoras.calledURL = fullUrl;
        corretoras.jsonResponse = responseBody;
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }
      callback(corretoras);

    } catch (const BrasilAPIException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}