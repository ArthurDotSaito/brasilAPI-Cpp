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
          cidade.setNome(jsonCptec["nome"].asString());
          cidade.setEstado(jsonCptec["estado"].asString());
          cidade.setId(jsonCptec["id"].asInt());
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
          cidade.setNome(jsonCptec["nome"].asString());
          cidade.setEstado(jsonCptec["estado"].asString());
          cidade.setId(jsonCptec["id"].asInt());
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

          capitais.setCodigoIcao(jsonCptec["codigo_icao"].asString());
          capitais.setAtualizadoEm(jsonCptec["atualizado_em"].asString());
          capitais.setPressaoAtmosferica(jsonCptec["pressao_atmosferica"].asString());
          capitais.setVisibilidade(jsonCptec["visibilidade"].asString());
          capitais.setVento(jsonCptec["vento"].asInt());
          capitais.setDirecaoVento(jsonCptec["direcao_vento"].asInt());
          capitais.setUmidade(jsonCptec["umidade"].asInt());
          capitais.setCondicao(jsonCptec["condicao"].asString());
          capitais.setCondicaoDesc(jsonCptec["condicao_Desc"].asString());
          capitais.setTemp(jsonCptec["temp"].asInt());

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
        cptecAeroporto.setCodigoIcao(jsonResponse["codigo_icao"].asString());
        cptecAeroporto.setAtualizadoEm(jsonResponse["atualizado_em"].asString());
        cptecAeroporto.setPressaoAtmosferica(jsonResponse["pressao_atmosferica"].asString());
        cptecAeroporto.setVisibilidade(jsonResponse["visibilidade"].asString());
        cptecAeroporto.setVento(jsonResponse["vento"].asInt());
        cptecAeroporto.setDirecaoVento(jsonResponse["direcao_vento"].asInt());
        cptecAeroporto.setUmidade(jsonResponse["umidade"].asInt());
        cptecAeroporto.setCondicao(jsonResponse["condicao"].asString());
        cptecAeroporto.setCondicaoDesc(jsonResponse["condicao_Desc"].asString());
        cptecAeroporto.setTemp(jsonResponse["temp"].asInt());
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
        cidadeClimaResponse.setCidade(jsonResponse["cidade"].asString());
        cidadeClimaResponse.setEstado(jsonResponse["estado"].asString());
        cidadeClimaResponse.setAtualizadoEm(jsonResponse["atualizado_em"].asString());

        const Json::Value jsonClimaArray = jsonResponse["clima"];
        for (const auto &jsonClima : jsonClimaArray) {
          ClimaDiario climaDiario;
          climaDiario.setData(jsonClima["data"].asString());
          climaDiario.setCondicao(jsonClima["condicao"].asString());
          climaDiario.setMin(jsonClima["min"].asInt());
          climaDiario.setMax(jsonClima["max"].asInt());
          climaDiario.setIndiceUv(jsonClima["indice_uv"].asInt());
          climaDiario.setCondicaoDesc(jsonClima["condicao_desc"].asString());
          cidadeClimaResponse.addClimaDiario(climaDiario);
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
      ensureSuccess(response, "/api/cptec/v1/clima/{cityCode}/{days}");
      std::string responseBody = std::string(response->getBody());

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse)) {
        CidadeClimaResponse cidadeClimaResponse;
        cidadeClimaResponse.setCidade(jsonResponse["cidade"].asString());
        cidadeClimaResponse.setEstado(jsonResponse["estado"].asString());
        cidadeClimaResponse.setAtualizadoEm(jsonResponse["atualizado_em"].asString());

        const Json::Value jsonClimaArray = jsonResponse["clima"];
        for (const auto &jsonClima : jsonClimaArray) {
          ClimaDiario climaDiario;
          climaDiario.setData(jsonClima["data"].asString());
          climaDiario.setCondicao(jsonClima["condicao"].asString());
          climaDiario.setMin(jsonClima["min"].asInt());
          climaDiario.setMax(jsonClima["max"].asInt());
          climaDiario.setIndiceUv(jsonClima["indice_uv"].asInt());
          climaDiario.setCondicaoDesc(jsonClima["condicao_desc"].asString());
          cidadeClimaResponse.addClimaDiario(climaDiario);
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

void CptecHandler::previsaoOceanicaCidade(int cityCode, std::function<void(const CptecPrevisaoOceanica &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cptec/v1/ondas/" + std::to_string(cityCode));
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cptec/v1/ondas/{cityCode}");
      std::string responseBody = std::string(response->getBody());

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse)) {
        CptecPrevisaoOceanica previsaoOceanica;
        previsaoOceanica.setCidade(jsonResponse["cidade"].asString());
        previsaoOceanica.setEstado(jsonResponse["estado"].asString());
        previsaoOceanica.setAtualizadoEm(jsonResponse["atualizado_em"].asString());

        const Json::Value jsonOndasArray = jsonResponse["ondas"];
        for (const auto &jsonOnda : jsonOndasArray) {
          Onda onda;
          onda.setData(jsonOnda["data"].asString());

          const Json::Value jsonDadosOndasArray = jsonOnda["dados_ondas"];
          for (const auto &jsonDadosOnda : jsonDadosOndasArray) {
            DadosOnda dadosOnda;
            dadosOnda.setVento(jsonDadosOnda["vento"].asFloat());
            dadosOnda.setDirecaoVento(jsonDadosOnda["direcao_vento"].asString());
            dadosOnda.setDirecaoVentoDesc(jsonDadosOnda["direcao_vento_desc"].asString());
            dadosOnda.setAlturaOnda(jsonDadosOnda["altura_onda"].asFloat());
            dadosOnda.setDirecaoOnda(jsonDadosOnda["direcao_onda"].asString());
            dadosOnda.setDirecaoOndaDesc(jsonDadosOnda["direcao_onda_desc"].asString());
            dadosOnda.setAgitation(jsonDadosOnda["agitation"].asString());
            dadosOnda.setHora(jsonDadosOnda["hora"].asString());
            onda.addDadosOnda(dadosOnda);
          }

          previsaoOceanica.addOnda(onda);
        }

        callback(previsaoOceanica);
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

void CptecHandler::previsaoOceanicaCidadeSeisDias(
    int cityCode, int days, std::function<void(const CptecPrevisaoOceanica &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cptec/v1/ondas/" + std::to_string(cityCode) + "/" + std::to_string(days));
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cptec/v1/ondas/{cityCode}");
      std::string responseBody = std::string(response->getBody());

      Json::Value jsonResponse;
      Json::Reader reader;
      if (reader.parse(responseBody, jsonResponse)) {
        CptecPrevisaoOceanica previsaoOceanica;
        previsaoOceanica.setCidade(jsonResponse["cidade"].asString());
        previsaoOceanica.setEstado(jsonResponse["estado"].asString());
        previsaoOceanica.setAtualizadoEm(jsonResponse["atualizado_em"].asString());

        const Json::Value jsonOndasArray = jsonResponse["ondas"];
        for (const auto &jsonOnda : jsonOndasArray) {
          Onda onda;
          onda.setData(jsonOnda["data"].asString());

          const Json::Value jsonDadosOndasArray = jsonOnda["dados_ondas"];
          for (const auto &jsonDadosOnda : jsonDadosOndasArray) {
            DadosOnda dadosOnda;
            dadosOnda.setVento(jsonDadosOnda["vento"].asFloat());
            dadosOnda.setDirecaoVento(jsonDadosOnda["direcao_vento"].asString());
            dadosOnda.setDirecaoVentoDesc(jsonDadosOnda["direcao_vento_desc"].asString());
            dadosOnda.setAlturaOnda(jsonDadosOnda["altura_onda"].asFloat());
            dadosOnda.setDirecaoOnda(jsonDadosOnda["direcao_onda"].asString());
            dadosOnda.setDirecaoOndaDesc(jsonDadosOnda["direcao_onda_desc"].asString());
            dadosOnda.setAgitation(jsonDadosOnda["agitation"].asString());
            dadosOnda.setHora(jsonDadosOnda["hora"].asString());
            onda.addDadosOnda(dadosOnda);
          }

          previsaoOceanica.addOnda(onda);
        }

        callback(previsaoOceanica);
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
