#include "CNPJHandler.h"
#include <Utils/BrasilAPIException.h>

void CNPJHandler::getCNPJ(std::string cnpj, std::function<void(const CNPJResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/cnpj/v1/" + cnpj);
  std::string fullUrl = baseUrl + req->getPath();

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    try {
      ensureSuccess(response, "/api/cnpj/v1/{cnpj}");
      std::string responseBody = std::string(response->getBody());

      Json::Value jsonResponse;
      Json::Reader reader;
      CNPJResponse cnpjResponse;
      if (reader.parse(responseBody, jsonResponse)) {
        cnpjResponse.setCnpj(jsonResponse["cnpj"].asString());
        cnpjResponse.setIdentificadorMatrizFilial(stoi(jsonResponse["identificador_matriz_filial"].asString()));
        cnpjResponse.setDescricaoMatrizFilial(jsonResponse["descricao_matriz_filial"].asString());
        cnpjResponse.setRazaoSocial(jsonResponse["razao_social"].asString());
        cnpjResponse.setNomeFantasia(jsonResponse["nome_fantasia"].asString());
        cnpjResponse.setSituacaoCadastral(stoi(jsonResponse["situacao_cadastral"].asString()));
        cnpjResponse.setDescricaoSituacaoCadastral(jsonResponse["descricao_situacao_cadastral"].asString());
        cnpjResponse.setDataSituacaoCadastral(jsonResponse["data_situacao_cadastral"].asString());
        cnpjResponse.setMotivoSituacaoCadastral(stoi(jsonResponse["motivo_situacao_cadastral"].asString()));
        cnpjResponse.setNomeCidadeExterior(jsonResponse["nome_cidade_exterior"].asString());
        cnpjResponse.setCodigoNaturezaJuridica(stoi(jsonResponse["codigo_natureza_juridica"].asString()));
        cnpjResponse.setDataInicioAtividade(jsonResponse["data_inicio_atividade"].asString());
        cnpjResponse.setCnaeFiscal(stoi(jsonResponse["cnae_fiscal"].asString()));
        cnpjResponse.setCnaeFiscalDescricao(jsonResponse["cnae_fiscal_descricao"].asString());
        cnpjResponse.setDescricaoTipoLogradouro(jsonResponse["descricao_tipo_logradouro"].asString());
        cnpjResponse.setLogradouro(jsonResponse["logradouro"].asString());
        cnpjResponse.setNumero(jsonResponse["numero"].asString());
        cnpjResponse.setComplemento(jsonResponse["complemento"].asString());
        cnpjResponse.setBairro(jsonResponse["bairro"].asString());
        cnpjResponse.setCep(stoi(jsonResponse["cep"].asString()));
        cnpjResponse.setUf(jsonResponse["uf"].asString());
        cnpjResponse.setCodigoMunicipio(stoi(jsonResponse["codigo_municipio"].asString()));
        cnpjResponse.setMunicipio(jsonResponse["municipio"].asString());
        cnpjResponse.setDddTelefone1(jsonResponse["ddd_telefone_1"].asString());
        cnpjResponse.setDddTelefone2(jsonResponse["ddd_telefone_2"].asString());
        cnpjResponse.setDddFax(jsonResponse["ddd_fax"].asString());
        cnpjResponse.setQualificacaoDoResponsavel(stoi(jsonResponse["qualificacao_do_responsavel"].asString()));
        cnpjResponse.setCapitalSocial(jsonResponse["capital_social"].asDouble());
        cnpjResponse.setCodigoPorte(stoi(jsonResponse["codigo_porte"].asString()));
        cnpjResponse.setPorte(jsonResponse["porte"].asString());
        cnpjResponse.setDescricaoPorte(jsonResponse["descricao_porte"].asString());
        cnpjResponse.setOpcaoPeloSimples(jsonResponse["opcao_pelo_simples"].asBool());
        cnpjResponse.setDataOpcaoPeloSimples(jsonResponse["data_opcao_pelo_simples"].asString());
        cnpjResponse.setDataExclusaoDoSimples(jsonResponse["data_exclusao_do_simples"].asString());
        cnpjResponse.setOpcaoPeloMei(jsonResponse["opcao_pelo_mei"].asBool());
        cnpjResponse.setSituacaoEspecial(jsonResponse["situacao_especial"].asString());
        cnpjResponse.setDataSituacaoEspecial(jsonResponse["data_situacao_especial"].asString());

        if (jsonResponse.isMember("cnaes_secundarios") && jsonResponse["cnaes_secundarios"].isArray()) {
          for (const auto &cnae : jsonResponse["cnaes_secundarios"]) {
            CNAE cnaeItem;
            cnaeItem.codigo = stoi(cnae["codigo"].asString());
            cnaeItem.descricao = cnae["descricao"].asString();
            cnpjResponse.addCnaeSecundario(cnaeItem);
          }
        }

        if (jsonResponse.isMember("qsa") && jsonResponse["qsa"].isArray()) {
          for (const auto &qsaItem : jsonResponse["qsa"]) {
            QSA qsaMember;
            qsaMember.identificador_de_socio = stoi(qsaItem["identificador_de_socio"].asString());
            qsaMember.nome_socio = qsaItem["nome_socio"].asString();
            qsaMember.cnpj_cpf_do_socio = qsaItem["cnpj_cpf_do_socio"].asString();
            qsaMember.codigo_qualificacao_socio = stoi(qsaItem["codigo_qualificacao_socio"].asString());
            if (qsaItem.isMember("percentual_capital_social"))
              qsaMember.percentual_capital_social = stoi(qsaItem["percentual_capital_social"].asString());
            qsaMember.data_entrada_sociedade = qsaItem["data_entrada_sociedade"].asString();
            if (qsaItem.isMember("cpf_representante_legal"))
              qsaMember.cpf_representante_legal = qsaItem["cpf_representante_legal"].asString();
            if (qsaItem.isMember("nome_representante_legal"))
              qsaMember.nome_representante_legal = qsaItem["nome_representante_legal"].asString();
            if (qsaItem.isMember("codigo_qualificacao_representante_legal"))
              qsaMember.codigo_qualificacao_representante_legal =
                  stoi(qsaItem["codigo_qualificacao_representante_legal"].asString());
            cnpjResponse.addQsaItem(qsaMember);
          }
        }

        cnpjResponse.calledURL = fullUrl;
      } else {
        std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
        return;
      }
      callback(cnpjResponse);

    } catch (const BrasilAPIException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return;
    }
  });
}