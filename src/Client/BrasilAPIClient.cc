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

void BrasilAPIClient::getAllBanks(std::function<void(std::variant<BankResponse, ErrorResponse>)> callback) {
  banksHandler.getAllBanks(callback);
}

void BrasilAPIClient::getBanksByCode(int code, std::function<void(std::variant<Bank, ErrorResponse>)> callback) {
  banksHandler.getBanksByCode(code, callback);
}

void BrasilAPIClient::getCep(int cep, std::function<void(std::variant<CepResponse, ErrorResponse>)> callback) {
  cepHandler.getCep(cep, callback);
}

void BrasilAPIClient::getCepV2(int cep, std::function<void(std::variant<CepResponse, ErrorResponse>)> callback) {
  cepHandler.getCepV2(cep, callback);
}

void BrasilAPIClient::getCNPJ(std::string cnpj, std::function<void(std::variant<CNPJResponse, ErrorResponse>)> callback) {
  cnpjHandler.getCNPJ(cnpj, callback);
}

void BrasilAPIClient::getAllCorretoras(std::function<void(std::variant<CorretorasResponse, ErrorResponse>)> callback) {
  corretorasHandler.getAllCorretoras(callback);
}

void BrasilAPIClient::getCorretorasByCnpj(
    std::string cnpj, std::function<void(std::variant<Corretoras, ErrorResponse>)> callback) {
  corretorasHandler.getCorretorasByCnpj(cnpj, callback);
}

void BrasilAPIClient::listAllCities(std::function<void(std::variant<CptecCidadesResponse, ErrorResponse>)> callback) {
  cptecHandler.listAllCities(callback);
}

void BrasilAPIClient::searchByTerms(
    std::string cityName, std::function<void(std::variant<CptecCidadesResponse, ErrorResponse>)> callback) {
  cptecHandler.searchByTerms(cityName, callback);
}

void BrasilAPIClient::listCondicoesMetereologicasCapitais(
    std::function<void(std::variant<CptecCapitaisResponse, ErrorResponse>)> callback) {
  cptecHandler.listCondicoesMetereologicasCapitais(callback);
}

void BrasilAPIClient::getCondicoesMetereologicasAeroporto(
    std::string icao, std::function<void(std::variant<CptecAeroporto, ErrorResponse>)> callback) {
  cptecHandler.getCondicoesMetereologicasAeroporto(icao, callback);
}

void BrasilAPIClient::getClimaEmCidade(
    int cityCode, std::function<void(std::variant<CidadeClimaResponse, ErrorResponse>)> callback) {
  cptecHandler.getClimaEmCidade(cityCode, callback);
}

void BrasilAPIClient::getPrevisaoCidadeSeisDias(
    int cityCode, int days, std::function<void(std::variant<CidadeClimaResponse, ErrorResponse>)> callback) {
  cptecHandler.getPrevisaoCidadeSeisDias(cityCode, days, callback);
}

void BrasilAPIClient::getPrevisaoOceanicaCidade(
    int cityCode, std::function<void(std::variant<CptecPrevisaoOceanica, ErrorResponse>)> callback) {
  cptecHandler.getPrevisaoOceanicaCidade(cityCode, callback);
}

void BrasilAPIClient::getPrevisaoOceanicaCidadeSeisDias(
    int cityCode, int days, std::function<void(std::variant<CptecPrevisaoOceanica, ErrorResponse>)> callback) {
  cptecHandler.getPrevisaoOceanicaCidadeSeisDias(cityCode, days, callback);
}

void BrasilAPIClient::listStateAndCities(int ddd, std::function<void(std::variant<DDDResponse, ErrorResponse>)> callback) {
  dddHandler.listStateAndCities(ddd, callback);
}

void BrasilAPIClient::listHolidaysAtYear(int ano, std::function<void(std::variant<FeriadosResponse, ErrorResponse>)> callback) {
  feriadosHandler.listHolidaysAtYear(ano, callback);
}

