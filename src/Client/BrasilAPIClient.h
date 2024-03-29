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
#include "Handlers/ISBNHandler.h"
#include "Handlers/NCMHandler.h"

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
#include "Response/ISBNResponse.h"
#include "Response/NCMResponse.h"
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
  ISBNHandler isbnHandler;
  NCMHandler ncmHandler;

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
  void getPrevisaoCidadeSeisDias(
      int cityCode, int days, std::function<void(std::variant<CidadeClimaResponse, ErrorResponse>)> callback);
  void getPrevisaoOceanicaCidade(int cityCode, std::function<void(std::variant<CptecPrevisaoOceanica, ErrorResponse>)> callback);
  void getPrevisaoOceanicaCidadeSeisDias(
      int cityCode, int days, std::function<void(std::variant<CptecPrevisaoOceanica, ErrorResponse>)> callback);
  void listStateAndCities(int ddd, std::function<void(std::variant<DDDResponse, ErrorResponse>)> callback);
  void listHolidaysAtYear(int ano, std::function<void(std::variant<FeriadosResponse, ErrorResponse>)> callback);
  void listarFipeMarcas(const std::optional<std::string> &tipoVeiculo, const std::optional<int> &tabela_referencia,
      std::function<void(std::variant<FipeMarcas, ErrorResponse>)> callback);
  void listarFipePreco(const std::string &codigoFipe, const std::optional<int> &tabela_referencia,
      std::function<void(std::variant<FipePrecos, ErrorResponse>)> callback);
  void listarFipeTabelas(std::function<void(std::variant<FipeTabelasReferencia, ErrorResponse>)> callback);
  void listarMunicipios(const std::string &siglaUf, const std::optional<std::string> &providers,
      std::function<void(std::variant<IBGEMunicipiosResponse, ErrorResponse>)> callback);
  void listarRegioes(std::function<void(std::variant<IBGERegioesResponse, ErrorResponse>)> callback);
  void getEstado(const std::string &uf, std::function<void(std::variant<Estado, ErrorResponse>)> callback);
  void getLivrosBrasil(const std::string &isbn, std::initializer_list<std::string> providers,
      std::function<void(std::variant<BookInfo, ErrorResponse>)> callback);
  void listarTodosNCM(std::function<void(std::variant<NCMResponse, ErrorResponse>)> callback);

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
  std::future<std::string> getPrevisaoCidadeSeisDiasAsync(int cityCode, int days);
  std::future<std::string> getPrevisaoOceanicaCidadeAsync(int cityCode);
  std::future<std::string> getPrevisaoOceanicaCidadeSeisDiasAsync(int cityCode, int days);
  std::future<std::string> listStateAndCitiesAsync(int ddd);
  std::future<std::string> listHolidaysAtYearAsync(int ano);
  std::future<std::string> listarFipeMarcasAsync();
  std::future<std::string> listarFipeMarcasAsync(std::optional<std::string> tipoVeiculo);
  std::future<std::string> listarFipeMarcasAsync(std::optional<int> tabela_referencia);
  std::future<std::string> listarFipeMarcasAsync(std::optional<std::string> tipoVeiculo, std::optional<int> tabela_referencia);
  std::future<std::string> listarFipePrecoAsync(std::string codigoFipe);
  std::future<std::string> listarFipePrecoAsync(std::string codigoFipe, std::optional<int> tabela_referencia);
  std::future<std::string> listarFipeTabelasAsync();
  std::future<std::string> listarMunicipiosAsync(std::string siglaUf);
  std::future<std::string> listarMunicipiosAsync(std::string siglaUf, std::optional<std::string> providers);
  std::future<std::string> listarRegioesAsync();
  std::future<std::string> getEstadoAsync(std::string uf);
  std::future<std::string> getLivrosBrasilAsync(std::string isbn);
  std::future<std::string> getLivrosBrasilAsync(std::string isbn, std::initializer_list<std::string> providers);
  std::future<std::string> listarTodosNCMAsync();

  // ...
};