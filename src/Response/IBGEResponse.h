#ifndef IBGE_RESPONSE_H
#define IBGE_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>

class IBGEMunicipios : public BaseResponse, public JsonSerialize {
  private:
  std::string nome;
  std::string codigo_ibge;

  public:
  const std::string &getNome() const {
    return nome;
  }
  const std::string &getCodigoIbge() const {
    return codigo_ibge;
  }

  void setNome(const std::string &n) {
    nome = n;
  }

  void setCodigoIbge(const std::string &c) {
    codigo_ibge = c;
  }

  Json::Value toJson() const override {
    Json::Value jsonValue;
    jsonValue["nome"] = nome;
    jsonValue["codigo_ibge"] = codigo_ibge;
    return jsonValue;
  }
};

class Regiao : public BaseResponse, public JsonSerialize {
  private:
  std::string id;
  std::string sigla;
  std::string nome;

  public:
  const std::string &getId() const {
    return id;
  }
  const std::string &getSigla() const {
    return sigla;
  }
  const std::string &getNome() const {
    return nome;
  }

  void setId(const std::string &i) {
    id = i;
  }
  void setSigla(const std::string &s) {
    sigla = s;
  }
  void setNome(const std::string &n) {
    nome = n;
  }

  Json::Value toJson() const override {
    Json::Value jsonValue;
    jsonValue["id"] = id;
    jsonValue["sigla"] = sigla;
    jsonValue["nome"] = nome;
    return jsonValue;
  }
};

class IBGEMunicipiosResponse : public BaseResponse, public JsonSerialize {
  public:
  std::vector<IBGEMunicipios> ibgeMunicipios;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : ibgeMunicipios) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

class IBGERegioesResponse : public BaseResponse, public JsonSerialize {
  public:
  std::vector<Regiao> regioes;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : regioes) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

#endif // IBGE_RESPONSE_H