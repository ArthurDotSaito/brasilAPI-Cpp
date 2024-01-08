#ifndef CPTECOCEANO_RESPONSE_H
#define CPTECOCEANO_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>
#include <vector>

class DadosOnda {
  private:
  float vento;
  std::string direcao_vento;
  std::string direcao_vento_desc;
  float altura_onda;
  std::string direcao_onda;
  std::string direcao_onda_desc;
  std::string agitation;
  std::string hora;

  public:
  float getVento() const {
    return vento;
  }
  const std::string &getDirecaoVento() const {
    return direcao_vento;
  }
  const std::string &getDirecaoVentoDesc() const {
    return direcao_vento_desc;
  }
  float getAlturaOnda() const {
    return altura_onda;
  }
  const std::string &getDirecaoOnda() const {
    return direcao_onda;
  }
  const std::string &getDirecaoOndaDesc() const {
    return direcao_onda_desc;
  }
  const std::string &getAgitation() const {
    return agitation;
  }
  const std::string &getHora() const {
    return hora;
  }

  void setVento(float v) {
    vento = v;
  }
  void setDirecaoVento(const std::string &dv) {
    direcao_vento = dv;
  }
  void setDirecaoVentoDesc(const std::string &dvd) {
    direcao_vento_desc = dvd;
  }
  void setAlturaOnda(float a) {
    altura_onda = a;
  }
  void setDirecaoOnda(const std::string &do_) {
    direcao_onda = do_;
  }
  void setDirecaoOndaDesc(const std::string &dod) {
    direcao_onda_desc = dod;
  }
  void setAgitation(const std::string &a) {
    agitation = a;
  }
  void setHora(const std::string &h) {
    hora = h;
  }

  Json::Value toJson() const {
    Json::Value jsonDadosOnda;
    jsonDadosOnda["vento"] = vento;
    jsonDadosOnda["direcao_vento"] = direcao_vento;
    jsonDadosOnda["direcao_vento_desc"] = direcao_vento_desc;
    jsonDadosOnda["altura_onda"] = altura_onda;
    jsonDadosOnda["direcao_onda"] = direcao_onda;
    jsonDadosOnda["direcao_onda_desc"] = direcao_onda_desc;
    jsonDadosOnda["agitation"] = agitation;
    jsonDadosOnda["hora"] = hora;
    return jsonDadosOnda;
  }
};

class Onda {
  private:
  std::string data;
  std::vector<DadosOnda> dados_ondas;

  public:
  const std::string &getData() const {
    return data;
  }
  const std::vector<DadosOnda> &getDadosOndas() const {
    return dados_ondas;
  }

  void setData(const std::string &d) {
    data = d;
  }
  void addClimaDiario(const DadosOnda &dadosOnda) {
    dados_ondas.push_back(dadosOnda);
  }

  Json::Value toJson() const {
    Json::Value jsonOnda;
    jsonOnda["data"] = data;
    Json::Value jsonDadosOndasArray(Json::arrayValue);
    for (const auto &dadosOnda : dados_ondas) {
      jsonDadosOndasArray.append(dadosOnda.toJson());
    }
    jsonOnda["dados_ondas"] = jsonDadosOndasArray;
    return jsonOnda;
  }
};

class CptecPrevisaoOceanica : public BaseResponse, public JsonSerialize {
  private:
  std::string cidade;
  std::string estado;
  std::string atualizado_em;
  std::vector<Onda> ondas;

  public:
  const std::string &getCidade() const {
    return cidade;
  }
  const std::string &getEstado() const {
    return estado;
  }
  const std::string &getAtualizadoEm() const {
    return atualizado_em;
  }
  const std::vector<Onda> &getOndas() const {
    return ondas;
  }

  void setCidade(const std::string &c) {
    cidade = c;
  }
  void setEstado(const std::string &e) {
    estado = e;
  }
  void setAtualizadoEm(const std::string &ae) {
    atualizado_em = ae;
  }
  void addOnda(const Onda &onda) {
    ondas.push_back(onda);
  }

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : ondas) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

class CptecPrevisaoOceanicaResponse : public BaseResponse, public JsonSerialize {
  public:
  std::vector<CptecPrevisaoOceanica> cptecPrevisaoOceanica;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : cptecPrevisaoOceanica) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

#endif // CPTECOCEANO_RESPONSE_H
