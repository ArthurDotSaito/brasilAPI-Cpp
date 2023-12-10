#include "Handlers/BanksHandler.h"
#include "Response/BankResponse.h"
#include <drogon/drogon.h>

class BrasilAPIClient {
private:
    BanksHandler banksHandler;
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

    // Funções que retornam std::future<std::string>
    std::future<std::string> getAllBanksAsync();
    std::future<std::string> getBanksByCodeAsync(int code);
};