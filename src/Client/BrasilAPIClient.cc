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

void BrasilAPIClient::previsaoOceanicaCidade(int cityCode, std::function<void(const CptecPrevisaoOceanica &)> callback) {
  cptecHandler.previsaoOceanicaCidade(cityCode, callback);
}

void BrasilAPIClient::previsaoOceanicaCidadeSeisDias(
    int cityCode, int days, std::function<void(const CptecPrevisaoOceanica &)> callback) {
  cptecHandler.previsaoOceanicaCidadeSeisDias(cityCode, days, callback);
}

void BrasilAPIClient::listStateAndCities(int ddd, std::function<void(const DDDResponse &)> callback) {
  dddHandler.listStateAndCities(ddd, callback);
}

void BrasilAPIClient::getFeriados(int ano, std::function<void(const FeriadosResponse &)> callback) {
  feriadosHandler.getFeriados(ano, callback);
}

void BrasilAPIClient::listFipeMarcas(const std::optional<std::string> &tipoVeiculo, const std::optional<int> &tabela_referencia,
    std::function<void(const FipeMarcas &)> callback) {
  fipeHandler.listFipeMarcas(tipoVeiculo, tabela_referencia, callback);
}

void BrasilAPIClient::listFipePreco(const std::string &codigoFipe, const std::optional<int> &tabela_referencia,
    std::function<void(const FipePrecos &)> callback) {
  fipeHandler.listFipePreco(codigoFipe, tabela_referencia, callback);
}

void BrasilAPIClient::listFipeTabelas(std::function<void(const FipeTabelasReferencia &)> callback) {
  fipeHandler.listFipeTabelas(callback);
}

void BrasilAPIClient::listMunicipios(const std::string &siglaUf, const std::optional<std::string> &providers,
    std::function<void(const IBGEMunicipiosResponse &)> callback) {
  ibgeHandler.listMunicipios(siglaUf, providers, callback);
}

void BrasilAPIClient::listRegioes(std::function<void(const IBGERegioesResponse &)> callback) {
  ibgeHandler.listRegioes(callback);
}

void BrasilAPIClient::getEstado(const std::string &uf, std::function<void(const Estado &)> callback) {
  ibgeHandler.getEstado(uf, callback);
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

/**
 * @brief Previsão oceânica para uma cidade
 * Retorna a previsão oceânica para a cidade informada.
 *
 * @param cityCode Código da cidade fornecido. Veja CptecCidade.
 */
std::future<std::string> BrasilAPIClient::previsaoOceanicaCidadeAsync(int cityCode) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cptecHandler.previsaoOceanicaCidade(
      cityCode, [this, promisePtr, cityCode](const CptecPrevisaoOceanica &cidade) { promisePtr->set_value(cidade.serialize()); });
  return future;
}

/**
 * @brief Previsão oceânica para uma cidade, para até 6 dias
 * Retorna a previsão oceânica para a cidade informada para um período de 1 até 6 dias.
 * Devido a inconsistências encontradas nos retornos da CPTEC nossa API só consegue retornar com precisão o período máximo de 6
 * dias.
 *
 * @param cityCode Código da cidade fornecido. Veja CptecCidade.
 * @param days Quantidade de dias desejado para a previsão. Máximo de 6 dias.
 */
std::future<std::string> BrasilAPIClient::previsaoOceanicaCidadeSeisDiasAsync(int cityCode, int days) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  cptecHandler.previsaoOceanicaCidadeSeisDias(cityCode, days,
      [this, promisePtr, cityCode](const CptecPrevisaoOceanica &cidade) { promisePtr->set_value(cidade.serialize()); });
  return future;
}

/**
 * @brief Busca por DDD
 * Retorna um objeto com informações referentes ao DDD solicitado.
 * @param ddd ddd para efetuar a busca.
 */

