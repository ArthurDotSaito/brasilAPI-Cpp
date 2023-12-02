#include <drogon/HttpController.h>

class TestController : public drogon::HttpController<TestController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TestController::handleGetAllBanks, "/api/banks/v1", drogon::Get);
    METHOD_LIST_END

    void handleGetAllBanks(const drogon::HttpRequestPtr &req, 
    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setBody(R"([{"ispb":"00000000","name":"Test Bank","code":123,"fullName":"Test Bank Ltd."}])");
        callback(resp);
    }

};
