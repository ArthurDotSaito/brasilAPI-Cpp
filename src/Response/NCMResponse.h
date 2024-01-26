#ifndef NCM_RESPONSE_H
#define NCM_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>
#include <vector>

class NCM : public BaseResponse, public JsonSerialize {
  private:
  std::string codigo;
  std::string descricao;
  std::string data_inicio;
  std::string data_fim;
  std::string tipo_ato;
  std::string numero_ato;
  std::string ano_ato;

  public:
  const std::string &getCodigo() const {
    return codigo;
  }
  const std::string &getDescricao() const {
    return descricao;
  }
  const std::string &getDataInicio() const {
    return data_inicio;
  }
  const std::string &getDataFim() const {
    return data_fim;
  }
  const std::string &getTipoAto() const {
    return tipo_ato;
  }
  const std::string &getNumeroAto() const {
    return numero_ato;
  }
  const std::string &getAnoAto() const {
    return ano_ato;
  }

  void setCodigo(const std::string &codigo) {
    this->codigo = codigo;
  }
  void setDescricao(const std::string &descricao) {
    this->descricao = descricao;
  }
  void setDataInicio(const std::string &data_inicio) {
    this->data_inicio = data_inicio;
  }
  void setDataFim(const std::string &data_fim) {
    this->data_fim = data_fim;
  }
  void setTipoAto(const std::string &tipo_ato) {
    this->tipo_ato = tipo_ato;
  }
  void setNumeroAto(const std::string &numero_ato) {
    this->numero_ato = numero_ato;
  }
  void setAnoAto(const std::string &ano_ato) {
    this->ano_ato = ano_ato;
  }

  Json::Value toJson() const override {
    Json::Value jsonValue;
    jsonValue["codigo"] = codigo;
    jsonValue["descricao"] = descricao;
    jsonValue["data_inicio"] = data_inicio;
    jsonValue["data_fim"] = data_fim;
    jsonValue["tipo_ato"] = tipo_ato;
    jsonValue["numero_ato"] = numero_ato;
    jsonValue["ano_ato"] = ano_ato;

    return jsonValue;
  }
};

class NCMResponse : public BaseResponse, public JsonSerialize {
  public:
  std::vector<NCM> ncm;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : ncm) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};
#endif // NCM_RESPONSE_H