std::future<std::string> BrasilAPIClient::listStateAndCitiesAsync(int ddd) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  dddHandler.listStateAndCities(
      ddd, [this, promisePtr, ddd](const DDDResponse &dddResponse) { promisePtr->set_value(dddResponse.serialize()); });
  return future;
}

/**
 * @brief Busca por feriados
 * Retorna um objeto com informações referentes ao ano solicitado.
 * @param ano ano para efetuar a busca.
 */
std::future<std::string> BrasilAPIClient::getFeriadosAsync(int ano) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  feriadosHandler.getFeriados(ano,
      [this, promisePtr, ano](const FeriadosResponse &feriadosResponse) { promisePtr->set_value(feriadosResponse.serialize()); });
  return future;
}

/**
 * @brief Lista as marcas de veículos referente ao tipo de veículo
 * Retorna um objeto com informações referentes ao tipo de veículo e/ou tabela de referência solicitado.
 * @param tipoVeiculo tipo de veículo para efetuar a busca - opcional. Quando o tipo não é específicado são buscada as marcas de
 * todos os tipos de veículos
 * @param tabela_referencia tabela de referência para efetuar a busca - opcional.
 * Por padrão é utilizado o código da tabela fipe
 * atual.
 */
std::future<std::string> BrasilAPIClient::listFipeMarcasAsync() {
  return listFipeMarcasAsync(std::nullopt, std::nullopt);
}

/**
 * @brief Lista as marcas de veículos referente ao tipo de veículo
 * Retorna um objeto com informações referentes ao tipo de veículo e/ou tabela de referência solicitado.
 * @param tipoVeiculo tipo de veículo para efetuar a busca - opcional. Quando o tipo não é específicado são buscada as marcas de
 * todos os tipos de veículos
 * @param tabela_referencia tabela de referência para efetuar a busca - opcional.
 * Por padrão é utilizado o código da tabela fipe
 * atual.
 */
std::future<std::string> BrasilAPIClient::listFipeMarcasAsync(std::optional<std::string> tipoVeiculo) {
  return listFipeMarcasAsync(tipoVeiculo, std::nullopt);
}

/**
 * @brief Lista as marcas de veículos referente ao tipo de veículo
 * Retorna um objeto com informações referentes ao tipo de veículo e/ou tabela de referência solicitado.
 * @param tipoVeiculo tipo de veículo para efetuar a busca - opcional. Quando o tipo não é específicado são buscada as marcas de
 * todos os tipos de veículos
 * @param tabela_referencia tabela de referência para efetuar a busca - opcional.
 * Por padrão é utilizado o código da tabela fipe
 * atual.
 */
std::future<std::string> BrasilAPIClient::listFipeMarcasAsync(std::optional<int> tabela_referencia) {
  return listFipeMarcasAsync(std::nullopt, tabela_referencia);
}

/**
 * @brief Lista as marcas de veículos referente ao tipo de veículo
 * Retorna um objeto com informações referentes ao tipo de veículo e/ou tabela de referência solicitado.
 * @param tipoVeiculo tipo de veículo para efetuar a busca - opcional. Quando o tipo não é específicado são buscada as marcas de
 * todos os tipos de veículos
 * @param tabela_referencia tabela de referência para efetuar a busca - opcional.
 * Por padrão é utilizado o código da tabela fipe
 * atual.
 */
std::future<std::string> BrasilAPIClient::listFipeMarcasAsync(
    std::optional<std::string> tipoVeiculo, std::optional<int> tabela_referencia) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  fipeHandler.listFipeMarcas(tipoVeiculo, tabela_referencia,
      [this, promisePtr](const FipeMarcas &fipeResponse) { promisePtr->set_value(fipeResponse.serialize()); });
  return future;
}

/**
 * @brief Consulta o preço do veículo segundo a tabela fipe.
 * Retorna um array de objetos com informações referentes ao veículo segundo a tabela fipe.
 * @param codigoFipe Código fipe do veículo/marca.
 * @param tabela_referencia tabela de referência para efetuar a busca - opcional.
 * Por padrão é utilizado o código da tabela fipe atual.
 */
