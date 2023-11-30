// main.cpp para testar BrasilAPIClient
#include "Client/BrasilAPIClient.h"
#include <iostream>

int main() {
    BrasilAPIClient brasilAPI;
    brasilAPI.setUserAgent("MeuApp/1.0");

    brasilAPI.getAllBanks([](const BankResponse& response) {
        std::cout << "Bancos recebidos:" << std::endl;
        for (const auto& bank : response.banks) {
            std::cout << "Nome do Banco: " << bank.name << std::endl;
            
        }
    });

    // Await async 
    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}
