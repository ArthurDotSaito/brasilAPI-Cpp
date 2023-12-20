#include "BrasilAPIClient.h"
#include <drogon/drogon.h>

BrasilAPIClient::BrasilAPIClient() : banksHandler() {
  startEventLoop();
}

BrasilAPIClient::~BrasilAPIClient() {
  if (eventLoopThread.joinable()) {
    drogon::app().quit();
    eventLoopThread.join();
  }
}

void BrasilAPIClient::setUserAgent(const std::string &ua) {
  userAgent = ua;
}

void BrasilAPIClient::getAllBanks(std::function<void(const BankResponse &)> callback) {
  banksHandler.getAllBanks(callback);
}

void BrasilAPIClient::getBanksByCode(int code, std::function<void(const Bank &)> callback) {
  banksHandler.getBanksByCode(code, callback);
}

void BrasilAPIClient::getCep(int cep, std::function<void(const CepResponse &)> callback) {
  cepHandler.getCep(cep, callback);
}

void BrasilAPIClient::getCepV2(int cep, std::function<void(const CepResponse &)> callback) {
  cepHandler.getCepV2(cep, callback);
}

void BrasilAPIClient::getCNPJ(std::string cnpj, std::function<void(const CNPJResponse &)> callback) {
  cnpjHandler.getCNPJ(cnpj, callback);
}

void BrasilAPIClient::getAllCorretoras(std::function<void(const CorretorasResponse &)> callback) {
  corretorasHandler.getAllCorretoras(callback);
}

void BrasilAPIClient::getCorretorasByCnpj(std::string cnpj, std::function<void(const Corretoras &)> callback) {
  corretorasHandler.getCorretorasByCnpj(cnpj, callback);
}

void BrasilAPIClient::listAllCities(std::function<void(const CptecCidadesResponse &)> callback) {
  cptecHandler.listAllCities(callback);
}

void BrasilAPIClient::searchByTerms(std::string cityName, std::function<void(const CptecCidadesResponse &)> callback) {
  cptecHandler.searchByTerms(cityName, callback);
}

void BrasilAPIClient::getCapitais(std::function<void(const CptecCapitaisResponse &)> callback) {
  cptecHandler.getCapitais(callback);
}

void BrasilAPIClient::getCondicoesAeroporto(std::string icao, std::function<void(const CptecAeroporto &)> callback) {
  cptecHandler.getCondicoesAeroporto(icao, callback);
}

void BrasilAPIClient::getCidadesClimaByCidade(int cityCode, std::function<void(const CidadeClimaResponse &)> callback) {
  cptecHandler.getCidadesClimaByCidade(cityCode, callback);
}

void BrasilAPIClient::previsaoCidadeSeisDias(int cityCode, int days, std::function<void(const CidadeClimaResponse &)> callback) {
  cptecHandler.previsaoCidadeSeisDias(cityCode, days, callback);
}

/**
 * @brief Retorna informações de todos os bancos do Brasil.
 * Retorna um array de objetos com informações de todos os bancos do Brasil.
 */
std::future<std::string> BrasilAPIClient::getAllBanksAsync() {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  banksHandler.getAllBanks([this, promisePtr](const BankResponse &response) { promisePtr->set_value(response.serialize()); });
  return future;
}

/**
 * @brief Busca as informações de um banco a partir de um código.
 * Retorna um objeto com informações referentes ao banco pesquisado.
 * @param cnpj código do banco para efetuar a busca.
 */
std::future<std::string> BrasilAPIClient::getBanksByCodeAsync(int code) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  banksHandler.getBanksByCode(code, [this, promisePtr, code](const Bank &bank) { promisePtr->set_value(bank.serialize()); });
  return future;
}

/**
 * @brief Serviço de busca por CEP com múltiplos providers de fallback.
 * Retorna um objeto com informações referentes ao cep de busca.
 * @param cnpj código cep para efetuar a busca.
 */
std::future<std::string> BrasilAPIClient::getCepAsync(int cep) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cepHandler.getCep(
      cep, [this, promisePtr, cep](const CepResponse &cepRespose) { promisePtr->set_value(cepRespose.serialize()); });
  return future;
}

/**
 * @brief versão 2 do serviço de busca por CEP com múltiplos providers de fallback.
 * Retorna um objeto com informações referentes ao cep de busca.
 * @param cnpj código cep para efetuar a busca.
 */
std::future<std::string> BrasilAPIClient::getCepV2Async(int cep) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cepHandler.getCepV2(
      cep, [this, promisePtr, cep](const CepResponse &cepRespose) { promisePtr->set_value(cepRespose.serialize()); });
  return future;
}

/**
 * @brief Busca por CNPJ na API Minha Receita.
 * Retorna um objeto com informações referentes ao cnpj solicitado.
 * @param cnpj cnpj para efetuar a busca.
 */
