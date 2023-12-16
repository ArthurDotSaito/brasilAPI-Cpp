#include "Handlers/BanksHandler.h"
#include "Handlers/CNPJHandler.h"
#include "Handlers/CepHandler.h"
#include "Handlers/CorretorasHandler.h"
#include "Handlers/CptecHandler.h"
#include "Response/BankResponse.h"
#include "Response/CNPJResponse.h"
#include "Response/CepResponse.h"
#include "Response/CorretorasResponse.h"
#include "Response/CptecCapitaisResponse.h"
#include "Response/CptecCidadesResponse.h"
#include <drogon/drogon.h>

class BrasilAPIClient {
  private:
  BanksHandler banksHandler;
  CepHandler cepHandler;
  CNPJHandler cnpjHandler;
  CorretorasHandler corretorasHandler;
  CptecHandler cptecHandler;

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

  // Funções que usam callbacks
  void getAllBanks(std::function<void(const BankResponse &)> callback);
  void getBanksByCode(int code, std::function<void(const Bank &)> callback);
  void getCep(int cep, std::function<void(const CepResponse &)> callback);
  void getCepV2(int cep, std::function<void(const CepResponse &)> callback);
  void getCNPJ(std::string cnpj, std::function<void(const CNPJResponse &)> callback);
  void getAllCorretoras(std::function<void(const CorretorasResponse &)> callback);
  void getCorretorasByCnpj(std::string cnpj, std::function<void(const Corretoras &)> callback);
  void listAllCities(std::function<void(const CptecCidadesResponse &)> callback);
  void searchByTerms(std::string cityName, std::function<void(const CptecCidadesResponse &)> callback);
  void getCapitais(std::function<void(const CptecCapitaisResponse &)> callback);
  void getCondicoesAeroporto(std::string icao, std::function<void(const CptecAeroporto &)> callback);
  void getCidadesClimaByCidade(int cityCode, std::function<void(const CidadeClimaResponse &)> callback);

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
  std::future<std::string> getCapitaisAsync();
  std::future<std::string> getCondicoesAeroportoAsync(std::string icao);
  std::future<std::string> getCidadesClimaByCidadeAsync(int cityCode);
};