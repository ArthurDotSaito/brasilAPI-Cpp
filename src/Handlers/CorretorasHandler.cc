#include <Utils/BrasilAPIException.h>
#include <CorretorasHandler.h>

void CorretorasHandler::getAllCorretoras(std::function<void(const CorretorasResponse&)> callback){
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::HttpMethod::Get);
    req->setPath("/api/cvm/corretoras/v1");
    std::string fullUrl = baseUrl + req->getPath();
    std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;
    
    httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        ensureSuccess(response, "/api/cvm/corretoras/v1");
        std::string responseBody = std::string(response->getBody());

        CorretorasResponse corretorasResponse;
        corretorasResponse.calledURL = fullUrl;
        corretorasResponse.jsonResponse = responseBody;

        Json::Value jsonResponse;
        Json::Reader reader;
        if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
            for (const auto& jsonCorretoras : jsonResponse) {
                Corretoras corretora;
                corretora.bairro = jsonCorretoras["bairro"].asString(); 
                corretora.cep = jsonCorretoras["cep"].asString();
                corretora.cnpj = jsonCorretoras["cnpj"].asString();
                corretora.código_cvm = jsonCorretoras["código_cvm"].asString();
                corretora.complemento = jsonCorretoras["complemento"].asString();
                corretora.data_inicio_situacao = jsonCorretoras["data_inicio_situacao"].asString();
                corretora.data_patrimonio_liquido = jsonCorretoras["data_patrimonio_liquido"].asString();
                corretora.email = jsonCorretoras["email"].asString();
                corretora.logradouro = jsonCorretoras["logradouro"].asString();
                corretora.municipio = jsonCorretoras["municipio"].asString();
                corretora.nome_social = jsonCorretoras["nome_social"].asString();
                corretora.nome_comercial = jsonCorretoras["nome_comercial"].asString();
                corretora.pais = jsonCorretoras["pais"].asString();
                corretora.status = jsonCorretoras["status"].asString();
                corretora.telefone = jsonCorretoras["telefone"].asString();
                corretora.type = jsonCorretoras["type"].asString();
                corretora.uf = jsonCorretoras["uf"].asString();
                corretora.valor_patrimonio_liquido = jsonCorretoras["valor_patrimonio_liquido"].asString();

                corretorasResponse.corretoras.push_back(corretora);
            }
        }

        callback(corretorasResponse);
    });
}

void CorretorasHandler::getCorretorasByCnpj(int cnpj, std::function<void(const Corretoras&)> callback){
    //TODO
}