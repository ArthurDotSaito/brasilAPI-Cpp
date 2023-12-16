#ifndef CORRETORAS_RESPONSE_H
#define CORRETORAS_RESPONSE_H

#include "BaseResponse.h"
#include <json/json.h>
#include <string>

class Corretoras : public BaseResponse {
  public:
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

  std::string serialize() const {
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

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, jsonCorretoras);
  }
};

class CorretorasResponse : public BaseResponse {
  public:
  std::vector<Corretoras> corretoras;

  std::string serialize() const {
    Json::Value jsonRoot;

    for (const auto &corretoras : corretoras) {
      Json::Value jsonCorretoras;
      jsonCorretoras["bairro"] = corretoras.bairro;
      jsonCorretoras["cep"] = corretoras.cep;
      jsonCorretoras["cnpj"] = corretoras.cnpj;
      jsonCorretoras["codigo_cvm"] = corretoras.codigo_cvm;
      jsonCorretoras["complemento"] = corretoras.complemento;
      jsonCorretoras["data_inicio_situacao"] = corretoras.data_inicio_situacao;
      jsonCorretoras["data_patrimonio_liquido"] = corretoras.data_patrimonio_liquido;
      jsonCorretoras["data_registro"] = corretoras.data_registro;
      jsonCorretoras["email"] = corretoras.email;
      jsonCorretoras["logradouro"] = corretoras.logradouro;
      jsonCorretoras["municipio"] = corretoras.municipio;
      jsonCorretoras["nome_social"] = corretoras.nome_social;
      jsonCorretoras["nome_comercial"] = corretoras.nome_comercial;
      jsonCorretoras["pais"] = corretoras.pais;
      jsonCorretoras["status"] = corretoras.status;
      jsonCorretoras["telefone"] = corretoras.telefone;
      jsonCorretoras["type"] = corretoras.type;
      jsonCorretoras["uf"] = corretoras.uf;
      jsonCorretoras["valor_patrimonio_liquido"] = corretoras.valor_patrimonio_liquido;
      jsonRoot.append(jsonCorretoras);
    }

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, jsonRoot);
  }
};

#endif // CORRETORAS_RESPONSE_H