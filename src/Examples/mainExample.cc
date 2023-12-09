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

    brasilAPI.getAllBanks();
    brasilAPI.getBanksByCode(1);

    return 0;
}
