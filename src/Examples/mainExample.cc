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
    
    std::cout << "Starting banks API request..." << std::endl;

    brasilAPI.getAllBanks([](const BankResponse& response) {
        std::cout << "Callback received." << std::endl;
        if (response.banks.empty()) {
            std::cout << "No banks returned." << std::endl;
        } else {
            std::cout << "Banks received:" << std::endl;
            for (const auto& bank : response.banks) {
                std::cout << "Bank name: " << bank.name << std::endl;
            }
        }
         drogon::app().quit();
    });

    brasilAPI.getBanksByCode(1, [](const Bank& bank) {
        std::cout << "Callback received." << std::endl;
        std::cout << "Bank Name: " << bank.name << std::endl;
        std::cout << "Bank Code: " << (bank.code.has_value() ? std::to_string(bank.code.value()) : "N/A") << std::endl;
        std::cout << "Fullname: " << bank.fullName << std::endl;
        drogon::app().quit();
    });

    drogon::app()
        .setLogLevel(trantor::Logger::LogLevel::kTrace)
        .run();
    std::cout << "Program end." << std::endl;
    return 0;
}
