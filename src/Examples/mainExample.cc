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
  /*
  auto futureBank = brasilAPI.getBanksByCodeAsync(0);
  auto bankData = futureBank.get();
  std::cout << "Bank Data: " << bankData << std::endl;

  auto futureBank2 = brasilAPI.getAllBanksAsync();
  auto bankData2 = futureBank2.get();
  std::cout << "Bank Data: " << bankData2 << std::endl;


  auto futureCep = brasilAPI.getCepAsync(890125);
  auto cepData = futureCep.get();
  std::cout << "Cep Data: " << cepData << std::endl;

  auto futureCepV2 = brasilAPI.getCepV2Async(89010025);
  auto cepDataV2 = futureCepV2.get();
  std::cout << "Cep Data V2: " << cepDataV2 << std::endl;


  auto futureCNPJ = brasilAPI.getCNPJAsync("19131243000197");
  auto cnpjData = futureCNPJ.get();
  std::cout << "CNPJ Data: " << cnpjData << std::endl;

  auto futureCorretora = brasilAPI.getCorretorasByCnpjAsync("02332886000104");
  auto corretoraData = futureCorretora.get();
  std::cout << "Corretora Data: " << corretoraData << std::endl;

  auto futureCorretoras = brasilAPI.getAllCorretorasAsync();
  auto corretorasData = futureCorretoras.get();
  std::cout << "Corretoras Data: " << corretorasData << std::endl;

  auto futureCptec = brasilAPI.listAllCitiesAsync();
  auto cptecData = futureCptec.get();
  std::cout << "Cptec Data: " << cptecData << std::endl;

  auto futureCptec2 = brasilAPI.searchByTermsAsync("Blumenau");
  auto cptecData2 = futureCptec2.get();
  std::cout << "Cptec Data: " << cptecData2 << std::endl;

  auto futureCptec3 = brasilAPI.listCondicoesMetereologicasCapitaisAsync();
  auto cptecData3 = futureCptec3.get();
  std::cout << "Cptec Data: " << cptecData3 << std::endl;

  auto futureCptec4 = brasilAPI.getCondicoesMetereologicasAeroportoAsync("SBAR");
  auto cptecData4 = futureCptec4.get();
  std::cout << "Cptec Data: " << cptecData4 << std::endl;

  auto futureCptec5 = brasilAPI.getCLimaEmCidadeAsync(999);
  auto cptecData5 = futureCptec5.get();
  std::cout << "Cptec Data: " << cptecData5 << std::endl;

  auto futureCptec6 = brasilAPI.getPrevisaoCidadeSeisDiasAsync(999, 6);
  auto cptecData6 = futureCptec6.get();
  std::cout << "Cptec Data: " << cptecData6 << std::endl;

  auto futureCptec7 = brasilAPI.getPrevisaoOceanicaCidadeAsync(241);
  auto cptecData7 = futureCptec7.get();
  std::cout << "Cptec Data: " << cptecData7 << std::endl;

  auto futureCptec8 = brasilAPI.getPrevisaoOceanicaCidadeSeisDiasAsync(241, 6);
  auto cptecData8 = futureCptec8.get();
  std::cout << "Cptec Data: " << cptecData8 << std::endl;
  */

  auto ddd = brasilAPI.listStateAndCitiesAsync(21);
  auto dddData = ddd.get();
  std::cout << "DDD Data: " << dddData << std::endl;

  auto feriados = brasilAPI.listHolidaysAtYearAsync(2024);
  auto feriadosData = feriados.get();
  std::cout << "Feriados Data: " << feriadosData << std::endl;

  /*
  auto fipe = brasilAPI.listFipeMarcasAsync();
  auto fipeData = fipe.get();
  std::cout << "Fipe Data: " << fipeData << std::endl;

  auto fipe1 = brasilAPI.listFipeMarcasAsync("carros");
  auto fipeData1 = fipe1.get();
  std::cout << "Fipe Data: " << fipeData1 << std::endl;

  auto fipe2 = brasilAPI.listFipeMarcasAsync(102);
  auto fipeData2 = fipe2.get();
  std::cout << "Fipe Data: " << fipeData2 << std::endl;

  auto fipe3 = brasilAPI.listFipePrecoAsync("001004-9");
  auto fipeData3 = fipe3.get();
  std::cout << "Fipe Data: " << fipeData3 << std::end auto fipe4 = brasilAPI.listFipeTabelasAsync();
  auto fipeData4 = fipe4.get();
  std::cout << "Fipe Data: " << fipeData4 << std::endl;

  auto ibge = brasilAPI.listMunicipiosAsync("SC");
  auto ibgeData = ibge.get();
  std::cout << "IBGE Data: " << ibgeData << std::endl;

  auto ibge1 = brasilAPI.listMunicipiosAsync("SC", "gov");
  auto ibgeData1 = ibge1.get();
  std::cout << "IBGE Data: " << ibgeData1 << std::endl;

  auto ibge2 = brasilAPI.listRegioesAsync();
  auto ibgeData2 = ibge2.get();
  std::cout << "IBGE Data: " << ibgeData2 << std::endl;

  auto ibge3 = brasilAPI.getEstadoAsync("SC");
  auto ibgeData3 = ibge3.get();
  std::cout << "IBGE Data: " << ibgeData3 << std::endl;
  */
  return 0;
}
