// mainExample.cpp para testar BrasilAPIClient
#include "Client/BrasilAPIClient.h"
#include <chrono>
#include <drogon/HttpClient.h>
#include <drogon/drogon.h>
#include <iostream>
#include <thread>

int main() {
  BrasilAPIClient brasilAPI;
  brasilAPI.setUserAgent("MeuApp/1.0");

  std::cout << "Starting banks API request..." << std::endl;

  /*
  auto futureBanks = brasilAPI.getAllBanksAsync();
  auto banksData = futureBanks.get();
  std::cout << "Banks Data: " << banksData << std::endl;

  auto futureBank = brasilAPI.getBanksByCodeAsync(1);
  auto bankData = futureBank.get();
  std::cout << "Bank Data: " << bankData << std::endl;

  auto futureCep = brasilAPI.getCepAsync(89010025);
  auto cepData = futureCep.get();
  std::cout << "Cep Data: " << cepData << std::endl;

  auto futureCepV2 = brasilAPI.getCepV2Async(89010025);
  auto cepDataV2 = futureCepV2.get();
  std::cout << "Cep Data V2: " << cepDataV2 << std::endl;

  auto futureCNPJ = brasilAPI.getCNPJAsync("19131243000197");
  auto cnpjData = futureCNPJ.get();
  std::cout << "CNPJ Data: " << cnpjData << std::endl;

  auto futureCorretoras = brasilAPI.getAllCorretorasAsync();
  auto corretorasData = futureCorretoras.get();
  std::cout << "Corretoras Data: " << corretorasData << std::endl;

  auto futureCorretora = brasilAPI.getCorretorasByCnpjAsync("02332886000104");
  auto corretoraData = futureCorretora.get();
  std::cout << "Corretora Data: " << corretoraData << std::endl;

  auto futureCptec = brasilAPI.listAllCitiesAsync();
  auto cptecData = futureCptec.get();
  std::cout << "Cptec Data: " << cptecData << std::endl;

  auto futureCptec2 = brasilAPI.searchByTermsAsync("Blumenau");
  auto cptecData2 = futureCptec2.get();
  std::cout << "Cptec Data: " << cptecData2 << std::endl;

  auto futureCptec3 = brasilAPI.getCapitaisAsync();
  auto cptecData3 = futureCptec3.get();
  std::cout << "Cptec Data: " << cptecData3 << std::endl;

  auto futureCptec4 = brasilAPI.getCondicoesAeroportoAsync("SBAR");
  auto cptecData4 = futureCptec4.get();
  std::cout << "Cptec Data: " << cptecData4 << std::endl;

  auto futureCptec5 = brasilAPI.getCidadesClimaByCidadeAsync(999);
  auto cptecData5 = futureCptec5.get();
  std::cout << "Cptec Data: " << cptecData5 << std::endl;

  auto futureCptec6 = brasilAPI.previsaoCidadeSeisDiasAsync(999, 6);
  auto cptecData6 = futureCptec6.get();
  std::cout << "Cptec Data: " << cptecData6 << std::endl;

  auto futureCptec7 = brasilAPI.previsaoOceanicaCidadeAsync(241);
  auto cptecData7 = futureCptec7.get();
  std::cout << "Cptec Data: " << cptecData7 << std::endl;


  auto futureCptec8 = brasilAPI.previsaoOceanicaCidadeSeisDiasAsync(241, 6);
  auto cptecData8 = futureCptec8.get();
  std::cout << "Cptec Data: " << cptecData8 << std::endl;

  auto ddd = brasilAPI.listStateAndCitiesAsync(21);
  auto dddData = ddd.get();
  std::cout << "DDD Data: " << dddData << std::endl;

  auto feriados = brasilAPI.getFeriadosAsync(2024);
  auto feriadosData = feriados.get();
  std::cout << "Feriados Data: " << feriadosData << std::endl;
  return 0;
  */

  auto fipe = brasilAPI.listFipeMarcasAsync();
  auto fipeData = fipe.get();
  std::cout << "Fipe Data: " << fipeData << std::endl;

  auto fipe1 = brasilAPI.listFipeMarcasAsync("carros");
  auto fipeData1 = fipe1.get();
  std::cout << "Fipe Data: " << fipeData1 << std::endl;

  auto fipe2 = brasilAPI.listFipeMarcasAsync(102);
  auto fipeData2 = fipe2.get();
  std::cout << "Fipe Data: " << fipeData2 << std::endl;

  return 0;
}
