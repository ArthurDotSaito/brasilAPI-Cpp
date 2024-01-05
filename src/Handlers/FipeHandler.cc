#include "FipeHandler.h"
#include <Utils/BrasilAPIException.h>

void FipeHandler::listFipeMarcas(const std::optional<std::string> &tipoVeiculo, const std::optional<int> &tabela_referencia,
    std::function<void(const FipeMarcas &)> callback) {
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

    FipeMarcas fipeResponse;
    fipeResponse.calledURL = fullUrl;
    fipeResponse.jsonResponse = responseBody;

    Json::Value jsonResponse;
    Json::Reader reader;
    if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
      for (const auto &jsonItem : jsonResponse) {
        Marcas marcas;
        marcas.nome = jsonItem["nome"].asString();
        marcas.valor = jsonItem["valor"].asString();
        fipeResponse.fipe.push_back(marcas);
      }
    }

    callback(fipeResponse);
  });
}

void FipeHandler::listFipePreco(const std::string &codigoFipe, const std::optional<int> &tabela_referencia,
    std::function<void(const FipePrecos &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  std::stringstream pathStream;
  std::stringstream queryStream;
  pathStream << "/api/fipe/preco/v1/" + codigoFipe;

  if (tabela_referencia) {
    queryStream << "?tabela_referencia=" << *tabela_referencia;
  };

  req->setPath(pathStream.str() + queryStream.str());
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    ensureSuccess(response, fullUrl);
    std::string responseBody = std::string(response->getBody());

    FipePrecos precosResponse;
    precosResponse.calledURL = fullUrl;
    precosResponse.jsonResponse = responseBody;

    Json::Value jsonResponse;
    Json::Reader reader;
    if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
      for (const auto &jsonItem : jsonResponse) {
        Precos precos;
        precos.setValor(jsonItem["valor"].asString());
        precos.setMarca(jsonItem["marca"].asString());
        precos.setModelo(jsonItem["modelo"].asString());
        precos.setAnoModelo(jsonItem["ano_modelo"].asInt());
        precos.setCombustivel(jsonItem["combustivel"].asString());
        precos.setCodigoFipe(jsonItem["codigo_fipe"].asString());
        precos.setMesReferencia(jsonItem["mes_referencia"].asString());
        precos.setTipoVeiculo(jsonItem["tipo_veiculo"].asInt());
        precos.setSiglaCombustivel(jsonItem["sigla_combustivel"].asString());

        precosResponse.precos.push_back(precos);
      }
    }

    callback(precosResponse);
  });
}