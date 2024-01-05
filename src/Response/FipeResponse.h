#ifndef FIPE_RESPONSE_H
#define FIPE_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>

class Marcas : public BaseResponse {
  private:
  std::string nome;
  std::string valor;

  public:
  const std::string &getNome() const {
    return nome;
  }
  const std::string &getValor() const {
    return valor;
  }

  void setNome(const std::string &n) {
    nome = n;
  }

  void setValor(const std::string &v) {
    valor = v;
  }

  Json::Value toJson() const {
    Json::Value jsonValue;
    jsonValue["nome"] = nome;
    jsonValue["valor"] = valor;
    return jsonValue;
  }
};

class Precos : public BaseResponse {
  private:
  std::string valor;
  std::string marca;
  std::string modelo;
  int anoModelo;
  std::string combustivel;
  std::string codigoFipe;
  std::string mesReferencia;
  int tipoVeiculo;
  std::string siglaCombustivel;
  std::string dataConsulta;

  public:
  const std::string &getValor() const {
    return valor;
  }
  const std::string &getMarca() const {
    return marca;
  }
  const std::string &getModelo() const {
    return modelo;
  }
  int getAnoModelo() const {
    return anoModelo;
  }
  const std::string &getCombustivel() const {
    return combustivel;
  }
  const std::string &getCodigoFipe() const {
    return codigoFipe;
  }
  const std::string &getMesReferencia() const {
    return mesReferencia;
  }
  int getTipoVeiculo() const {
    return tipoVeiculo;
  }
  const std::string &getSiglaCombustivel() const {
    return siglaCombustivel;
  }
  const std::string &getDataConsulta() const {
    return dataConsulta;
  }

  void setValor(const std::string &v) {
    valor = v;
  }
  void setMarca(const std::string &m) {
    marca = m;
  }
  void setModelo(const std::string &m) {
    modelo = m;
  }
  void setAnoModelo(int am) {
    anoModelo = am;
  }
  void setCombustivel(const std::string &c) {
    combustivel = c;
  }
  void setCodigoFipe(const std::string &cf) {
    codigoFipe = cf;
  }
  void setMesReferencia(const std::string &mr) {
    mesReferencia = mr;
  }
  void setTipoVeiculo(int tv) {
    tipoVeiculo = tv;
  }
  void setSiglaCombustivel(const std::string &sc) {
    siglaCombustivel = sc;
  }
  void setDataConsulta(const std::string &dc) {
    dataConsulta = dc;
  }

  Json::Value toJson() const {
    Json::Value jsonValue;
    jsonValue["valor"] = valor;
    jsonValue["marca"] = marca;
    jsonValue["modelo"] = modelo;
    jsonValue["anoModelo"] = anoModelo;
    jsonValue["combustivel"] = combustivel;
    jsonValue["codigoFipe"] = codigoFipe;
    jsonValue["mesReferencia"] = mesReferencia;
    jsonValue["tipoVeiculo"] = tipoVeiculo;
    jsonValue["siglaCombustivel"] = siglaCombustivel;
    jsonValue["dataConsulta"] = dataConsulta;
    return jsonValue;
  }
};

class FipeMarcas : public BaseResponse, public JsonSerialize {
  public:
  std::vector<Marcas> fipe;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : fipe) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

class FipePrecos : public BaseResponse, public JsonSerialize {
  public:
  std::vector<Precos> precos;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : precos) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

#endif // FIPE_RESPONSE_H