#include "CptecHandler.h"
#include "Utils/BrasilAPIException.h"

void CptecHandler::listAllCities(std::function<void(const CptecCidadesResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cptec/v1/cidade");
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cptec/v1/cidade");
      std::string responseBody = std::string(response->getBody());

      CptecCidadesResponse cptecCidadesResponse;
      cptecCidadesResponse.calledURL = fullUrl;
      cptecCidadesResponse.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
        for (const auto &jsonCptec : jsonResponse) {
          CptecCidades cidade;
          cidade.nome = jsonCptec["nome"].asString();
          cidade.estado = jsonCptec["estado"].asString();
          cidade.id = jsonCptec["id"].asInt();
          cptecCidadesResponse.cptecCidades.push_back(cidade);
        }
      }
      callback(cptecCidadesResponse);

    } catch (const BrasilAPIException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}

void CptecHandler::searchByTerms(std::string cityName, std::function<void(const CptecCidadesResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cptec/v1/cidade/" + cityName);
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cptec/v1/cidade/{cityName}");
      std::string responseBody = std::string(response->getBody());

      CptecCidadesResponse cptecCidadesResponse;
      cptecCidadesResponse.calledURL = fullUrl;
      cptecCidadesResponse.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
        for (const auto &jsonCptec : jsonResponse) {
          CptecCidades cidade;
          cidade.nome = jsonCptec["nome"].asString();
          cidade.estado = jsonCptec["estado"].asString();
          cidade.id = jsonCptec["id"].asInt();
          cptecCidadesResponse.cptecCidades.push_back(cidade);
        }
      }
      callback(cptecCidadesResponse);
    } catch (const BrasilAPIException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}

void CptecHandler::getCapitais(std::function<void(const CptecCapitaisResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cptec/v1/clima/capital");
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cptec/v1/clima/capital");
      std::string responseBody = std::string(response->getBody());

      CptecCapitaisResponse cptecCapitaisResponse;
      cptecCapitaisResponse.calledURL = fullUrl;
      cptecCapitaisResponse.jsonResponse = responseBody;

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
        for (const auto &jsonCptec : jsonResponse) {
          CptecCapitais capitais;

          capitais.codigo_icao = jsonCptec["codigo_icao"].asString();
          capitais.atualizado_em = jsonCptec["atualizado_em"].asString();
          capitais.pressao_atmosferica = jsonCptec["pressao_atmosferica"].asString();
          capitais.visibilidade = jsonCptec["visibilidade"].asString();
          capitais.vento = jsonCptec["vento"].asInt();
          capitais.direcao_vento = jsonCptec["direcao_vento"].asInt();
          capitais.umidade = jsonCptec["umidade"].asInt();
          capitais.condicao = jsonCptec["condicao"].asString();
          capitais.condicao_Desc = jsonCptec["condicao_Desc"].asString();
          capitais.temp = jsonCptec["temp"].asInt();

          cptecCapitaisResponse.cptecCapitais.push_back(capitais);
        }
      }
      callback(cptecCapitaisResponse);

    } catch (const BrasilAPIException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}

void CptecHandler::getCondicoesAeroporto(std::string icao, std::function<void(const CptecAeroporto &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cptec/v1/clima/aeroporto/" + icao);
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cptec/v1/clima/aeroporto/{icaoCode}");
      std::string responseBody = std::string(response->getBody());

      Json::Value jsonResponse;
      Json::Reader reader;
      CptecAeroporto cptecAeroporto;
      if (reader.parse(responseBody, jsonResponse)) {
        cptecAeroporto.codigo_icao = jsonResponse["codigo_icao"].asString();
        cptecAeroporto.atualizado_em = jsonResponse["atualizado_em"].asString();
        cptecAeroporto.pressao_atmosferica = jsonResponse["pressao_atmosferica"].asString();
        cptecAeroporto.visibilidade = jsonResponse["visibilidade"].asString();
        cptecAeroporto.vento = jsonResponse["vento"].asInt();
        cptecAeroporto.direcao_vento = jsonResponse["direcao_vento"].asInt();
        cptecAeroporto.umidade = jsonResponse["umidade"].asInt();
        cptecAeroporto.condicao = jsonResponse["condicao"].asString();
        cptecAeroporto.condicao_Desc = jsonResponse["condicao_Desc"].asString();
        cptecAeroporto.temp = jsonResponse["temp"].asInt();

        cptecAeroporto.calledURL = fullUrl;
        cptecAeroporto.jsonResponse = responseBody;
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }
      callback(cptecAeroporto);

    } catch (const BrasilAPIException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}

void CptecHandler::getCidadesClimaByCidade(int cityCode, std::function<void(const CidadeClimaResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cptec/v1/clima/previsao/" + std::to_string(cityCode));
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cptec/v1/clima/clima/{cityCode}");
      std::string responseBody = std::string(response->getBody());

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse)) {
        CidadeClimaResponse cidadeClimaResponse;
        cidadeClimaResponse.cidade = jsonResponse["cidade"].asString();
        cidadeClimaResponse.estado = jsonResponse["estado"].asString();
        cidadeClimaResponse.atualizado_em = jsonResponse["atualizado_em"].asString();

        const Json::Value jsonClimaArray = jsonResponse["clima"];
        for (const auto &jsonClima : jsonClimaArray) {
          ClimaDiario climaDiario;
          climaDiario.data = jsonClima["data"].asString();
          climaDiario.condicao = jsonClima["condicao"].asString();
          climaDiario.min = jsonClima["min"].asInt();
          climaDiario.max = jsonClima["max"].asInt();
          climaDiario.indice_uv = jsonClima["indice_uv"].asInt();
          climaDiario.condicao_desc = jsonClima["condicao_desc"].asString();
          cidadeClimaResponse.clima.push_back(climaDiario);
        }

        callback(cidadeClimaResponse);
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

void CptecHandler::previsaoCidadeSeisDias(int cityCode, int days, std::function<void(const CidadeClimaResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cptec/v1/clima/previsao/" + std::to_string(cityCode) + "/" + std::to_string(days));
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cptec/v1/clima/clima/{cityCode}/{days}");
      std::string responseBody = std::string(response->getBody());

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse)) {
        CidadeClimaResponse cidadeClimaResponse;
        cidadeClimaResponse.cidade = jsonResponse["cidade"].asString();
        cidadeClimaResponse.estado = jsonResponse["estado"].asString();
        cidadeClimaResponse.atualizado_em = jsonResponse["atualizado_em"].asString();

        const Json::Value jsonClimaArray = jsonResponse["clima"];
        for (const auto &jsonClima : jsonClimaArray) {
          ClimaDiario climaDiario;
          climaDiario.data = jsonClima["data"].asString();
          climaDiario.condicao = jsonClima["condicao"].asString();
          climaDiario.min = jsonClima["min"].asInt();
          climaDiario.max = jsonClima["max"].asInt();
          climaDiario.indice_uv = jsonClima["indice_uv"].asInt();
          climaDiario.condicao_desc = jsonClima["condicao_desc"].asString();
          cidadeClimaResponse.clima.push_back(climaDiario);
        }

        callback(cidadeClimaResponse);
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