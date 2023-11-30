#include <drogon/HttpClient.h>

class BrasilAPIFacadeBase{
    protected:
        std::shared_ptr<drogon::HttpClient> httpClient;
        const std::string baseUrl = "https://brasilapi.com.br/api";

    public:
        BrasilAPIFacadeBase(){
            httpClient = drogon::HttpClient::newHttpClient(baseUrl);
        }
        void ensureSuccess(const drogon::HttpResponsePtr& response, const std::string& url);
};