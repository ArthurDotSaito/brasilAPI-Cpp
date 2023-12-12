// mainExample.cpp para testar BrasilAPIClient
#include "Client/BrasilAPIClient.h"
#include <iostream>
#include <drogon/drogon.h>
#include <drogon/HttpClient.h>
#include <chrono>
#include <thread>

int main() {
    BrasilAPIClient brasilAPI;
    brasilAPI.setUserAgent("MeuApp/1.0");
    
    std::cout << "Starting banks API request..." << std::endl;

/*     auto futureBanks = brasilAPI.getAllBanksAsync();
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
 */

    auto futureCorretoras = brasilAPI.getAllCorretorasAsync();
    auto corretorasData = futureCorretoras.get();
    std::cout << "Corretoras Data: " << corretorasData << std::endl;

    auto futureCorretora = brasilAPI.getCorretorasByCnpjAsync("02332886000104");
    auto corretoraData = futureCorretora.get();
    std::cout << "Corretora Data: " << corretoraData << std::endl;

    return 0;
}
