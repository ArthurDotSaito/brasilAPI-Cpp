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
  void getCidadesClimaByCidade(int cityCode, std::function<void(const CidadeClimaResponse &)> callback);
  void previsaoCidadeSeisDias(int cityCode, int days, std::function<void(const CidadeClimaResponse &)> callback);
  void previsaoOceanicaCidade(int cityCode, std::function<void(const CptecPrevisaoOceanica &)> callback);
  void previsaoOceanicaCidadeSeisDias(int cityCode, int days, std::function<void(const CptecPrevisaoOceanica &)> callback);
};