#ifndef CPTECCIDADES_RESPONSE_H
#define CPTECCIDADES_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>

class CptecCidades : public BaseResponse, public JsonSerialize {
  private:
  std::string nome;
  std::string estado;
  int id;

  public:
  std::string getNome() const {
    return nome;
  }
  std::string getEstado() const {
    return estado;
  }
  int getId() const {
    return id;
  }

  void setNome(const std::string &n) {
    nome = n;
  }
  void setEstado(const std::string &e) {
    estado = e;
  }
  void setId(const int &i) {
    id = i;
  }

  Json::Value toJson() const {
    Json::Value jsonCptecCidades;
    jsonCptecCidades["nome"] = nome;
    jsonCptecCidades["estado"] = estado;
    jsonCptecCidades["id"] = id;
    return jsonCptecCidades;
  }
};

class CptecCidadesResponse : public BaseResponse, public JsonSerialize {
  public:
  std::vector<CptecCidades> cptecCidades;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : cptecCidades) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

#endif // CPTECCIDADES_RESPONSE_H