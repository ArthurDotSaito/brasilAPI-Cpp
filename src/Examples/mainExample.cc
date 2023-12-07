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

    brasilAPI.getAllBanks([](const BankResponse& response) {
        std::cout << "Callback received." << std::endl;
        std::cout << response.serialize() << std::endl;
    });

    brasilAPI.getBanksByCode(1, [](const Bank& response) {
        std::cout << "Callback received." << std::endl;
        std::cout << response.serialize() << std::endl;
        drogon::app().quit();
    });

    drogon::app()
        .setLogLevel(trantor::Logger::LogLevel::kTrace)
        .run();
    std::cout << "Program end." << std::endl;
    return 0;
}