std::future<std::string> BrasilAPIClient::listFipePrecoAsync(std::string codigoFipe) {
  return listFipePrecoAsync(codigoFipe, std::nullopt);
}

/**
 * @brief Consulta o preço do veículo segundo a tabela fipe.
 * Retorna um array de objetos com informações referentes ao veículo segundo a tabela fipe.
 * @param codigoFipe Código fipe do veículo/marca.
 * @param tabela_referencia tabela de referência para efetuar a busca - opcional.
 * Por padrão é utilizado o código da tabela fipe atual.
 */
std::future<std::string> BrasilAPIClient::listFipePrecoAsync(std::string codigoFipe, std::optional<int> tabela_referencia) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  fipeHandler.listFipePreco(codigoFipe, tabela_referencia,
      [this, promisePtr](const FipePrecos &fipeResponse) { promisePtr->set_value(fipeResponse.serialize()); });
  return future;
}

/**
 * @brief Lista as tabelas fipe de referência existentes.
 * Retorna um array de objetos com informações referentes as tabelas de referência da tabela fipe.
 */
std::future<std::string> BrasilAPIClient::listFipeTabelasAsync() {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  fipeHandler.listFipeTabelas(
      [this, promisePtr](const FipeTabelasReferencia &fipeResponse) { promisePtr->set_value(fipeResponse.serialize()); });
  return future;
}

/**
 * @brief Retorna os municípios da unidade federativa
 * Retorna um array de objetos com nome e codigo IBGE da unidade correspondente
 * @param siglaUf Sigla da unidade federativa, por exemplo SP, RJ, SC, etc.
 * @param providers Lista de provedores separados por vírgula. Este parâmetro é opcional.
 * Quando não fornecido, o sistema utilizará os provedores padrão.
 * Provedores Disponíveis: dados-abertos-br, gov, wikipedia
 */
std::future<std::string> BrasilAPIClient::listMunicipiosAsync(std::string siglaUf) {
  return listMunicipiosAsync(siglaUf, std::nullopt);
}

/**
 * @brief Retorna os municípios da unidade federativa
 * Retorna um array de objetos com nome e codigo IBGE da unidade correspondente
 * @param siglaUf Sigla da unidade federativa, por exemplo SP, RJ, SC, etc.
 * @param providers Lista de provedores separados por vírgula. Este parâmetro é opcional.
 * Quando não fornecido, o sistema utilizará os provedores padrão.
 * Provedores Disponíveis: dados-abertos-br, gov, wikipedia
 */
std::future<std::string> BrasilAPIClient::listMunicipiosAsync(std::string siglaUf, std::optional<std::string> providers) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  ibgeHandler.listMunicipios(siglaUf, providers,
      [this, promisePtr](const IBGEMunicipiosResponse &ibgeResponse) { promisePtr->set_value(ibgeResponse.serialize()); });
  return future;
}

/**
 * @brief Retorna informações de todos estados do Brasil
 * Retorna um array de objetos com nome, sigla e id de cada estado do Brasil.
 */
std::future<std::string> BrasilAPIClient::listRegioesAsync() {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  ibgeHandler.listRegioes(
      [this, promisePtr](const IBGERegioesResponse &ibgeResponse) { promisePtr->set_value(ibgeResponse.serialize()); });
  return future;
}

/**
 * @brief Busca as informações de um estado a partir da sigla ou código.
 * Retorna um objeto com nome, sigla e id do estado do Brasil, bem como informações acerca da região.
 * @param uf Sigla da unidade federativa, por exemplo SP, RJ, SC, etc.
 */
std::future<std::string> BrasilAPIClient::getEstadoAsync(std::string uf) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();
  ibgeHandler.getEstado(uf, [this, promisePtr](const Estado &estado) { promisePtr->set_value(estado.serialize()); });
  return future;
}