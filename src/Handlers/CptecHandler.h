#include "BrasilAPIHandlerBase.h"
#include "Response/CidadePrevisaoMetereologica.h"
#include "Response/CondicoesAeroporto.h"
#include "Response/CptecCapitaisResponse.h"
#include "Response/CptecCidadesResponse.h"
#include "Response/ErrorResponse.h"
#include "Response/PrevisaoOceanica.h"
#include <variant>

class CptecHandler : public BrasilAPIHandlerBase {
  public:
  void listAllCities(std::function<void(std::variant<CptecCidadesResponse, ErrorResponse>)> callback);
  void searchByTerms(std::string cityName, std::function<void(std::variant<CptecCidadesResponse, ErrorResponse>)> callback);
  void listCondicoesMetereologicasCapitais(std::function<void(std::variant<CptecCapitaisResponse, ErrorResponse>)> callback);
  void getCondicoesMetereologicasAeroporto(
      std::string icao, std::function<void(std::variant<CptecAeroporto, ErrorResponse>)> callback);
  void getClimaEmCidade(int cityCode, std::function<void(std::variant<CidadeClimaResponse, ErrorResponse>)> callback);
  void getPrevisaoCidadeSeisDias(
      int cityCode, int days, std::function<void(std::variant<CidadeClimaResponse, ErrorResponse>)> callback);
  void getPrevisaoOceanicaCidade(int cityCode, std::function<void(std::variant<CptecPrevisaoOceanica, ErrorResponse>)> callback);
  void getPrevisaoOceanicaCidadeSeisDias(
      int cityCode, int days, std::function<void(std::variant<CptecPrevisaoOceanica, ErrorResponse>)> callback);
};