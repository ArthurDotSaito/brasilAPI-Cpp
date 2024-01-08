#ifndef CPTECCAPITAIS_RESPONSE_H
#define CPTECCAPITAIS_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>

class CptecCapitais : public BaseResponse, public JsonSerialize {
  private:
  std::string codigo_icao;
  std::string atualizado_em;
  std::string pressao_atmosferica;
  std::string visibilidade;
  int vento;
  int direcao_vento;
  int umidade;
  std::string condicao;
  std::string condicao_Desc;
  int temp;

  public:
  std::string getCodigoIcao() const {
    return codigo_icao;
  }
  std::string getAtualizadoEm() const {
    return atualizado_em;
  }
  std::string getPressaoAtmosferica() const {
    return pressao_atmosferica;
  }
  std::string getVisibilidade() const {
    return visibilidade;
  }
  int getVento() const {
    return vento;
  }
  int getDirecaoVento() const {
    return direcao_vento;
  }
  int getUmidade() const {
    return umidade;
  }
  std::string getCondicao() const {
    return condicao;
  }
  std::string getCondicaoDesc() const {
    return condicao_Desc;
  }
  int getTemp() const {
    return temp;
  }

  void setCodigoIcao(const std::string &c) {
    codigo_icao = c;
  }
  void setAtualizadoEm(const std::string &a) {
    atualizado_em = a;
  }
  void setPressaoAtmosferica(const std::string &p) {
    pressao_atmosferica = p;
  }
  void setVisibilidade(const std::string &v) {
    visibilidade = v;
  }
  void setVento(const int &v) {
    vento = v;
  }
  void setDirecaoVento(const int &d) {
    direcao_vento = d;
  }
  void setUmidade(const int &u) {
    umidade = u;
  }
  void setCondicao(const std::string &c) {
    condicao = c;
  }
  void setCondicaoDesc(const std::string &c) {
    condicao_Desc = c;
  }
  void setTemp(const int &t) {
    temp = t;
  }

  Json::Value toJson() const override {
    Json::Value jsonCptecCapitais;
    jsonCptecCapitais["codigo_icao"] = codigo_icao;
    jsonCptecCapitais["atualizado_em"] = atualizado_em;
    jsonCptecCapitais["pressao_atmosferica"] = pressao_atmosferica;
    jsonCptecCapitais["visibilidade"] = visibilidade;
    jsonCptecCapitais["vento"] = vento;
    jsonCptecCapitais["direcao_vento"] = direcao_vento;
    jsonCptecCapitais["umidade"] = umidade;
    jsonCptecCapitais["condicao"] = condicao;
    jsonCptecCapitais["condicao_Desc"] = condicao_Desc;
    jsonCptecCapitais["temp"] = temp;
    return jsonCptecCapitais;
  }
};

class CptecCapitaisResponse : public BaseResponse, public JsonSerialize {
  public:
  std::vector<CptecCapitais> cptecCapitais;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : cptecCapitais) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

#endif // CPTECCAPITAIS_RESPONSE_H