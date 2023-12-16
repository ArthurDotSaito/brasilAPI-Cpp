#ifndef CPTECCAPITAIS_RESPONSE_H
#define CPTECCAPITAIS_RESPONSE_H

#include "BaseResponse.h"
#include <json/json.h>
#include <string>

class CptecCapitais : public BaseResponse {
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

  std::string serialize() const {
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
    builder["indentation"] = "  ";
    return Json::writeString(builder, jsonCptecCapitais);
  }
};

class CptecCapitaisResponse : public BaseResponse {
  public:
  std::vector<CptecCapitais> cptecCapitais;

  std::string serialize() const {
    Json::Value jsonRoot;
    for (const auto &cptecCapitais : cptecCapitais) {
      Json::Value jsonCptecCapitais;
      jsonCptecCapitais["codigo_icao"] = cptecCapitais.codigo_icao;
      jsonCptecCapitais["atualizado_em"] = cptecCapitais.atualizado_em;
      jsonCptecCapitais["pressao_atmosferica"] = cptecCapitais.pressao_atmosferica;
      jsonCptecCapitais["visibilidade"] = cptecCapitais.visibilidade;
      jsonCptecCapitais["vento"] = cptecCapitais.vento;
      jsonCptecCapitais["direcao_vento"] = cptecCapitais.direcao_vento;
      jsonCptecCapitais["umidade"] = cptecCapitais.umidade;
      jsonCptecCapitais["condicao"] = cptecCapitais.condicao;
      jsonCptecCapitais["condicao_Desc"] = cptecCapitais.condicao_Desc;
      jsonCptecCapitais["temp"] = cptecCapitais.temp;

      jsonRoot.append(jsonCptecCapitais);
    }

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, jsonRoot);
  }
};

#endif // CPTECCAPITAIS_RESPONSE_H