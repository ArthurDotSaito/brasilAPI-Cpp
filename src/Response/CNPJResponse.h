#ifndef CNPJ_RESPONSE_H
#define CNPJ_RESPONSE_H

#include "BaseResponse.h"
#include <json/json.h>
#include <optional>
#include <string>
#include <vector>

struct CNAE {
  int codigo;
  std::string descricao;
};

struct QSA {
  int identificador_de_socio;
  std::string nome_socio;
  std::string cnpj_cpf_do_socio;
  int codigo_qualificacao_socio;
  int percentual_capital_social;
  std::string data_entrada_sociedade;
  std::optional<std::string> cpf_representante_legal;
  std::optional<std::string> nome_representante_legal;
  std::optional<int> codigo_qualificacao_representante_legal;
};

class CNPJResponse : public BaseResponse {
  public:
  std::string cnpj;
  int identificador_matriz_filial;
  std::string descricao_matriz_filial;
  std::string razao_social;
  std::string nome_fantasia;
  int situacao_cadastral;
  std::string descricao_situacao_cadastral;
  std::string data_situacao_cadastral;
  int motivo_situacao_cadastral;
  std::optional<std::string> nome_cidade_exterior;
  int codigo_natureza_juridica;
  std::string data_inicio_atividade;
  int cnae_fiscal;
  std::string cnae_fiscal_descricao;
  std::string descricao_tipo_logradouro;
  std::string logradouro;
  std::string numero;
  std::string complemento;
  std::string bairro;
  int cep;
  std::string uf;
  int codigo_municipio;
  std::string municipio;
  std::string ddd_telefone_1;
  std::optional<std::string> ddd_telefone_2;
  std::optional<std::string> ddd_fax;
  int qualificacao_do_responsavel;
  double capital_social;
  int codigo_porte;
  std::string porte;
  std::string descricao_porte;
  bool opcao_pelo_simples;
  std::optional<std::string> data_opcao_pelo_simples;
  std::optional<std::string> data_exclusao_do_simples;
  bool opcao_pelo_mei;
  std::optional<std::string> situacao_especial;
  std::optional<std::string> data_situacao_especial;
  std::vector<CNAE> cnaes_secundarios;
  std::vector<QSA> qsa;

  std::string serialize() const {
    Json::Value jsonCNPJ;
    jsonCNPJ["cnpj"] = cnpj;
    jsonCNPJ["identificador_matriz_filial"] = identificador_matriz_filial;
    jsonCNPJ["descricao_matriz_filial"] = descricao_matriz_filial;
    jsonCNPJ["razao_social"] = razao_social;
    jsonCNPJ["nome_fantasia"] = nome_fantasia;
    jsonCNPJ["situacao_cadastral"] = situacao_cadastral;
    jsonCNPJ["descricao_situacao_cadastral"] = descricao_situacao_cadastral;
    jsonCNPJ["data_situacao_cadastral"] = data_situacao_cadastral;
    jsonCNPJ["motivo_situacao_cadastral"] = motivo_situacao_cadastral;
    jsonCNPJ["nome_cidade_exterior"] =
        nome_cidade_exterior.has_value() ? nome_cidade_exterior.value() : Json::Value(Json::nullValue);
    jsonCNPJ["codigo_natureza_juridica"] = codigo_natureza_juridica;
    jsonCNPJ["data_inicio_atividade"] = data_inicio_atividade;
    jsonCNPJ["cnae_fiscal"] = cnae_fiscal;
    jsonCNPJ["cnae_fiscal_descricao"] = cnae_fiscal_descricao;
    jsonCNPJ["descricao_tipo_logradouro"] = descricao_tipo_logradouro;
    jsonCNPJ["logradouro"] = logradouro;
    jsonCNPJ["numero"] = numero;
    jsonCNPJ["complemento"] = complemento;
    jsonCNPJ["bairro"] = bairro;
    jsonCNPJ["cep"] = cep;
    jsonCNPJ["uf"] = uf;
    jsonCNPJ["codigo_municipio"] = codigo_municipio;
    jsonCNPJ["municipio"] = municipio;
    jsonCNPJ["ddd_telefone_1"] = ddd_telefone_1;
    jsonCNPJ["ddd_telefone_2"] = ddd_telefone_2.has_value() ? ddd_telefone_2.value() : Json::Value(Json::nullValue);
    jsonCNPJ["ddd_fax"] = ddd_fax.has_value() ? ddd_fax.value() : Json::Value(Json::nullValue);
    jsonCNPJ["qualificacao_do_responsavel"] = qualificacao_do_responsavel;
    jsonCNPJ["capital_social"] = capital_social;
    jsonCNPJ["codigo_porte"] = codigo_porte;
    jsonCNPJ["porte"] = porte;
    jsonCNPJ["descricao_porte"] = descricao_porte;
    jsonCNPJ["opcao_pelo_simples"] = opcao_pelo_simples;
    jsonCNPJ["data_opcao_pelo_simples"] =
        data_opcao_pelo_simples.has_value() ? data_opcao_pelo_simples.value() : Json::Value(Json::nullValue);
    jsonCNPJ["data_exclusao_do_simples"] =
        data_exclusao_do_simples.has_value() ? data_exclusao_do_simples.value() : Json::Value(Json::nullValue);
    jsonCNPJ["opcao_pelo_mei"] = opcao_pelo_mei;
    jsonCNPJ["situacao_especial"] = situacao_especial.has_value() ? situacao_especial.value() : Json::Value(Json::nullValue);
    jsonCNPJ["data_situacao_especial"] =
        data_situacao_especial.has_value() ? data_situacao_especial.value() : Json::Value(Json::nullValue);

    Json::Value jsonCNAEs(Json::arrayValue);
    for (const auto &cnae : cnaes_secundarios) {
      Json::Value jsonCNAE;
      jsonCNAE["codigo"] = cnae.codigo;
      jsonCNAE["descricao"] = cnae.descricao;
      jsonCNAEs.append(jsonCNAE);
    }
    jsonCNPJ["cnaes_secundarios"] = jsonCNAEs;

    Json::Value jsonQSA(Json::arrayValue);
    for (const auto &qsaItem : qsa) {
      Json::Value jsonQSAItem;
      jsonQSAItem["identificador_de_socio"] = qsaItem.identificador_de_socio;
      jsonQSAItem["nome_socio"] = qsaItem.nome_socio;
      jsonQSAItem["cnpj_cpf_do_socio"] = qsaItem.cnpj_cpf_do_socio;
      jsonQSAItem["codigo_qualificacao_socio"] = qsaItem.codigo_qualificacao_socio;
      jsonQSAItem["percentual_capital_social"] = qsaItem.percentual_capital_social;
      jsonQSAItem["data_entrada_sociedade"] = qsaItem.data_entrada_sociedade;
      if (qsaItem.cpf_representante_legal)
        jsonQSAItem["cpf_representante_legal"] = *qsaItem.cpf_representante_legal;
      if (qsaItem.nome_representante_legal)
        jsonQSAItem["nome_representante_legal"] = *qsaItem.nome_representante_legal;
      if (qsaItem.codigo_qualificacao_representante_legal)
        jsonQSAItem["codigo_qualificacao_representante_legal"] = *qsaItem.codigo_qualificacao_representante_legal;
      jsonQSA.append(jsonQSAItem);
    }
    jsonCNPJ["qsa"] = jsonQSA;

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, jsonCNPJ);
  }
};
#endif // CNPJ_RESPONSE_H
