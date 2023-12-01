// main.cpp para testar BrasilAPIClient
#include "Client/BrasilAPIClient.h"
#include <iostream>
#include <drogon/drogon.h>
#include <drogon/HttpClient.h>
#include <chrono>
#include <thread>

int main() {
    BrasilAPIClient brasilAPI;
    brasilAPI.setUserAgent("MeuApp/1.0");
    

    std::cout << "Iniciando a solicitação de bancos..." << std::endl;

    brasilAPI.getAllBanks([](const BankResponse& response) {
        std::cout << "Callback recebido." << std::endl;
        if (response.banks.empty()) {
        
            std::cout << "Nenhum banco recebido." << std::endl;
        } else {
            std::cout << "Bancos recebidos:" << std::endl;
            for (const auto& bank : response.banks) {
                std::cout << "Nome do Banco: " << bank.name << std::endl;
            }
        }
         drogon::app().quit();
    });

    drogon::app()
        .setLogLevel(trantor::Logger::LogLevel::kTrace)
        .run();
    std::cout << "Programa finalizado." << std::endl;
    return 0;
}
