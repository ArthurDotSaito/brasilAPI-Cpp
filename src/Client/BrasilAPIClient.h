// Handler
#include "Handlers/BanksHandler.h"
#include "Handlers/CNPJHandler.h"
#include "Handlers/CepHandler.h"
#include "Handlers/CorretorasHandler.h"
#include "Handlers/CptecHandler.h"
#include "Handlers/DDDHandler.h"
#include "Handlers/FeriadosHandler.h"
#include "Handlers/FipeHandler.h"
#include "Handlers/IBGEHandler.h"

// Response
#include "Response/BankResponse.h"
#include "Response/CNPJResponse.h"
#include "Response/CepResponse.h"
#include "Response/CorretorasResponse.h"
#include "Response/CptecCapitaisResponse.h"
#include "Response/CptecCidadesResponse.h"
#include "Response/DDD.h"
#include "Response/FipeResponse.h"
#include "Response/IBGEResponse.h"
#include "Response/PrevisaoOceanica.h"

#include <drogon/drogon.h>

class BrasilAPIClient {
  private:
  BanksHandler banksHandler;
  CepHandler cepHandler;
  CNPJHandler cnpjHandler;
  CorretorasHandler corretorasHandler;
  CptecHandler cptecHandler;
  DDDHandler dddHandler;
  FeriadosHandler feriadosHandler;
  FipeHandler fipeHandler;
  IBGEHandler ibgeHandler;

  std::string userAgent;
  std::thread eventLoopThread;
  std::mutex mutex;

  void startEventLoop() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!eventLoopThread.joinable()) {
      eventLoopThread = std::thread([]() { drogon::app().run(); });
    }
  }

  public:
  BrasilAPIClient();
  ~BrasilAPIClient();

  void setUserAgent(const std::string &userAgent);

  // TODO: Revisar nome das funções (list vs get, etc)
  // Funções que usam callbacks
  void getAllBanks(std::function<void(std::variant<BankResponse, ErrorResponse>)> callback);
  void getBanksByCode(int code, std::function<void(std::variant<Bank, ErrorResponse>)> callback);
  void getCep(int cep, std::function<void(std::variant<CepResponse, ErrorResponse>)> callback);
  void getCepV2(int cep, std::function<void(std::variant<CepResponse, ErrorResponse>)> callback);
  void getCNPJ(std::string cnpj, std::function<void(std::variant<CNPJResponse, ErrorResponse>)> callback);
  void getAllCorretoras(std::function<void(std::variant<CorretorasResponse, ErrorResponse>)> callback);
  void getCorretorasByCnpj(std::string cnpj, std::function<void(std::variant<Corretoras, ErrorResponse>)> callback);
  void listAllCities(std::function<void(std::variant<CptecCidadesResponse, ErrorResponse>)> callback);
  void searchByTerms(std::string cityName, std::function<void(std::variant<CptecCidadesResponse, ErrorResponse>)> callback);
  void listCondicoesMetereologicasCapitais(std::function<void(std::variant<CptecCapitaisResponse, ErrorResponse>)> callback);
  void getCondicoesMetereologicasAeroporto(
      std::string icao, std::function<void(std::variant<CptecAeroporto, ErrorResponse>)> callback);
  void getClimaEmCidade(int cityCode, std::function<void(std::variant<CidadeClimaResponse, ErrorResponse>)> callback);
  void previsaoCidadeSeisDias(int cityCode, int days, std::function<void(const CidadeClimaResponse &)> callback);
  void previsaoOceanicaCidade(int cityCode, std::function<void(const CptecPrevisaoOceanica &)> callback);
  void previsaoOceanicaCidadeSeisDias(int cityCode, int days, std::function<void(const CptecPrevisaoOceanica &)> callback);
  void listStateAndCities(int ddd, std::function<void(const DDDResponse &)> callback);
  void getFeriados(int ano, std::function<void(const FeriadosResponse &)> callback);
  void listFipeMarcas(const std::optional<std::string> &tipoVeiculo, const std::optional<int> &tabela_referencia,
      std::function<void(const FipeMarcas &)> callback);
  void listFipePreco(const std::string &codigoFipe, const std::optional<int> &tabela_referencia,
      std::function<void(const FipePrecos &)> callback);
  void listFipeTabelas(std::function<void(const FipeTabelasReferencia &)> callback);
  void listMunicipios(const std::string &siglaUf, const std::optional<std::string> &providers,
      std::function<void(const IBGEMunicipiosResponse &)> callback);
  void listRegioes(std::function<void(const IBGERegioesResponse &)> callback);
  void getEstado(const std::string &uf, std::function<void(const Estado &)> callback);

  // Funções que retornam std::future<std::string>
  std::future<std::string> getAllBanksAsync();
  std::future<std::string> getBanksByCodeAsync(int code);
  std::future<std::string> getCepAsync(int cep);
  std::future<std::string> getCepV2Async(int cep);
  std::future<std::string> getCNPJAsync(std::string cnpj);
  std::future<std::string> getAllCorretorasAsync();
  std::future<std::string> getCorretorasByCnpjAsync(std::string cnpj);
  std::future<std::string> listAllCitiesAsync();
  std::future<std::string> searchByTermsAsync(std::string cityName);
  std::future<std::string> listCondicoesMetereologicasCapitaisAsync();
  std::future<std::string> getCondicoesMetereologicasAeroportoAsync(std::string icao);
  std::future<std::string> getCLimaEmCidadeAsync(int cityCode);
  std::future<std::string> previsaoCidadeSeisDiasAsync(int cityCode, int days);
  std::future<std::string> previsaoOceanicaCidadeAsync(int cityCode);
  std::future<std::string> previsaoOceanicaCidadeSeisDiasAsync(int cityCode, int days);
  std::future<std::string> listStateAndCitiesAsync(int ddd);
  std::future<std::string> getFeriadosAsync(int ano);
  std::future<std::string> listFipeMarcasAsync();
  std::future<std::string> listFipeMarcasAsync(std::optional<std::string> tipoVeiculo);
  std::future<std::string> listFipeMarcasAsync(std::optional<int> tabela_referencia);
  std::future<std::string> listFipeMarcasAsync(std::optional<std::string> tipoVeiculo, std::optional<int> tabela_referencia);
  std::future<std::string> listFipePrecoAsync(std::string codigoFipe);
  std::future<std::string> listFipePrecoAsync(std::string codigoFipe, std::optional<int> tabela_referencia);
  std::future<std::string> listFipeTabelasAsync();
  std::future<std::string> listMunicipiosAsync(std::string siglaUf);
  std::future<std::string> listMunicipiosAsync(std::string siglaUf, std::optional<std::string> providers);
  std::future<std::string> listRegioesAsync();
  std::future<std::string> getEstadoAsync(std::string uf);

  // ...
};