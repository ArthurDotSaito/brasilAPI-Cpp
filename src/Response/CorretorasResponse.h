#ifndef CORRETORAS_RESPONSE_H
#define CORRETORAS_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>

class Corretoras : public BaseResponse, public JsonSerialize {
  private:
  std::string bairro;
  std::string cep;
  std::string cnpj;
  std::string codigo_cvm;
  std::string complemento;
  std::string data_inicio_situacao;
  std::string data_patrimonio_liquido;
  std::string data_registro;
  std::string email;
  std::string logradouro;
  std::string municipio;
  std::string nome_social;
  std::string nome_comercial;
  std::string pais;
  std::string status;
  std::string telefone;
  std::string type;
  std::string uf;
  std::string valor_patrimonio_liquido;

  public:
  std::string getBairro() const {
    return bairro;
  }
  std::string getCep() const {
    return cep;
  }
  std::string getCnpj() const {
    return cnpj;
  }
  std::string getCodigoCvm() const {
    return codigo_cvm;
  }
  std::string getComplemento() const {
    return complemento;
  }
  std::string getDataInicioSituacao() const {
    return data_inicio_situacao;
  }
  std::string getDataPatrimonioLiquido() const {
    return data_patrimonio_liquido;
  }
  std::string getDataRegistro() const {
    return data_registro;
  }
  std::string getEmail() const {
    return email;
  }
  std::string getLogradouro() const {
    return logradouro;
  }
  std::string getMunicipio() const {
    return municipio;
  }
  std::string getNomeSocial() const {
    return nome_social;
  }
  std::string getNomeComercial() const {
    return nome_comercial;
  }
  std::string getPais() const {
    return pais;
  }
  std::string getStatus() const {
    return status;
  }
  std::string getTelefone() const {
    return telefone;
  }
  std::string getType() const {
    return type;
  }
  std::string getUf() const {
    return uf;
  }
  std::string getValorPatrimonioLiquido() const {
    return valor_patrimonio_liquido;
  }

  void setBairro(const std::string &value) {
    bairro = value;
  }
  void setCep(const std::string &value) {
    cep = value;
  }
  void setCnpj(const std::string &value) {
    cnpj = value;
  }
  void setCodigoCvm(const std::string &value) {
    codigo_cvm = value;
  }
  void setComplemento(const std::string &value) {
    complemento = value;
  }
  void setDataInicioSituacao(const std::string &value) {
    data_inicio_situacao = value;
  }
  void setDataPatrimonioLiquido(const std::string &value) {
    data_patrimonio_liquido = value;
  }
  void setDataRegistro(const std::string &value) {
    data_registro = value;
  }
  void setEmail(const std::string &value) {
    email = value;
  }
  void setLogradouro(const std::string &value) {
    logradouro = value;
  }
  void setMunicipio(const std::string &value) {
    municipio = value;
  }
  void setNomeSocial(const std::string &value) {
    nome_social = value;
  }
  void setNomeComercial(const std::string &value) {
    nome_comercial = value;
  }
  void setPais(const std::string &value) {
    pais = value;
  }
  void setStatus(const std::string &value) {
    status = value;
  }
  void setTelefone(const std::string &value) {
    telefone = value;
  }
  void setType(const std::string &value) {
    type = value;
  }
  void setUf(const std::string &value) {
    uf = value;
  }
  void setValorPatrimonioLiquido(const std::string &value) {
    valor_patrimonio_liquido = value;
  }

  Json::Value toJson() const {
    Json::Value jsonCorretoras;
    jsonCorretoras["bairro"] = bairro;
    jsonCorretoras["cep"] = cep;
    jsonCorretoras["cnpj"] = cnpj;
    jsonCorretoras["codigo_cvm"] = codigo_cvm;
    jsonCorretoras["complemento"] = complemento;
    jsonCorretoras["data_inicio_situacao"] = data_inicio_situacao;
    jsonCorretoras["data_patrimonio_liquido"] = data_patrimonio_liquido;
    jsonCorretoras["data_registro"] = data_registro;
    jsonCorretoras["email"] = email;
    jsonCorretoras["logradouro"] = logradouro;
    jsonCorretoras["municipio"] = municipio;
    jsonCorretoras["nome_social"] = nome_social;
    jsonCorretoras["nome_comercial"] = nome_comercial;
    jsonCorretoras["pais"] = pais;
    jsonCorretoras["status"] = status;
    jsonCorretoras["telefone"] = telefone;
    jsonCorretoras["type"] = type;
    jsonCorretoras["uf"] = uf;
    jsonCorretoras["valor_patrimonio_liquido"] = valor_patrimonio_liquido;
    return jsonCorretoras;
  }
};

class CorretorasResponse : public BaseResponse, public JsonSerialize {
  public:
  std::vector<Corretoras> corretoras;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : corretoras) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

#endif // CORRETORAS_RESPONSE_H