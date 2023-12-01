#include <drogon/HttpController.h>

class TestController : public drogon::HttpController<TestController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TestController::handleGet, "/api/{1}", drogon::Get);
    ADD_METHOD_TO(TestController::handlePost, "/api/{1}", drogon::Post);
    METHOD_LIST_END

    void handleGet(const drogon::HttpRequestPtr &req, 
    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
        auto path = req->getPath();
        auto resp = drogon::HttpResponse::newHttpResponse();

        if (path == "/api/banks/v1") {
            resp->setBody("Response for /banks/v1");
        }

        callback(resp);
    }

    void handlePost(const drogon::HttpRequestPtr &req, 
    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
        auto path = req->getPath();
        auto resp = drogon::HttpResponse::newHttpResponse();

        callback(resp);
    }
};
