#include <drogon/drogon.h>
#include <drogon/HttpClient.h>
#include <json/json.h>

int main(){
    drogon::app()
        .loadConfigFile("config.json")
        .setLogLevel(trantor::Logger::LogLevel::kTrace)
        .run();
    
    return 0;
}