void BrasilAPIClient::listarFipeMarcas(const std::optional<std::string> &tipoVeiculo, const std::optional<int> &tabela_referencia,
    std::function<void(std::variant<FipeMarcas, ErrorResponse>)> callback) {
  fipeHandler.listarFipeMarcas(tipoVeiculo, tabela_referencia, callback);
}

void BrasilAPIClient::listarFipePreco(const std::string &codigoFipe, const std::optional<int> &tabela_referencia,
    std::function<void(std::variant<FipePrecos, ErrorResponse>)> callback) {
  fipeHandler.listarFipePreco(codigoFipe, tabela_referencia, callback);
}

void BrasilAPIClient::listarFipeTabelas(std::function<void(std::variant<FipeTabelasReferencia, ErrorResponse>)> callback) {
  fipeHandler.listarFipeTabelas(callback);
}

void BrasilAPIClient::listarMunicipios(const std::string &siglaUf, const std::optional<std::string> &providers,
    std::function<void(std::variant<IBGEMunicipiosResponse, ErrorResponse>)> callback) {
  ibgeHandler.listarMunicipios(siglaUf, providers, callback);
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

  banksHandler.getAllBanks([promisePtr](std::variant<BankResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<BankResponse>(result)) {
        BankResponse bankResponse = std::get<BankResponse>(result);
        promisePtr->set_value(bankResponse.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });

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

  banksHandler.getBanksByCode(code, [promisePtr](std::variant<Bank, ErrorResponse> result) {
    try {
      if (std::holds_alternative<Bank>(result)) {
        Bank bank = std::get<Bank>(result);
        promisePtr->set_value(bank.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });

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

  cepHandler.getCep(cep, [promisePtr](std::variant<CepResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CepResponse>(result)) {
        CepResponse cepResponse = std::get<CepResponse>(result);
        promisePtr->set_value(cepResponse.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief versão 2 do serviço de busca por CEP com múltiplos providers de fallback.
 * Retorna um objeto com informações referentes ao cep de busca.
 * @param cnpj código cep para efetuar a busca.
 */
std::future<std::string> BrasilAPIClient::getCepV2Async(int cep) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  cepHandler.getCepV2(cep, [promisePtr](std::variant<CepResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CepResponse>(result)) {
        CepResponse cepResponse = std::get<CepResponse>(result);
        promisePtr->set_value(cepResponse.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Busca por CNPJ na API Minha Receita.
 * Retorna um objeto com informações referentes ao cnpj solicitado.
 * @param cnpj cnpj para efetuar a busca.
 */
std::future<std::string> BrasilAPIClient::getCNPJAsync(std::string cnpj) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  cnpjHandler.getCNPJ(cnpj, [promisePtr](std::variant<CNPJResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CNPJResponse>(result)) {
        CNPJResponse cnpjResponse = std::get<CNPJResponse>(result);
        promisePtr->set_value(cnpjResponse.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief retorna todas as corretoras nos arquivos da CVM.
 * Retorna um array des objetos com informações sobre a corretora solicitada.
 */
std::future<std::string> BrasilAPIClient::getAllCorretorasAsync() {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  corretorasHandler.getAllCorretoras([promisePtr](std::variant<CorretorasResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CorretorasResponse>(result)) {
        CorretorasResponse corretoras = std::get<CorretorasResponse>(result);
        promisePtr->set_value(corretoras.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Busca por corretoras nos arquivos da CVM.
 * Retorna um objeto com informações sobre a corretora solicitada.
 * @param cnpj cnpj da corretora.
 */
std::future<std::string> BrasilAPIClient::getCorretorasByCnpjAsync(std::string cnpj) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  corretorasHandler.getCorretorasByCnpj(cnpj, [promisePtr](std::variant<Corretoras, ErrorResponse> result) {
    try {
      if (std::holds_alternative<Corretoras>(result)) {
        Corretoras corretoras = std::get<Corretoras>(result);
        promisePtr->set_value(corretoras.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Buscar localidades
 * Retorna listagem com todas as cidades junto a seus respectivos códigos presentes nos serviços da CPTEC. O Código destas
 * cidades será utilizado para os serviços de meteorologia e a ondas (previsão oceânica) fornecido pelo centro. Leve em
 * consideração que o WebService do CPTEC as vezes é instável, então se não encontrar uma determinada cidade na listagem
 * completa, tente buscando por parte de seu nome no endpoint de busca.
 */
std::future<std::string> BrasilAPIClient::listAllCitiesAsync() {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  cptecHandler.listAllCities([promisePtr](std::variant<CptecCidadesResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CptecCidadesResponse>(result)) {
        CptecCidadesResponse cidades = std::get<CptecCidadesResponse>(result);
        promisePtr->set_value(cidades.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

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

  cptecHandler.searchByTerms(cityName, [promisePtr](std::variant<CptecCidadesResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CptecCidadesResponse>(result)) {
        CptecCidadesResponse cidades = std::get<CptecCidadesResponse>(result);
        promisePtr->set_value(cidades.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Condições atuais nas capitais
 * Retorna condições meteorológicas atuais nas capitais do país, com base nas estações de solo de seu aeroporto.
 */
std::future<std::string> BrasilAPIClient::listCondicoesMetereologicasCapitaisAsync() {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  cptecHandler.listCondicoesMetereologicasCapitais([promisePtr](std::variant<CptecCapitaisResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CptecCapitaisResponse>(result)) {
        CptecCapitaisResponse capitais = std::get<CptecCapitaisResponse>(result);
        promisePtr->set_value(capitais.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Condições atuais em um aeroporto
 * Retorna condições meteorológicas atuais no aeroporto solicitado.
 * Este endpoint utiliza o código ICAO (4 dígitos) do aeroporto.
 * @param icao Código ICAO (4 dígitos) do aeroporto desejado.
 */
std::future<std::string> BrasilAPIClient::getCondicoesMetereologicasAeroportoAsync(std::string icao) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  cptecHandler.getCondicoesMetereologicasAeroporto(icao, [promisePtr](std::variant<CptecAeroporto, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CptecAeroporto>(result)) {
        CptecAeroporto aeroporto = std::get<CptecAeroporto>(result);
        promisePtr->set_value(aeroporto.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Previsão meteorológica de um dia de uma cidade
 * Retorna Pervisão meteorológica para 1 dia na cidade informada.
 *
 * @param cityCode Código da cidade fornecido. Veja CptecCidade.
 */
std::future<std::string> BrasilAPIClient::getCLimaEmCidadeAsync(int cityCode) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  cptecHandler.getClimaEmCidade(cityCode, [promisePtr](std::variant<CidadeClimaResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CidadeClimaResponse>(result)) {
        CidadeClimaResponse cidadeClima = std::get<CidadeClimaResponse>(result);
        promisePtr->set_value(cidadeClima.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Previsão meteorológica para, até, 6 dias
 * Retorna a previsão meteorológica para a cidade informada para um período de 1 até 6 dias.
 * Devido a inconsistências encontradas nos retornos da CPTEC nossa API só consegue retornar com precisão o período máximo de 6
 * dias.
 *
 * @param cityCode Código da cidade fornecido. Veja CptecCidade.
 * @param days Quantidade de dias desejado para a previsão. Máximo de 6 dias.
 */
std::future<std::string> BrasilAPIClient::getPrevisaoCidadeSeisDiasAsync(int cityCode, int days) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  cptecHandler.getPrevisaoCidadeSeisDias(cityCode, days, [promisePtr](std::variant<CidadeClimaResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CidadeClimaResponse>(result)) {
        CidadeClimaResponse cidadeClima = std::get<CidadeClimaResponse>(result);
        promisePtr->set_value(cidadeClima.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Previsão oceânica para uma cidade
 * Retorna a previsão oceânica para a cidade informada.
 *
 * @param cityCode Código da cidade fornecido. Veja CptecCidade.
 */
std::future<std::string> BrasilAPIClient::getPrevisaoOceanicaCidadeAsync(int cityCode) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  cptecHandler.getPrevisaoOceanicaCidade(cityCode, [promisePtr](std::variant<CptecPrevisaoOceanica, ErrorResponse> result) {
    try {
      if (std::holds_alternative<CptecPrevisaoOceanica>(result)) {
        CptecPrevisaoOceanica previsaoOceanicaCidade = std::get<CptecPrevisaoOceanica>(result);
        promisePtr->set_value(previsaoOceanicaCidade.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Previsão oceânica para uma cidade, para até 6 dias
 * Retorna a previsão oceânica para a cidade informada para um período de 1 até 6 dias.
 * Devido a inconsistências encontradas nos retornos da CPTEC nossa API só consegue retornar com precisão o período máximo de 6
 * dias.
 *
 * @param cityCode Código da cidade fornecido. Veja CptecCidade.
 * @param days Quantidade de dias desejado para a previsão. Máximo de 6 dias.
 */
std::future<std::string> BrasilAPIClient::getPrevisaoOceanicaCidadeSeisDiasAsync(int cityCode, int days) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  cptecHandler.getPrevisaoOceanicaCidadeSeisDias(
      cityCode, days, [promisePtr](std::variant<CptecPrevisaoOceanica, ErrorResponse> result) {
        try {
          if (std::holds_alternative<CptecPrevisaoOceanica>(result)) {
            CptecPrevisaoOceanica previsaoOceanicaCidade = std::get<CptecPrevisaoOceanica>(result);
            promisePtr->set_value(previsaoOceanicaCidade.serialize());
          } else {
            ErrorResponse error = std::get<ErrorResponse>(result);
            promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
          }
        } catch (const std::exception &e) {
          promisePtr->set_value("Exception: " + std::string(e.what()));
        }
      });
  return future;
};

/**
 * @brief Busca por DDD
 * Retorna um objeto com informações referentes ao DDD solicitado.
 * @param ddd ddd para efetuar a busca.
 */
std::future<std::string> BrasilAPIClient::listStateAndCitiesAsync(int ddd) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  dddHandler.listStateAndCities(ddd, [promisePtr](std::variant<DDDResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<DDDResponse>(result)) {
        DDDResponse dddResponse = std::get<DDDResponse>(result);
        promisePtr->set_value(dddResponse.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Busca por feriados
 * Retorna um objeto com informações referentes ao ano solicitado.
 * @param ano ano para efetuar a busca.
 */
std::future<std::string> BrasilAPIClient::listHolidaysAtYearAsync(int ano) {
  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  feriadosHandler.listHolidaysAtYear(ano, [promisePtr](std::variant<FeriadosResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<FeriadosResponse>(result)) {
        FeriadosResponse feriados = std::get<FeriadosResponse>(result);
        promisePtr->set_value(feriados.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Lista as marcas de veículos referente ao tipo de veículo
 * Retorna um objeto com informações referentes ao tipo de veículo e/ou tabela de referência solicitado.
 * @param tipoVeiculo tipo de veículo para efetuar a busca - opcional. Quando o tipo não é específicado são buscada as marcas de
 * todos os tipos de veículos
 * @param tabela_referencia tabela de referência para efetuar a busca - opcional.
 * Por padrão é utilizado o código da tabela fipe
 * atual.
 */
std::future<std::string> BrasilAPIClient::listarFipeMarcasAsync() {
  return listarFipeMarcasAsync(std::nullopt, std::nullopt);
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
std::future<std::string> BrasilAPIClient::listarFipeMarcasAsync(std::optional<std::string> tipoVeiculo) {
  return listarFipeMarcasAsync(tipoVeiculo, std::nullopt);
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
std::future<std::string> BrasilAPIClient::listarFipeMarcasAsync(std::optional<int> tabela_referencia) {
  return listarFipeMarcasAsync(std::nullopt, tabela_referencia);
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

std::future<std::string> BrasilAPIClient::listarFipeMarcasAsync(
    std::optional<std::string> tipoVeiculo, std::optional<int> tabela_referencia) {

  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  fipeHandler.listarFipeMarcas(tipoVeiculo, tabela_referencia, [promisePtr](std::variant<FipeMarcas, ErrorResponse> result) {
    try {
      if (std::holds_alternative<FipeMarcas>(result)) {
        FipeMarcas marcas = std::get<FipeMarcas>(result);
        promisePtr->set_value(marcas.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Consulta o preço do veículo segundo a tabela fipe.
 * Retorna um array de objetos com informações referentes ao veículo segundo a tabela fipe.
 * @param codigoFipe Código fipe do veículo/marca.
 * @param tabela_referencia tabela de referência para efetuar a busca - opcional.
 * Por padrão é utilizado o código da tabela fipe atual.
 */
std::future<std::string> BrasilAPIClient::listarFipePrecoAsync(std::string codigoFipe) {
  return listarFipePrecoAsync(codigoFipe, std::nullopt);
}

/**
 * @brief Consulta o preço do veículo segundo a tabela fipe.
 * Retorna um array de objetos com informações referentes ao veículo segundo a tabela fipe.
 * @param codigoFipe Código fipe do veículo/marca.
 * @param tabela_referencia tabela de referência para efetuar a busca - opcional.
 * Por padrão é utilizado o código da tabela fipe atual.
 */
std::future<std::string> BrasilAPIClient::listarFipePrecoAsync(std::string codigoFipe, std::optional<int> tabela_referencia) {

  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  fipeHandler.listarFipePreco(codigoFipe, tabela_referencia, [promisePtr](std::variant<FipePrecos, ErrorResponse> result) {
    try {
      if (std::holds_alternative<FipePrecos>(result)) {
        FipePrecos precos = std::get<FipePrecos>(result);
        promisePtr->set_value(precos.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Lista as tabelas fipe de referência existentes.
 * Retorna um array de objetos com informações referentes as tabelas de referência da tabela fipe.
 */
std::future<std::string> BrasilAPIClient::listarFipeTabelasAsync() {

  auto promisePtr = std::make_shared<std::promise<std::string>>();
  auto future = promisePtr->get_future();

  fipeHandler.listarFipeTabelas([promisePtr](std::variant<FipeTabelasReferencia, ErrorResponse> result) {
    try {
      if (std::holds_alternative<FipeTabelasReferencia>(result)) {
        FipeTabelasReferencia tabelasReferencia = std::get<FipeTabelasReferencia>(result);
        promisePtr->set_value(tabelasReferencia.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

/**
 * @brief Retorna os municípios da unidade federativa
 * Retorna um array de objetos com nome e codigo IBGE da unidade correspondente
 * @param siglaUf Sigla da unidade federativa, por exemplo SP, RJ, SC, etc.
 * @param providers Lista de provedores separados por vírgula. Este parâmetro é opcional.
 * Quando não fornecido, o sistema utilizará os provedores padrão.
 * Provedores Disponíveis: dados-abertos-br, gov, wikipedia
 */
std::future<std::string> BrasilAPIClient::listarMunicipiosAsync(std::string siglaUf) {
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

  ibgeHandler.listarMunicipios(siglaUf, providers, [promisePtr](std::variant<IBGEMunicipiosResponse, ErrorResponse> result) {
    try {
      if (std::holds_alternative<IBGEMunicipiosResponse>(result)) {
        IBGEMunicipiosResponse municipios = std::get<IBGEMunicipiosResponse>(result);
        promisePtr->set_value(municipios.serialize());
      } else {
        ErrorResponse error = std::get<ErrorResponse>(result);
        promisePtr->set_value("Error: " + std::to_string(error.errorCode) + " - " + error.errorMessage);
      }
    } catch (const std::exception &e) {
      promisePtr->set_value("Exception: " + std::string(e.what()));
    }
  });
  return future;
};

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