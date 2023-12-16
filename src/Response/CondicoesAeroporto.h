#ifndef CONDICOESAEROPORTO_RESPONSE_H
#define CONDICOESAEROPORTO_RESPONSE_H

#include <string>
#include <json/json.h>
#include "BaseResponse.h"

class CptecAeroporto : public BaseResponse
{
public:
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

    std::string serialize() const
    {
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

        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "";
        return Json::writeString(builder, jsonCptecCapitais);
    }
};

#endif // CONDICOESAEROPORTO_RESPONSE_H