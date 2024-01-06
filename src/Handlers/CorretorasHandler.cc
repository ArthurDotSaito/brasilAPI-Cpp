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
          corretora.setBairro(jsonCorretoras["bairro"].asString());
          corretora.setCep(jsonCorretoras["cep"].asString());
          corretora.setCnpj(jsonCorretoras["cnpj"].asString());
          corretora.setCodigoCvm(jsonCorretoras["codigo_cvm"].asString());
          corretora.setComplemento(jsonCorretoras["complemento"].asString());
          corretora.setDataInicioSituacao(jsonCorretoras["data_inicio_situacao"].asString());
          corretora.setDataPatrimonioLiquido(jsonCorretoras["data_patrimonio_liquido"].asString());
          corretora.setDataRegistro(jsonCorretoras["data_registro"].asString());
          corretora.setEmail(jsonCorretoras["email"].asString());
          corretora.setLogradouro(jsonCorretoras["logradouro"].asString());
          corretora.setMunicipio(jsonCorretoras["municipio"].asString());
          corretora.setNomeSocial(jsonCorretoras["nome_social"].asString());
          corretora.setNomeComercial(jsonCorretoras["nome_comercial"].asString());
          corretora.setPais(jsonCorretoras["pais"].asString());
          corretora.setStatus(jsonCorretoras["status"].asString());
          corretora.setTelefone(jsonCorretoras["telefone"].asString());
          corretora.setType(jsonCorretoras["type"].asString());
          corretora.setUf(jsonCorretoras["uf"].asString());
          corretora.setValorPatrimonioLiquido(jsonCorretoras["valor_patrimonio_liquido"].asString());

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

      Json::Value jsonResponse;
      Json::Reader reader;
      Corretoras corretoras;
      if (reader.parse(responseBody, jsonResponse)) {
        corretoras.setBairro(jsonResponse["bairro"].asString());
        corretoras.setCep(jsonResponse["cep"].asString());
        corretoras.setCnpj(jsonResponse["cnpj"].asString());
        corretoras.setCodigoCvm(jsonResponse["codigo_cvm"].asString());
        corretoras.setComplemento(jsonResponse["complemento"].asString());
        corretoras.setDataInicioSituacao(jsonResponse["data_inicio_situacao"].asString());
        corretoras.setDataPatrimonioLiquido(jsonResponse["data_patrimonio_liquido"].asString());
        corretoras.setDataRegistro(jsonResponse["data_registro"].asString());
        corretoras.setEmail(jsonResponse["email"].asString());
        corretoras.setLogradouro(jsonResponse["logradouro"].asString());
        corretoras.setMunicipio(jsonResponse["municipio"].asString());
        corretoras.setNomeSocial(jsonResponse["nome_social"].asString());
        corretoras.setNomeComercial(jsonResponse["nome_comercial"].asString());
        corretoras.setPais(jsonResponse["pais"].asString());
        corretoras.setStatus(jsonResponse["status"].asString());
        corretoras.setTelefone(jsonResponse["telefone"].asString());
        corretoras.setType(jsonResponse["type"].asString());
        corretoras.setUf(jsonResponse["uf"].asString());
        corretoras.setValorPatrimonioLiquido(jsonResponse["valor_patrimonio_liquido"].asString());
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