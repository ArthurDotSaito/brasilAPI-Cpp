#include "CNPJHandler.h"

void CNPJHandler::getCNPJ(std::string cnpj, std::function<void(const CNPJResponse&)> callback) {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/cnpj/v1/" + cnpj);
    std::string fullUrl = baseUrl + req->getPath();

    httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "/api/cnpj/v1/{cnpj}");
        std::string responseBody = std::string(response->getBody());

        Json::Value jsonResponse;
        Json::Reader reader;
        CNPJResponse cnpjResponse;
        if (reader.parse(responseBody, jsonResponse)) {
            cnpjResponse.cnpj = jsonResponse["cnpj"].asString();
            cnpjResponse.identificador_matriz_filial = stoi(jsonResponse["identificador_matriz_filial"].asString());
            cnpjResponse.descricao_matriz_filial = jsonResponse["descricao_matriz_filial"].asString();
            cnpjResponse.razao_social = jsonResponse["razao_social"].asString();
            cnpjResponse.nome_fantasia = jsonResponse["nome_fantasia"].asString();
            cnpjResponse.situacao_cadastral = stoi(jsonResponse["situacao_cadastral"].asString());
            cnpjResponse.descricao_situacao_cadastral = jsonResponse["descricao_situacao_cadastral"].asString();
            cnpjResponse.data_situacao_cadastral = jsonResponse["data_situacao_cadastral"].asString();
            cnpjResponse.motivo_situacao_cadastral = stoi(jsonResponse["motivo_situacao_cadastral"].asString());
            cnpjResponse.nome_cidade_exterior = jsonResponse["nome_cidade_exterior"].asString();
            cnpjResponse.codigo_natureza_juridica = stoi(jsonResponse["codigo_natureza_juridica"].asString());
            cnpjResponse.data_inicio_atividade = jsonResponse["data_inicio_atividade"].asString();
            cnpjResponse.cnae_fiscal = stoi(jsonResponse["cnae_fiscal"].asString());
            cnpjResponse.cnae_fiscal_descricao = jsonResponse["cnae_fiscal_descricao"].asString();
            cnpjResponse.descricao_tipo_logradouro = jsonResponse["descricao_tipo_logradouro"].asString();
            cnpjResponse.logradouro = jsonResponse["logradouro"].asString();
            cnpjResponse.numero = jsonResponse["numero"].asString();
            cnpjResponse.complemento = jsonResponse["complemento"].asString();
            cnpjResponse.bairro = jsonResponse["bairro"].asString();
            cnpjResponse.cep = stoi(jsonResponse["cep"].asString());
            cnpjResponse.uf = jsonResponse["uf"].asString();
            cnpjResponse.codigo_municipio = stoi(jsonResponse["codigo_municipio"].asString());
            cnpjResponse.municipio = jsonResponse["municipio"].asString();
            cnpjResponse.ddd_telefone_1 = jsonResponse["ddd_telefone_1"].asString();
            cnpjResponse.ddd_telefone_2 = jsonResponse["ddd_telefone_2"].asString();
            cnpjResponse.ddd_fax = jsonResponse["ddd_fax"].asString();
            cnpjResponse.qualificacao_do_responsavel = stoi(jsonResponse["qualificacao_do_responsavel"].asString());
            cnpjResponse.capital_social = jsonResponse["capital_social"].asDouble();
            cnpjResponse.codigo_porte = stoi(jsonResponse["codigo_porte"].asString());
            cnpjResponse.porte = jsonResponse["porte"].asString();
            cnpjResponse.descricao_porte = jsonResponse["descricao_porte"].asString();
            cnpjResponse.opcao_pelo_simples = jsonResponse["opcao_pelo_simples"].asBool();
            cnpjResponse.data_opcao_pelo_simples = jsonResponse["data_opcao_pelo_simples"].asString();
            cnpjResponse.data_exclusao_do_simples = jsonResponse["data_exclusao_do_simples"].asString();
            cnpjResponse.opcao_pelo_mei = jsonResponse["opcao_pelo_mei"].asBool();
            cnpjResponse.situacao_especial = jsonResponse["situacao_especial"].asString();
            cnpjResponse.data_situacao_especial = jsonResponse["data_situacao_especial"].asString();

            if (jsonResponse.isMember("cnaes_secundarios") && jsonResponse["cnaes_secundarios"].isArray()) {
                for (const auto& cnae : jsonResponse["cnaes_secundarios"]) {
                    CNAE cnaeItem;
                    cnaeItem.codigo = stoi(cnae["codigo"].asString());
                    cnaeItem.descricao = cnae["descricao"].asString();
                    cnpjResponse.cnaes_secundarios.push_back(cnaeItem);
                }
            }

            if (jsonResponse.isMember("qsa") && jsonResponse["qsa"].isArray()) {
                for (const auto& qsaItem : jsonResponse["qsa"]) {
                    QSA qsaMember;
                    qsaMember.identificador_de_socio = stoi(qsaItem["identificador_de_socio"].asString());
                    qsaMember.nome_socio = qsaItem["nome_socio"].asString();
                    qsaMember.cnpj_cpf_do_socio = qsaItem["cnpj_cpf_do_socio"].asString();
                    qsaMember.codigo_qualificacao_socio = stoi(qsaItem["codigo_qualificacao_socio"].asString());
                    if(qsaItem.isMember("percentual_capital_social")) qsaMember.percentual_capital_social = stoi(qsaItem["percentual_capital_social"].asString());
                    qsaMember.data_entrada_sociedade = qsaItem["data_entrada_sociedade"].asString();
                    if (qsaItem.isMember("cpf_representante_legal")) qsaMember.cpf_representante_legal = qsaItem["cpf_representante_legal"].asString();
                    if (qsaItem.isMember("nome_representante_legal")) qsaMember.nome_representante_legal = qsaItem["nome_representante_legal"].asString();
                    if (qsaItem.isMember("codigo_qualificacao_representante_legal")) qsaMember.codigo_qualificacao_representante_legal = stoi(qsaItem["codigo_qualificacao_representante_legal"].asString());
                    cnpjResponse.qsa.push_back(qsaMember);
                }
            }

            cnpjResponse.calledURL = fullUrl;
        } else {
            std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
            return;
        }

        callback(cnpjResponse);
    });
}