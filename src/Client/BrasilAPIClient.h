#include <drogon/drogon.h>
#include "Handlers/BanksHandler.h"
#include "Response/BankResponse.h"
#include "Handlers/CepHandler.h"
#include "Response/CepResponse.h"
#include "Handlers/CNPJHandler.h"
#include "Response/CNPJResponse.h"

class BrasilAPIClient {
private:
    BanksHandler banksHandler;
    CepHandler cepHandler;
    std::string userAgent;
    std::thread eventLoopThread;
    std::mutex mutex;

    void startEventLoop() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!eventLoopThread.joinable()) {
            eventLoopThread = std::thread([]() {
                drogon::app().run();
            });
        }
    }
public:
    BrasilAPIClient();
    ~BrasilAPIClient();

    void setUserAgent(const std::string& userAgent);

    // Funções que usam callbacks
    void getAllBanks(std::function<void(const BankResponse&)> callback);
    void getBanksByCode(int code, std::function<void(const Bank&)> callback);
    void getCep(int cep, std::function<void(const CepResponse&)> callback);
    void getCepV2(int cep, std::function<void(const CepResponse&)> callback);
    void getCNPJ(std::string cnpj, std::function<void(const CNPJResponse&)> callback);

    // Funções que retornam std::future<std::string>
    std::future<std::string> getAllBanksAsync();
    std::future<std::string> getBanksByCodeAsync(int code);
    std::future<std::string> getCepAsync(int cep);
    std::future<std::string> getCepV2Async(int cep);
    std::future<std::string> getCNPJAsync(std::string cnpj);
};