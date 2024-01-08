#ifndef CIDADE_CLIMA_RESPONSE_H
#define CIDADE_CLIMA_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>

class ClimaDiario {
  private:
  std::string data;
  std::string condicao;
  int min;
  int max;
  int indice_uv;
  std::string condicao_desc;

  public:
  const std::string &getData() const {
    return data;
  }
  const std::string &getCondicao() const {
    return condicao;
  }
  int getMin() const {
    return min;
  }
  int getMax() const {
    return max;
  }
  int getIndiceUv() const {
    return indice_uv;
  }
  const std::string &getCondicaoDesc() const {
    return condicao_desc;
  }

  void setData(const std::string &d) {
    data = d;
  }
  void setCondicao(const std::string &c) {
    condicao = c;
  }
  void setMin(int m) {
    min = m;
  }
  void setMax(int m) {
    max = m;
  }
  void setIndiceUv(int i) {
    indice_uv = i;
  }
  void setCondicaoDesc(const std::string &c) {
    condicao_desc = c;
  }

  Json::Value toJson() const {
    Json::Value jsonClima;
    jsonClima["data"] = data;
    jsonClima["condicao"] = condicao;
    jsonClima["min"] = min;
    jsonClima["max"] = max;
    jsonClima["indice_uv"] = indice_uv;
    jsonClima["condicao_desc"] = condicao_desc;
    return jsonClima;
  }
};

class CidadeClimaResponse : public BaseResponse, public JsonSerialize {
  private:
  std::string cidade;
  std::string estado;
  std::string atualizado_em;
  std::vector<ClimaDiario> clima;

  public:
  const std::string &getCidade() const {
    return cidade;
  }
  const std::string &getEstado() const {
    return estado;
  }
  const std::string &getAtualizadoEm() const {
    return atualizado_em;
  }
  const std::vector<ClimaDiario> &getClima() const {
    return clima;
  }

  void setCidade(const std::string &c) {
    cidade = c;
  }
  void setEstado(const std::string &e) {
    estado = e;
  }
  void setAtualizadoEm(const std::string &a) {
    atualizado_em = a;
  }
  void setClima(const std::vector<ClimaDiario> &c) {
    clima = c;
  }

  void addClimaDiario(const ClimaDiario &climaDiario) {
    clima.push_back(climaDiario);
  }

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : clima) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

#endif // CIDADE_CLIMA_RESPONSE_H