std::future<std::string> BrasilAPIClient::getCNPJAsync(std::string cnpj) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cnpjHandler.getCNPJ(
      cnpj, [this, promisePtr, cnpj](const CNPJResponse &cnpjResponse) { promisePtr->set_value(cnpjResponse.serialize()); });
  return future;
}

/**
 * @brief retorna todas as corretoras nos arquivos da CVM.
 * Retorna um array des objetos com informações sobre a corretora solicitada.
 */
std::future<std::string> BrasilAPIClient::getAllCorretorasAsync() {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  corretorasHandler.getAllCorretoras([this, promisePtr](const CorretorasResponse &corretorasResponse) {
    promisePtr->set_value(corretorasResponse.serialize());
  });
  return future;
}

/**
 * @brief Busca por corretoras nos arquivos da CVM.
 * Retorna um objeto com informações sobre a corretora solicitada.
 * @param cnpj cnpj da corretora.
 */
std::future<std::string> BrasilAPIClient::getCorretorasByCnpjAsync(std::string cnpj) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  corretorasHandler.getCorretorasByCnpj(
      cnpj, [this, promisePtr, cnpj](const Corretoras &corretora) { promisePtr->set_value(corretora.serialize()); });
  return future;
}

/**
 * @brief Buscar localidades
 * Retorna listagem com todas as cidades junto a seus respectivos códigos presentes nos serviços da CPTEC. O Código destas cidades
 * será utilizado para os serviços de meteorologia e a ondas (previsão oceânica) fornecido pelo centro. Leve em consideração que o
 * WebService do CPTEC as vezes é instável, então se não encontrar uma determinada cidade na listagem completa, tente buscando por
 * parte de seu nome no endpoint de busca.
 */
std::future<std::string> BrasilAPIClient::listAllCitiesAsync() {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cptecHandler.listAllCities(
      [this, promisePtr](const CptecCidadesResponse &cidades) { promisePtr->set_value(cidades.serialize()); });
  return future;
}

/**
 * @brief Buscar localidades
 * Retorna listagem com todas as cidades correspondentes ao termo pesquisado junto a seus respectivos códigos presentes nos
 * serviços da CPTEC. O Código destas cidades será utilizado para os serviços de meteorologia e a ondas (previsão oceânica)
 * fornecido pelo centro.
 * @param cityName Nome ou parte do nome da cidade a ser buscada.
 */
std::future<std::string> BrasilAPIClient::searchByTermsAsync(std::string cityName) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cptecHandler.searchByTerms(cityName,
      [this, promisePtr, cityName](const CptecCidadesResponse &cidades) { promisePtr->set_value(cidades.serialize()); });
  return future;
}

/**
 * @brief Condições atuais nas capitais
 * Retorna condições meteorológicas atuais nas capitais do país, com base nas estações de solo de seu aeroporto.
 */
std::future<std::string> BrasilAPIClient::getCapitaisAsync() {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cptecHandler.getCapitais(
      [this, promisePtr](const CptecCapitaisResponse &capitais) { promisePtr->set_value(capitais.serialize()); });
  return future;
}

/**
 * @brief Condições atuais em um aeroporto
 * Retorna condições meteorológicas atuais no aeroporto solicitado.
 * Este endpoint utiliza o código ICAO (4 dígitos) do aeroporto.
 * @param icao Código ICAO (4 dígitos) do aeroporto desejado.
 */
std::future<std::string> BrasilAPIClient::getCondicoesAeroportoAsync(std::string icao) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cptecHandler.getCondicoesAeroporto(
      icao, [this, promisePtr, icao](const CptecAeroporto &aeroporto) { promisePtr->set_value(aeroporto.serialize()); });
  return future;
}

/**
 * @brief Previsão meteorológica de um dia de uma cidade
 * Retorna Pervisão meteorológica para 1 dia na cidade informada.
 *
 * @param cityCode Código da cidade fornecido. Veja CptecCidade.
 */
std::future<std::string> BrasilAPIClient::getCidadesClimaByCidadeAsync(int cityCode) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cptecHandler.getCidadesClimaByCidade(
      cityCode, [this, promisePtr, cityCode](const CidadeClimaResponse &cidade) { promisePtr->set_value(cidade.serialize()); });
  return future;
}

/**
 * @brief Previsão meteorológica para, até, 6 dias
 * Retorna a previsão meteorológica para a cidade informada para um período de 1 até 6 dias.
 * Devido a inconsistências encontradas nos retornos da CPTEC nossa API só consegue retornar com precisão o período máximo de 6
 * dias.
 *
 * @param cityCode Código da cidade fornecido. Veja CptecCidade.
 * @param days Quantidade de dias desejado para a previsão. Máximo de 6 dias.
 */
std::future<std::string> BrasilAPIClient::previsaoCidadeSeisDiasAsync(int cityCode, int days) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cptecHandler.previsaoCidadeSeisDias(cityCode, days,
      [this, promisePtr, cityCode](const CidadeClimaResponse &cidade) { promisePtr->set_value(cidade.serialize()); });
  return future;
}