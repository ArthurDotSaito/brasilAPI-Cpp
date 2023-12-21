#ifndef CPTECOCEANO_RESPONSE_H
#define CPTECOCEANO_RESPONSE_H

#include "BaseResponse.h"
#include <json/json.h>
#include <string>
#include <vector>

class DadosOnda {
  public:
  float vento;
  std::string direcao_vento;
  std::string direcao_vento_desc;
  float altura_onda;
  std::string direcao_onda;
  std::string direcao_onda_desc;
  std::string agitation;
  std::string hora;

  Json::Value toJson() const {
    Json::Value jsonDadosOnda;
    jsonDadosOnda["vento"] = vento;
    jsonDadosOnda["direcao_vento"] = direcao_vento;
    jsonDadosOnda["direcao_vento_desc"] = direcao_vento_desc;
    jsonDadosOnda["altura_onda"] = altura_onda;
    jsonDadosOnda["direcao_onda"] = direcao_onda;
    jsonDadosOnda["direcao_onda_desc"] = direcao_onda_desc;
    jsonDadosOnda["agitation"] = agitation;
    jsonDadosOnda["hora"] = hora;
    return jsonDadosOnda;
  }
};

class Onda {
  public:
  std::string data;
  std::vector<DadosOnda> dados_ondas;

  Json::Value toJson() const {
    Json::Value jsonOnda;
    jsonOnda["data"] = data;
    Json::Value jsonDadosOndasArray(Json::arrayValue);
    for (const auto &dadosOnda : dados_ondas) {
      jsonDadosOndasArray.append(dadosOnda.toJson());
    }
    jsonOnda["dados_ondas"] = jsonDadosOndasArray;
    return jsonOnda;
  }
};

class CptecPrevisaoOceanica : public BaseResponse {
  public:
  std::string cidade;
  std::string estado;
  std::string atualizado_em;
  std::vector<Onda> ondas;

  Json::Value toJson() const {
    Json::Value cptecPrevisaoOceanica;
    cptecPrevisaoOceanica["cidade"] = cidade;
    cptecPrevisaoOceanica["estado"] = estado;
    cptecPrevisaoOceanica["atualizado_em"] = atualizado_em;

    Json::Value jsonOndasArray(Json::arrayValue);
    for (const auto &onda : ondas) {
      jsonOndasArray.append(onda.toJson());
    }
    cptecPrevisaoOceanica["ondas"] = jsonOndasArray;
    return cptecPrevisaoOceanica;
  }

  std::string serialize() const {
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, this->toJson());
  }
};

class CptecPrevisaoOceanicaResponse : public BaseResponse {
  public:
  std::vector<CptecPrevisaoOceanica> cptecPrevisaoOceanica;

  std::string serialize() const {
    Json::Value jsonRoot;
    for (const auto &cptecPrevisaoOceanica : cptecPrevisaoOceanica) {
      jsonRoot.append(cptecPrevisaoOceanica.toJson());
    }
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, jsonRoot);
  }
};

#endif // CPTECOCEANO_RESPONSE_H
